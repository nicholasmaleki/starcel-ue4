# UNTESTED
# Control a Multimeter, Python-Arduino (LabJack), and Spectrometer

# Tekpower TP4000 or https://www.amazon.com/Tekpower-TP5000-Multimeter/dp/B010HDFFQ8
# https://www.amazon.com/LabJack-U3-LV/dp/B000NF9CAG or https://www.amazon.com/LabJack-U3-HV/dp/B001716LD6
# Ebay for a USB 4000 or https://www.oceanoptics.com/spectrometer/sr2/ https://www.oceanoptics.com/spectrometers/


import serial
# pip install pyserial

class Dmm: # https://github.com/Xuth/tp4000_dmm
    """
    Takes readings off the serial port from a class of multimeters that includes
    the TekPower TP4000ZC (the meter I own) and supposedly is the same as the the
    'VC820' mode in QtDMM.

    example code:

    # load the module
    import tp4000zc

    # the port that we're going to use.  This can be a number or device name.
    # on linux or posix systems this will look like /dev/tty2 or /dev/ttyUSB0
    # on windows this will look something like COM3
    port = '/dev/ttyUSB0'

    # get an instance of the class
    dmm = tp4000zc.Dmm(port)

    # read a value
    val = dmm.read()

    print val.text       # print the text representation of the value
                         # something like: -4.9 millivolts DC
    print val.numericVal # and the numeric value
                         # ie: -0.0048
    # recycle the serial port
    dmm.close()


    Public Interface:
    __init__(port, retries=3, timeout=3.0):
        Instantiating the class attempts to open the serial port specified,
        initialize it and read enough from the serial port to synchronize
        the module with the start/end of a full reading.

    read():
        Attempt to get a complete reading off of the serial port, parse it and
        return an instance of DmmValue holding the interpretted reading.

    close():
        Finally you can close the serial port connection with close()

    Exceptions will be raised if
       * PySerial raises an exception (SerialException or ValueError)
       * this module can't get a full reading that passes initial data integrity
         checks (subclasses of DmmException)
       * I made a coding error (whatever python might throw)

    If no exceptions are raised the DmmValue might still fail various sanity
    checks or not have a numeric value.  Ie I believe that showing showing
    multiple decimal points makes no sense but is valid per the protocol so
    no exception is raised but the saneValue flag will be set to False in the
    DmmValue.

    Meter Documentation:

    Per the documentation page, the meter spits out readings which are bursts of
    14 bytes every .25 seconds.  The high nibble of each byte is the byte number
    (1-14) for synchronization and sanity checks, the low nibble holds the data.

    Each data bit represents an individual field on the LCD display of the meter,
    from segments of the 7 segment digits to individual flags.  Bytes 1 and 10-14
    are flags (with four bits reserved/unmapped on this meter) and bytes (2,3),
    (4,5), (5,6) and (7,8) representing the individual digits on the display.

    For the digits, if the high bit of the first nibble of a digit is set then the
    negative sign (for the first digit) or the leading decimal point is turned on.
    the remaining bits of the two nibbles represent the elements of the 7 segment
    digit display as follows:

      pos 3       nibble 1:   S123
     p     p      nibble 2:   4567
     o     o      where S is either the sign or decimal bit.
     s     s
     2     7      The legal values of the segment bits are represented in
      pos 6       digitTable and include the digits 0-9 along with blank and
     p     p      'L'.
     o     o
     s     s
     1     5
      pos 4

    Serial settings for this meter are:
    2400 baud 8N1
    """

    bytesPerRead = 14

    def __init__(self, port='/dev/ttyUSB0', retries=3, timeout=3.0):
        self.ser = serial.Serial(
            port=port,
            baudrate=2400,
            parity=serial.PARITY_NONE,
            stopbits=serial.STOPBITS_ONE,
            bytesize=serial.EIGHTBITS,
            timeout=timeout)
        self.retries = retries  # the number of times it's allowed to retry to get a valid 14 byte read

        self._synchronize()

    def close(self):
        "Close the serial port connection."
        self.ser.close()

    def read(self):
        "Attempt to take a reading from the digital multimeter."

        # first get a set of bytes and validate it.
        # if the first doesn't validate, synch and get a new set.
        success = False
        for readAttempt in range(self.retries):
            data = self.ser.read(self.bytesPerRead)
            if len(data) != self.bytesPerRead:
                self._synchronize()
                continue

            for pos, byte in enumerate(data, start=1):
                # in Python3 indexing a bytes object yields an int
                if byte // 16 != pos:
                    self._synchronize()
                    break
            else:
                success = True
                break

            # if we're here we need to resync and retry
            self._synchronize()

        if not success:
            raise DmmReadFailure()

        val = ''
        for (d1, d2, ch) in self.digits:
            highBit, digit = self._readDigit(data[d1 - 1], data[d2 - 1])
            if highBit:
                val = val + ch
            val = val + digit

        attribs = self._initAttribs()
        for k, v in self.bits.items():
            self._readAttribByte(data[k - 1], v, attribs)

        return DmmValue(val, attribs, readAttempt, data)

    def _synchronize(self):
        v = self.ser.read(1)
        if len(v) != 1:
            raise DmmNoData()
        # v is a bytes object of length 1; indexing gives an int
        n = v[0]
        pos = n // 16
        if pos == 0 or pos == 15:
            raise DmmInvalidSyncValue()

        bytesNeeded = self.bytesPerRead - pos
        if bytesNeeded:
            v = self.ser.read(bytesNeeded)
            # should we check the validity of these bytes?
            # the read() function allows an occasional invalid
            # read without throwing an exception so for now
            # I'll say no.

    bits = {
        1: [('flags', 'AC'), ('flags', 'DC'), ('flags', 'AUTO'), ('flags', 'RS232')],
        10: [('scale', 'micro'), ('scale', 'nano'), ('scale', 'kilo'), ('measure', 'diode')],
        11: [('scale', 'milli'), ('measure', '% (duty-cycle)'), ('scale', 'mega'),
             ('flags', 'beep')],
        12: [('measure', 'Farads'), ('measure', 'Ohms'), ('flags', 'REL delta'),
             ('flags', 'Hold')],
        13: [('measure', 'Amps'), ('measure', 'volts'), ('measure', 'Hertz'),
             ('other', 'other_13_1')],
        14: [('other', 'other_14_4'), ('measure', 'degrees Celcius'), ('other', 'other_14_2'),
             ('other', 'other_14_1')]}

    digits = [(2, 3, '-'), (4, 5, '.'), (6, 7, '.'), (8, 9, '.')]
    digitTable = {(0, 5): '1', (5, 11): '2', (1, 15): '3', (2, 7): '4', (3, 14): '5',
                  (7, 14): '6', (1, 5): '7', (7, 15): '8', (3, 15): '9', (7, 13): '0',
                  (6, 8): 'L', (0, 0): ' '}

    def _initAttribs(self):
        return {'flags': [], 'scale': [], 'measure': [], 'other': []}

    def _readAttribByte(self, byte, bits, attribs):
        # byte is int in Python3 when indexing a bytes object
        b = byte % 16
        bitVal = 8
        for (attr, val) in bits:
            v = b // bitVal
            if v:
                b = b - bitVal
                # print("adding flag type %s, val %s" % (attr, val))
                attribs[attr].append(val)
            bitVal //= 2

    def _readDigit(self, byte1, byte2):
        # byte1 and byte2 are ints
        b1 = byte1 % 16
        highBit = b1 // 8
        b1 = b1 % 8
        b2 = byte2 % 16
        try:
            digit = self.digitTable[(b1, b2)]
        except Exception:
            digit = 'X'
        return highBit, digit


