#include "LargeFloat.h"

void ULargeFloat::SetFromString(const FString& InDecimal, int32 PrecisionBits)
{
    Value.precision(PrecisionBits);
    Value = BigFloat(TCHAR_TO_UTF8(*InDecimal));

    TArray<uint8> Bytes;
    SerializeToBytes(Bytes);
    BuildChunks(Bytes);
}

FString ULargeFloat::ToString() const
{
    return UTF8_TO_TCHAR(Value.str().c_str());
}

void ULargeFloat::SerializeToBytes(TArray<uint8>& OutBytes) const
{
    std::string Str = Value.str();
    uint32 Precision = Value.precision();

    FMemoryWriter Writer(OutBytes);
    Writer << Precision;

    uint32 Len = (uint32)Str.size();
    Writer << Len;
    Writer.Serialize((void*)Str.data(), Len);
}

void ULargeFloat::DeserializeFromBytes(const TArray<uint8>& InBytes)
{
    FMemoryReader Reader(InBytes);

    uint32 Precision;
    Reader << Precision;

    uint32 Len;
    Reader << Len;

    std::string Str;
    Str.resize(Len);
    Reader.Serialize(&Str[0], Len);

    Value.precision(Precision);
    Value = BigFloat(Str);
}
