// Do NOT include CoreMinimal.h here
// This TU is isolated from Unreal headers
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include "XTensorBridgeAPI.h"
THIRD_PARTY_INCLUDES_START
#pragma push_macro("check")
#pragma push_macro("verify")
#pragma push_macro("PI")
#pragma push_macro("small")
#pragma push_macro("big")
#pragma push_macro("min")
#pragma push_macro("max")
#pragma push_macro("constant")
#undef check
#undef verify
#undef PI
#undef small
#undef big
#undef min
#undef max
#undef constant
#include <boost/multiprecision/mpfr.hpp>
#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <xtensor/containers/xarray.hpp>
#include <xtensor/containers/xadapt.hpp>
#include <xtensor/core/xmath.hpp>
#include <xtensor/io/xio.hpp>
#include <gmp.h>
#pragma pop_macro("constant")
#pragma pop_macro("big")
#pragma pop_macro("small")
#pragma pop_macro("PI")
#pragma pop_macro("verify")
#pragma pop_macro("max")
#pragma pop_macro("min")
#pragma pop_macro("check")
THIRD_PARTY_INCLUDES_END

using boost::multiprecision::cpp_int;
using boost::multiprecision::mpfr_float;

using namespace boost::multiprecision;

extern "C"
{
    void XTensor_SmokeTest()
    {
        xt::xarray<double> a = {{1.0, 2.0}, {3.0, 4.0}};
        auto b = xt::sqrt(a);

        cpp_int x = 1;
        x <<= 100;
    }
}

namespace XTensorBridge
{
    void MultiplyArrayByScalar(TArray<float>& Array, float Scalar)
    {
        // Convert TArray -> xtensor
        xt::xarray<float> tensor(Array.Num());
        for (int i = 0; i < Array.Num(); ++i)
            tensor(i) = Array[i];

        // Multiply
        tensor *= Scalar;

        // Convert back to TArray
        for (int i = 0; i < Array.Num(); ++i)
            Array[i] = tensor(i);
    }

    FString BigIntToString(const FString& ValueStr)
    {
        // Convert FString -> cpp_int
        std::string StdStr(TCHAR_TO_UTF8(*ValueStr));
        cpp_int bigInt(StdStr);

        // Example operation
        cpp_int squared = bigInt * bigInt;

        // Return as FString
        return FString(squared.str().c_str());
    }
}