class DmmValue:
    """
    This is a representation of a single read from the multimeter.

    Attributes in rough order of usefulness:

    Sanity checks:
       saneValue: True if no sanity checks failed.

    High level computed fields:
       text: Nicely formatted text representation of the value.
       numericVal: numeric value after SI prefixes applied or None if value is non-numeric.
       measurement: what is being measured.
       delta: True if the meter is in delta mode.
       ACDC: 'AC', 'DC' or None.
       readErrors:  Number of failed reads attempts before successfully getting a reading
           from the meter.

    Other, possibly useful, computed fields:
       val: cleaned up display value
       scale: SI prefix for val

    Unprocessed values:
       rawVal: Numeric display
       flags: Various flags modifying the measurement
       scaleFlags: SI scaling factor flags
       measurementFlags: Flags to specify what the meter is measuring
       reservedFlags: Flags that are undefined
       rawBytes:  the raw, 14 byte bitstream that produced this value.

    """

    def __init__(self, val, attribs, readErrors, rawBytes):
        self.saneValue = True
        self.rawVal = self.val = val
        self.flags = attribs['flags']
        self.scaleFlags = attribs['scale']
        self.measurementFlags = attribs['measure']
        self.reservedFlags = attribs['other']
        self.readErrors = readErrors
        self.rawBytes = rawBytes
        self.text = 'Invalid Value'

        self.processFlags()
        self.processScale()
        self.processMeasurement()
        self.processVal()

        if self.saneValue:
            self.createTextExpression()

    def createTextExpression(self):
        text = self.deltaText
        text += self.val
        text += ' '
        text += self.scale
        text += self.measurement
        text += self.ACDCText
        self.text = text

    def processFlags(self):
        flags = self.flags
        self.ACDC = None
        self.ACDCText = ''
        self.delta = False
        self.deltaText = ''

        if 'AC' in flags and 'DC' in flags:
            self.saneValue = False
        if 'AC' in flags:
            self.ACDC = 'AC'
        if 'DC' in flags:
            self.ACDC = 'DC'
        if self.ACDC is not None:
            self.ACDCText = ' ' + self.ACDC
        if 'REL delta' in flags:
            self.delta = True
            self.deltaText = 'delta '

    scaleTable = {'nano': 0.000000001, 'micro': 0.000001, 'milli': 0.001,
                  'kilo': 1000.0, 'mega': 1000000.0}

    def processScale(self):
        s = self.scaleFlags
        self.scale = ''
        self.multiplier = 1

        if len(s) == 0:
            return
        if len(s) > 1:
            self.saneValue = False
            return
        self.scale = s[0]
        self.multiplier = self.scaleTable[self.scale]

    def processMeasurement(self):
        m = self.measurementFlags
        self.measurement = None
        if len(m) != 1:
            self.saneValue = False
            return
        self.measurement = m[0]

    def processVal(self):
        v = self.rawVal
        self.numericVal = None
        if 'X' in v:
            self.saneValue = False
            return
        if v.count('.') > 1:
            self.saneValue = False
            return

        n = None
        try:
            n = float(v)
        except Exception:
            pass

        if n is not None:
            self.val = '%s' % n  # this should remove leading zeros, spaces etc.
            self.numericVal = n * self.multiplier

    def __repr__(self):
        return "<DmmValue instance: %s>" % self.text


