#include "LargeInt.h"
THIRD_PARTY_INCLUDES_START
#pragma push_macro("check")
#undef check
#include <boost/multiprecision/cpp_int.hpp>
#pragma pop_macro("check")
THIRD_PARTY_INCLUDES_END

void ULargeInt::SetFromString(const FString& ValueStr)
{
    std::string S(TCHAR_TO_UTF8(*ValueStr));
    Value = boost::multiprecision::cpp_int(S);
    BuildChunks();
}

FString ULargeInt::ToString() const
{
    return UTF8_TO_TCHAR(Value.convert_to<std::string>().c_str());
}

void ULargeInt::SerializeToBytes(TArray<uint8>& Out) const
{
    std::string S = Value.convert_to<std::string>();
    Out.Append((uint8*)S.data(), S.size());
}

void ULargeInt::DeserializeFromBytes(const TArray<uint8>& In)
{
    std::string S((char*)In.GetData(), In.Num());
    Value = boost::multiprecision::cpp_int(S);
}
