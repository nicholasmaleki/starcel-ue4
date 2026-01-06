#import os, sys, socket, subprocess, cmdix, xarray as xr, numpy as np, fast_autocomplete, dill
#from p10ga_py import *
#from skimage.measure import marching_cubes
#import scipy.sparse.linalg
#dill.dump_session('globalsave.pkl')

print("Recursion\n")
import dill
dill.load_session('globalsave.pkl') # Maybe faster than loading the libraries from scratch
print("opening TCP on port 7828...")
HOST = "127.0.0.1"
PORT = 7828

# list(cmdix.listcommands()): arch, base64, basename, bunzip2, bzip2, cal, cat, cp, crond, diff, dirname, env, expand, gunzip, gzip, httpd, init, kill, ln, logger, ls, md5sum, mkdir, mktemp, more, mv, nl, pwd, rm, rmdir, sendmail, seq, sh, sha1sum, sha224sum, sha256sum, sha384sum, sha512sum, shred, shuf, sleep, sort, tail, tar, touch, uname, uuidgen, wc, wget, yes, zip


#cmd = ['echo', 'I like potatos']
#proc = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

#o, e = proc.communicate()

#print('Output: ' + o.decode('ascii'))
#print('Error: '  + e.decode('ascii'))
#print('code: ' + str(proc.returncode))


class StdoutHandler:
    def __init__(self):
        self.last_output = ""
    
    def start(self):
        self._handled_stdout = sys.stdout
        sys.stdout = self
    
    def write(self, data: str):
        # write(data="") is called for the end kwarg in print(..., end="")
        if data:
            #print("does this work?")
            self.last_output+= data
            self._handled_stdout.write(data)

    def end(self):
        sys.stdout = self._handled_stdout
    
    def flush(self):
        self._handled_stdout.flush()


def ls(args):
    windows_command="dir /b /ogn"
    if not args or args is None:
        # cmdix.runcommandline(windows_command + " ".join(args))
        print(subprocess.check_output(windows_command.split(" "), shell=True, cwd=os.getcwd(), text=True))
        #return subprocess.run(windows_command.split(" "), capture_output=True, text=True, shell=True,cwd=os.path.dirname(os.path.realpath(__file__))).stdout
        #return subprocess.Popen(windows_command.split(" "), stdout=subprocess.PIPE, shell=True, cwd=os.path.dirname(os.path.realpath(__file__))).communicate()[0].decode('utf-8')
        #subprocess.check_output(windows_command.split(" "))
        #subprocess.run(windows_command.split(" "), capture_output=True, shell=True,cwd=os.getcwd()).stdout.decode('utf-8')
        # op = subprocess.Popen(windows_command.split(" "), stderr=subprocess.PIPE, stdout=subprocess.PIPE)
        # if op:
        #     o, e = op.communicate()
        #     # print(op.stdout.read())
        #     #print('Error: '  + e.decode('ascii'))
        #     #print('code: ' + str(proc.returncode))
        #     return o.decode('ascii')
    else:
        print(subprocess.check_output(windows_command.split(" ").append(args), shell=True, cwd=os.getcwd(), text=True))
        #return subprocess.run(windows_command.split(" ").append(args), capture_output=True, text=True).stdout
        #return subprocess.Popen(windows_command.split(" ").append(args), stdout=subprocess.PIPE, shell=True, cwd = os.path.dirname(os.path.realpath(__file__))).communicate()[0].decode('utf-8')
        # subprocess.check_output(windows_command.split(" ").append(args))
        #subprocess.run(windows_command.split(" ").append(args), shell=True)
        # op = subprocess.Popen(windows_command.split(" ").append(args), stderr=subprocess.PIPE, stdout=subprocess.PIPE)
        # if op:
        #     o, e = op.communicate()
        #     #print('Error: '  + e.decode('ascii'))
        #     #print('code: ' + str(proc.returncode))
        #     return o.decode('ascii')

def man(args):
    print((subprocess.run(["help"], shell=True, capture_output=True, text=True).stdout))