class DmmException(Exception):
    "Base exception class for Dmm."


class DmmNoData(DmmException):
    "Read from serial port timed out with no bytes read."


class DmmInvalidSyncValue(DmmException):
    "Got an invalid byte during syncronization."


class DmmReadFailure(DmmException):
    "Unable to get a successful read within the number of allowed retries."




import seabreeze.spectrometers as sb
# pip install seabreeze then, seabreeze_os_setup

class Spectrometer: # USB 4000 or
    """
    mySpectrometer = Spectrometer("USB4H08370")
    print(mySpectrometer.get_wavelengths())  # return a list of the wavelengths
    print(mySpectrometer.get_counts())
    """
    def __init__(self, serial_num):
        self.serial_num = serial_num
        self.device = sb.Spectrometer.from_serial_number(self.serial_num) # alternatively, get the first device spec = sb.Spectrometer(self.devices[0])
        self.integration_time = 10000
        self.device.integration_time_micros(self.integration_time)
        self.CalDark = None
        self.Cal1 = None
        self.devices = sb.list_devices()

    def get_devices(self):
        self.devices = sb.list_devices()
        return self.devices

    def print_devices(self):
        print(self.devices)

    def open(self):
        self.device._open_device(self.device)

    def close(self):
        self.device.close()

    def set_integration_time(self, integration_time):
        self.integration_time = integration_time
        self.device.integration_time_micros(self.integration_time)

    def get_wavelengths(self):
        return self.device.wavelengths()

    def get_counts(self):
        return self.device.counts()

    def get_spectra(self):
        return {'wavelengths': self.get_wavelengths(), 'Counts': self.get_counts()}




