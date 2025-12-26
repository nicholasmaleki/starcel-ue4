#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "ThirdParty/ThirdPartyIncludes.h"
#include <sstream>
#include "FHybridNumber.generated.h"

using BigInt = boost::multiprecision::cpp_int;
using HPFloat = boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>>; // dynamic precision

USTRUCT(BlueprintType)
struct LWCEXTREME_API FHybridNumber
{
    GENERATED_BODY()

public:
    BigInt Num{ 0 };
    BigInt Den{ 1 };
    HPFloat FloatValue{ 0 };
    bool bIsRational{ true };
    int32 MPFRBitsOverride{ 0 };

    // ------------------------------
    // Constructors
    // ------------------------------
    FHybridNumber() = default;

    // Rational constructors
    FHybridNumber(const BigInt& InNum)
        : Num(InNum), Den(1), bIsRational(true) {}

    FHybridNumber(const BigInt& InNum, const BigInt& InDen)
        : Num(InNum), Den(InDen), bIsRational(true)
    {
        SafeRational();
    }

    FHybridNumber(int32 Val)
        : Num(Val), Den(1), bIsRational(true) {}

    FHybridNumber(int64 Val)
        : Num(Val), Den(1), bIsRational(true) {}

    // Floating point constructors
    FHybridNumber(double Val)
        : FloatValue(Val), bIsRational(false) {}

    FHybridNumber(const HPFloat& Val)
        : FloatValue(Val), bIsRational(false) {}

    FHybridNumber(const FHybridNumber& Other)
    {
        bIsRational = Other.bIsRational;
        if (bIsRational)
        {
            Num = Other.Num;
            Den = Other.Den;
        }
        else
        {
            FloatValue = Other.FloatValue;
        }
    }

    // ------------------------------
    // Safety
    // ------------------------------
    FORCEINLINE void SafeRational() { if (Den == 0) Den = 1; }

    // ------------------------------
    // Conversions
    // ------------------------------
    FORCEINLINE FString ToString() const
    {
        if (bIsRational)
            return FString(Num.str().c_str()) + TEXT("/") + FString(Den.str().c_str());
        std::stringstream ss;
        ss << FloatValue;
        return FString(ss.str().c_str());
    }

    FORCEINLINE static FHybridNumber FromString(const FString& Str)
    {
        FHybridNumber Out;
        FString Left, Right;
        if (Str.Split(TEXT("/"), &Left, &Right))
        {
            Out.Num = BigInt(TCHAR_TO_UTF8(*Left));
            Out.Den = BigInt(TCHAR_TO_UTF8(*Right));
            Out.bIsRational = true;
            Out.SafeRational();
        }
        else
        {
            Out.FloatValue = HPFloat(TCHAR_TO_UTF8(*Str));
            Out.bIsRational = false;
        }
        return Out;
    }

    // ------------------------------
    // Arithmetic helpers
    // ------------------------------
    FORCEINLINE HPFloat AsFloat() const
    {
        return bIsRational ? HPFloat(Num.str()) / HPFloat(Den.str()) : FloatValue;
    }

    // ------------------------------
    // Arithmetic operators
    // ------------------------------
    FORCEINLINE FHybridNumber operator+(const FHybridNumber& Other) const
    {
        if (bIsRational && Other.bIsRational)
            return FHybridNumber(Num * Other.Den + Other.Num * Den, Den * Other.Den);

        return FHybridNumber(AsFloat() + Other.AsFloat());
    }

    FORCEINLINE FHybridNumber operator-(const FHybridNumber& Other) const
    {
        if (bIsRational && Other.bIsRational)
            return FHybridNumber(Num * Other.Den - Other.Num * Den, Den * Other.Den);

        return FHybridNumber(AsFloat() - Other.AsFloat());
    }

    FORCEINLINE FHybridNumber operator*(const FHybridNumber& Other) const
    {
        if (bIsRational && Other.bIsRational)
            return FHybridNumber(Num * Other.Num, Den * Other.Den);

        return FHybridNumber(AsFloat() * Other.AsFloat());
    }

    FORCEINLINE FHybridNumber operator/(const FHybridNumber& Other) const
    {
        if (bIsRational && Other.bIsRational)
        {
            if (Other.Num == 0) return FHybridNumber(0);
            return FHybridNumber(Num * Other.Den, Den * Other.Num);
        }

        HPFloat B = Other.AsFloat();
        return FHybridNumber(B != 0 ? AsFloat() / B : 0);
    }

    FORCEINLINE FHybridNumber operator-() const
    {
        return bIsRational ? FHybridNumber(-Num, Den) : FHybridNumber(-FloatValue);
    }

    // ------------------------------
    // Comparison operators
    // ------------------------------
    FORCEINLINE bool operator==(const FHybridNumber& Other) const
    {
        if (bIsRational && Other.bIsRational) return Num * Other.Den == Other.Num * Den;
        return AsFloat() == Other.AsFloat();
    }

    FORCEINLINE bool operator!=(const FHybridNumber& Other) const { return !(*this == Other); }
    FORCEINLINE bool operator<(const FHybridNumber& Other) const
    {
        if (bIsRational && Other.bIsRational) return Num * Other.Den < Other.Num* Den;
        return AsFloat() < Other.AsFloat();
    }
    FORCEINLINE bool operator<=(const FHybridNumber& Other) const { return *this < Other || *this == Other; }
    FORCEINLINE bool operator>(const FHybridNumber& Other) const { return !(*this <= Other); }
    FORCEINLINE bool operator>=(const FHybridNumber& Other) const { return !(*this < Other); }

    // ------------------------------
    // Math functions
    // ------------------------------
    FORCEINLINE FHybridNumber Sqrt() const { return FHybridNumber(boost::multiprecision::sqrt(AsFloat())); }
    FORCEINLINE FHybridNumber Ln() const { return FHybridNumber(boost::multiprecision::log(AsFloat())); }
    FORCEINLINE FHybridNumber Exp() const { return FHybridNumber(boost::multiprecision::exp(AsFloat())); }
    FORCEINLINE FHybridNumber Sin() const { return FHybridNumber(boost::multiprecision::sin(AsFloat())); }
    FORCEINLINE FHybridNumber Cos() const { return FHybridNumber(boost::multiprecision::cos(AsFloat())); }
    FORCEINLINE FHybridNumber Tan() const { return FHybridNumber(boost::multiprecision::tan(AsFloat())); }

    // ------------------------------
    // NetSerialize
    // ------------------------------
    FORCEINLINE bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
    {
        FString Str = ToString();
        const int32 ChunkSize = 1024;

        if (Ar.IsSaving())
        {
            int32 TotalLength = Str.Len();
            Ar << TotalLength;
            for (int32 Offset = 0; Offset < TotalLength; Offset += ChunkSize)
            {
                FString Chunk = Str.Mid(Offset, FMath::Min(ChunkSize, TotalLength - Offset));
                Ar << Chunk;
            }
        }
        else
        {
            int32 TotalLength = 0;
            Ar << TotalLength;
            Str.Empty();
            Str.Reserve(TotalLength);
            for (int32 Offset = 0; Offset < TotalLength; Offset += ChunkSize)
            {
                FString Chunk;
                Ar << Chunk;
                Str += Chunk;
            }
            *this = FromString(Str);
        }

        bOutSuccess = true;
        return true;
    }
};

// ------------------------------
// NetSerialize trait
// ------------------------------
template<>
struct TStructOpsTypeTraits<FHybridNumber> : public TStructOpsTypeTraitsBase2<FHybridNumber>
{
    enum { WithNetSerializer = true, WithCopy = true };
};
