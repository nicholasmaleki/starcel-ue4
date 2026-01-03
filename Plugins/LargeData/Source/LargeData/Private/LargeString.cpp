#include "LargeString.h"

void ULargeString::SetFromString(const FString& InString)
{
    Value = TCHAR_TO_UTF8(*InString);
    BuildChunks();
}

FString ULargeString::ToString() const
{
    return FString(UTF8_TO_TCHAR(Value.c_str()));
}

void ULargeString::SerializeToBytes(TArray<uint8>& OutBytes) const
{
    OutBytes.Append(
        reinterpret_cast<const uint8*>(Value.data()),
        Value.size()
    );
}

void ULargeString::DeserializeFromBytes(const TArray<uint8>& InBytes)
{
    Value.assign(
        reinterpret_cast<const char*>(InBytes.GetData()),
        InBytes.Num()
    );
}