from helpers import u3

## Prerequisites
# You need LabJackPython.py, Modbus.py, and u3.py which can be found on LabJack's GitHub, (https://github.com/labjack/LabJackPython)
# Run LabJack.exe, https://labjack.com/support/software/installers/ud to install LabJack dependencies
# https://labjack.com/support/datasheets/u3/hardware-description all data pins are flexible but the CIO which are dedicated digital pins

## Example Code
"""
import time
from LabJack import LabJack, Pin

my_labs = LabJack(None)          # create a new set of LabJacks
my_labs.open_devices()          # open all of the devices
my_labs.print_devices_serial_numbers()  # print all of the serial numbers
# my_labs.setup_devices()       # use this to setup the defaults of devices in mass
# my_labs.reset_devices()       # use this to reset the defaults of devices in mass
my_labs.close_devices()         # close all of the devices

my_lab = LabJack(320086141)      # create a single LabJack based on the serial numbers printed earlier
my_lab.open()                   # open that single LabJack

for i in range(5):              # toggle LabJack indicator LED 5 times
    my_lab.toggle_led()
    time.sleep(0.5)

print(bin(int(my_lab.get_fio_state())))  # print current FIO pin states
print(bin(int(my_lab.get_eio_state())))  # print current EIO pin states

my_pin = Pin(my_lab, "FIO7")     # create a pin on FIO7

# The following four lines configure everything for you:
print(my_pin.read_digital())    # digital read on my_pin
print(my_pin.read_analog())     # analog read on my_pin
my_pin.set_high()
my_pin.set_low()

my_pin2 = Pin(my_lab, "DAC1")    # create a pin on DAC1
my_pin2.set_voltage(1.5)        # set pin voltage to 1.5V
"""