def getalias():
    # load aliases from csv into xarray
    aliasfunctions = xr.DataArray(np.loadtxt("../../../data/aliasfunctions.csv", delimiter=",", dtype=str))
    available_functions = aliasfunctions.isel(dim_1=0)[1:]
    #print([func.split('/') for func in available_functions])
    for function in np.array(available_functions):
        print("'" + function + "'" + ",")
    flat_list = [item for sublist in [func.split('/') for func in np.array(available_functions)] for item in sublist]
    return flat_list #available_functions

#Collect all aliases
#test_keys = np.array(getalias()).tolist()
#print(test_keys)
words = {}
for key in getalias():
    words[key] = {}

def autocomplete(search_word):
    autocomplete = fast_autocomplete.AutoComplete(words=words)
    ac_output = []
    if search_word:
        ac_output = autocomplete.search(word=search_word[0])
    #print(ac_output)
    #return [''.join(x) for x in ac_output]
    return ['_autocomplete'] + ac_output

def plot(_):
    x, y, z = np.pi*np.mgrid[-1:1:7j, -1:1:7j, -1:1:7j]
    vol = np.cos(x) + np.cos(y) + np.cos(z)
    iso_val=0.0
    verts, faces, normals, values = marching_cubes(vol, iso_val, spacing=(0.4, 0.4, 0.4))
    return ("_vertices", [["X=%.3f"%x[0] + " Y=%.3f"%x[1] + " Z=%.3f"%x[2]]for x in verts] , "_faces", [["X=%s"%x[0] + " Y=%s"%x[1] + " Z=%s"%x[2]]for x in faces] , "_normals", [["X=%.3f"%x[0] + " Y=%.3f"%x[1] + " Z=%.3f"%x[2]]for x in normals])

#stdout handler so it cant be sent over tcp
stdout_handler = StdoutHandler()
stdout_handler.start()

#os.chdir(os.path.dirname(os.path.realpath(__file__)))

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.bind((HOST, PORT))
    s.listen(True)
    conn, addr = s.accept()
    with conn:
        #file = s.makefile('w', buffering=None)
        #sys.stdout = file
        print("connected by " + str(addr))
        elapsedtime=0
        print("beginning TCP eval loop...")
        while True:
            elapsedtime += 1
            data = conn.recv(65536)#1024
            if not data:
                break
            print(data.decode())
            parsed = data.decode().strip().split(' ')
            output=None
            stdout_handler.last_output = ""
            if parsed[0] in list(cmdix.listcommands()): # linux commands
                output = cmdix.runcommandline(data.decode())
            elif ((parsed[0]) in locals().keys()): # functions defined in this file
                #print("customfunc called")
                #print(parsed[1:])
                output = locals()[parsed[0]](parsed[1:]) # TODO: Support for no argument functions 
                
            else:
                #print("eval called")
                try:
                    output = exec(data.decode()) # Executing of receieved statement. Exec relies on the stdout print statements to receive output whereas when this is switched to eval, output is sent back over the socket 
                except Exception as e:
                    output = e
            #output = "tempoutput"
            #print(output)
            #print(type(output))
            if not str(output) or output is None or output == "":
                # print("output empty defaulting to stdout")
                output = repr(stdout_handler.last_output)
            
            if output is not None:
                output = str(output)[:65536]
                #print(output)
                #print("output print finished")
                conn.sendall(str(output).encode())
                print("data sent" + str(output))
        print("loop end")
# with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
#     s.connect((HOST, PORT))
#     elapsedtime=0
#     print("beginning TCP eval loop...")
#     while True:
#         elapsedtime += 1
#         data = s.recv(65536)
#         if not data:
#             break
#         s.sendall(eval(data))
#     print("loop end")



# import numpy as np
# from numpy import cos, pi
# from skimage.measure import marching_cubes
# import matplotlib.pyplot as plt
# from mpl_toolkits.mplot3d import Axes3D

# x, y, z = pi*np.mgrid[-1:1:31j, -1:1:31j, -1:1:31j]
# vol = cos(x) + cos(y) + cos(z)
# iso_val=0.0
# verts, faces, _, _ = marching_cubes(vol, iso_val, spacing=(0.1, 0.1, 0.1))

# fig = plt.figure()
# ax = fig.add_subplot(111, projection='3d')
# ax.plot_trisurf(verts[:, 0], verts[:,1], faces, verts[:, 2], cmap='Spectral', lw=1)
# plt.show()