class LabJack:  # A simple wrapper for LabJack devices which brings high level arduino-like functions to the device.
    def __init__(self, serial_num):
        self.serial_num = serial_num
        self.lab = u3.U3(autoOpen=False)
        self.labs = []

    def open_devices(self):
        self.labs = u3.openAllU3()
        return self.labs

    def close_devices(self):
        for ser_num, device in self.labs.items():
            device.close()

    def reset_devices(self):
        for ser_num, device in self.labs.items():
            device.reset()

    def setup_devices(
        self,
        local_id=None,
        timer_counter_config=None,
        fio_analog=None,
        fio_direction=None,
        fio_state=None,
        eio_analog=None,
        eio_direction=None,
        eio_state=None,
        cio_direction=None,
        cio_state=None,
        dac1_enable=None,
        dac0=None,
        dac1=None,
        timer_clock_config=None,
        timer_clock_divisor=None,
        compatibility_options=None,
    ):
        config_results = []
        for ser_num, device in self.labs.items():
            t_u3 = self.labs[ser_num]
            config_results.append(
                t_u3.configU3(
                    LocalID=local_id,
                    TimerCounterConfig=timer_counter_config,
                    FIOAnalog=fio_analog,
                    FIODirection=fio_direction,
                    FIOState=fio_state,
                    EIOAnalog=eio_analog,
                    EIODirection=eio_direction,
                    EIOState=eio_state,
                    CIODirection=cio_direction,
                    CIOState=cio_state,
                    DAC1Enable=dac1_enable,
                    DAC0=dac0,
                    DAC1=dac1,
                    TimerClockConfig=timer_clock_config,
                    TimerClockDivisor=timer_clock_divisor,
                    CompatibilityOptions=compatibility_options,
                )
            )
        return config_results

    def print_devices_serial_numbers(self):
        for ser_num, device in self.labs.items():
            print(ser_num + "\n")

    def open(self):
        self.lab.open(serial=self.serial_num)

    def close(self):
        self.lab.close()

    def reset(self):
        self.lab.reset()

    def setup(
        self,
        local_id=None,
        timer_counter_config=None,
        fio_analog=None,
        fio_direction=None,
        fio_state=None,
        eio_analog=None,
        eio_direction=None,
        eio_state=None,
        cio_direction=None,
        cio_state=None,
        dac1_enable=None,
        dac0=None,
        dac1=None,
        timer_clock_config=None,
        timer_clock_divisor=None,
        compatibility_options=None,
    ):
        return self.lab.configU3(
            LocalID=local_id,
            TimerCounterConfig=timer_counter_config,
            FIOAnalog=fio_analog,
            FIODirection=fio_direction,
            FIOState=fio_state,
            EIOAnalog=eio_analog,
            EIODirection=eio_direction,
            EIOState=eio_state,
            CIODirection=cio_direction,
            CIOState=cio_state,
            DAC1Enable=dac1_enable,
            DAC0=dac0,
            DAC1=dac1,
            TimerClockConfig=timer_clock_config,
            TimerClockDivisor=timer_clock_divisor,
            CompatibilityOptions=compatibility_options,
        )

    def read_analog(self, pin_id):
        return self.lab.getAIN(pin_id)

    def read_digital(self, pin_id):
        return self.lab.getFeedback(u3.BitStateRead(pin_id))

    def set_pin_high(self, pin_id):
        return self.lab.getFeedback(u3.BitStateWrite(IONumber=pin_id, State=1))

    def set_pin_low(self, pin_id):
        return self.lab.getFeedback(u3.BitStateWrite(IONumber=pin_id, State=0))

    def set_pin_output(self, pin_id):
        if not self.is_output(pin_id):
            return self.lab.getFeedback(u3.BitDirWrite(pin_id, 1))

    def set_pin_input(self, pin_id):
        if not self.is_input(pin_id):
            return self.lab.getFeedback(u3.BitDirWrite(pin_id, 0))

    def is_input(self, pin_id):  # input is 0 and output is 1
        return self.lab.getFeedback(u3.BitDirRead(pin_id))[0] == 0

    def is_output(self, pin_id):  # input is 0 and output is 1
        return self.lab.getFeedback(u3.BitDirRead(pin_id))[0] == 1

    def get_fio_state(self):
        config_dict = self.lab.configIO()
        return config_dict["FIOAnalog"]

    def get_eio_state(self):
        config_dict = self.lab.configIO()
        return config_dict["EIOAnalog"]

    def set_pin_analog(self, pin_id):
        self.set_pin_state(pin_id, 1)

    def set_pin_digital(self, pin_id):
        self.set_pin_state(pin_id, 0)

    def set_pin_state(self, pin_id, state):
        channel_id = pin_id.lower()
        channel_id = channel_id.replace("fio", "").replace("eio", "").replace("cio", "")
        if pin_id.lower().startswith("fio"):
            self.lab.configIO(FIOAnalog=self.set_bit(self.get_fio_state(), channel_id, state))
        elif pin_id.lower().startswith("eio"):
            self.lab.configIO(EIOAnalog=self.set_bit(self.get_eio_state(), channel_id, state))
        elif pin_id.lower().startswith("cio"):
            if state != 0:
                print("CIO cannot be changed from digital.")
        else:
            print("Pin ID must be formatted like: FIO4.")

    def set_bit(self, pin_bits, index, state):
        index = int(index)
        mask = 1 << index
        if state:
            pin_bits |= mask
        else:
            pin_bits &= ~mask
        return pin_bits

    def toggle_led(self):
        self.lab.toggleLED()

    def set_pin_DAC0(self, voltage):
        dac0_value = self.lab.voltageToDACBits(voltage, dacNumber=0, is16Bits=False)
        return self.lab.getFeedback(u3.DAC0_8(dac0_value))

    def set_pin_DAC1(self, voltage):
        dac1_value = self.lab.voltageToDACBits(voltage, dacNumber=1, is16Bits=False)
        return self.lab.getFeedback(u3.DAC1_8(dac1_value))


class Pin:
    def __init__(self, labjack, pin_id):
        self.pin_id = pin_id.lower()
        self.channel_id = self.get_channel_id()
        self.labjack = labjack
        self.pin_state = None
        self.io_state = None
        self.ad_state = None

    def get_channel_id(self):
        channel_id = int(self.pin_id.replace("fio", "").replace("eio", "").replace("cio", "").replace("dac", ""))
        if self.pin_id.startswith("fio"):
            pass
        elif self.pin_id.startswith("eio"):
            channel_id += 8
        elif self.pin_id.startswith("cio"):
            channel_id += 16
        elif self.pin_id.startswith("dac"):
            channel_id = -2
        else:
            channel_id = -1
        return channel_id

    def set_pin_id(self, pin_id):
        self.pin_id = pin_id
        self.channel_id = self.get_channel_id()

    def set_labjack(self, labjack):
        self.labjack = labjack

    def set_analog(self):
        if self.ad_state != "A":
            self.ad_state = "A"
            if self.channel_id >= 0:
                self.labjack.set_pin_analog(self.pin_id)
            else:
                print("That action cannot be performed on this pin")

    def set_digital(self):
        if self.ad_state != "D":
            self.ad_state = "D"
            if self.channel_id >= 0:
                self.labjack.set_pin_digital(self.pin_id)
            else:
                print("That action cannot be performed on this pin")

    def set_input(self):
        if self.io_state != "I":
            self.io_state = "I"
            if self.channel_id >= 0:
                self.set_digital()
                return self.labjack.set_pin_input(self.channel_id)
            else:
                print("That action cannot be performed on this pin")

    def set_output(self):
        if self.io_state != "O":
            self.io_state = "O"
            if self.channel_id >= 0:
                self.set_digital()
                return self.labjack.set_pin_output(self.channel_id)
            else:
                print("That action cannot be performed on this pin")

    def set_high(self):
        if self.pin_state != "High":
            self.pin_state = "High"
            if self.channel_id >= 0:
                self.set_output()
                return self.labjack.set_pin_high(self.channel_id)
            else:
                print("That action cannot be performed on this pin")

    def set_low(self):
        if self.pin_state != "Low":
            self.pin_state = "Low"
            if self.channel_id >= 0:
                self.set_output()
                return self.labjack.set_pin_low(self.channel_id)
            else:
                print("That action cannot be performed on this pin")

    def read_analog(self):
        if self.channel_id >= 0:
            self.set_analog()
            return self.labjack.read_analog(self.channel_id)
        else:
            print("That action cannot be performed on this pin")

    def read_digital(self):
        if self.channel_id >= 0:
            self.set_digital()
            self.set_input()
            return self.labjack.read_digital(self.channel_id)
        else:
            print("That action cannot be performed on this pin")

    def set_voltage(self, voltage):
        if self.channel_id == -2:
            if self.pin_id == "dac0":
                return self.labjack.set_pin_DAC0(voltage)
            if self.pin_id == "dac1":
                return self.labjack.set_pin_DAC1(voltage)
            else:
                print("That is not a valid pin id")
        else:
            print("That action cannot be performed on this pin")