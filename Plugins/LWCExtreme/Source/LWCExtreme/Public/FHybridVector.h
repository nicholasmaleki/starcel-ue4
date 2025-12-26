#pragma once
#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "FHybridNumber.h"
#include "FHybridVector.generated.h"

USTRUCT(BlueprintType)
struct LWCEXTREME_API FHybridVector
{
    GENERATED_BODY()

public:
    FHybridNumber X;
    FHybridNumber Y;
    FHybridNumber Z;

    // ------------------------------
    // Constructors
    // ------------------------------
    FHybridVector() = default;

    FHybridVector(const FHybridNumber& InX, const FHybridNumber& InY, const FHybridNumber& InZ)
        : X(InX), Y(InY), Z(InZ) {}

    FHybridVector(const FHybridVector& Other)
        : X(Other.X), Y(Other.Y), Z(Other.Z) {}

    // ------------------------------
    // Arithmetic operators
    // ------------------------------
    FORCEINLINE FHybridVector operator+(const FHybridVector& Other) const
    {
        return FHybridVector(X + Other.X, Y + Other.Y, Z + Other.Z);
    }

    FORCEINLINE FHybridVector operator-(const FHybridVector& Other) const
    {
        return FHybridVector(X - Other.X, Y - Other.Y, Z - Other.Z);
    }

    // Scalar multiplication/division
    FORCEINLINE FHybridVector operator*(const FHybridNumber& Scalar) const
    {
        return FHybridVector(X * Scalar, Y * Scalar, Z * Scalar);
    }

    FORCEINLINE FHybridVector operator/(const FHybridNumber& Scalar) const
    {
        return FHybridVector(X / Scalar, Y / Scalar, Z / Scalar);
    }

    FORCEINLINE FHybridVector& operator+=(const FHybridVector& Other)
    {
        X = X + Other.X; Y = Y + Other.Y; Z = Z + Other.Z;
        return *this;
    }

    FORCEINLINE FHybridVector& operator-=(const FHybridVector& Other)
    {
        X = X - Other.X; Y = Y - Other.Y; Z = Z - Other.Z;
        return *this;
    }

    FORCEINLINE FHybridVector& operator*=(const FHybridNumber& Scalar)
    {
        X = X * Scalar; Y = Y * Scalar; Z = Z * Scalar;
        return *this;
    }

    FORCEINLINE FHybridVector& operator/=(const FHybridNumber& Scalar)
    {
        X = X / Scalar; Y = Y / Scalar; Z = Z / Scalar;
        return *this;
    }

    // Component-wise multiplication/division
    FORCEINLINE FHybridVector operator*(const FHybridVector& Other) const
    {
        return FHybridVector(X * Other.X, Y * Other.Y, Z * Other.Z);
    }

    FORCEINLINE FHybridVector operator/(const FHybridVector& Other) const
    {
        return FHybridVector(X / Other.X, Y / Other.Y, Z / Other.Z);
    }

    // ------------------------------
    // Vector math
    // ------------------------------
    // Component-wise multiplication (Scale)
    FORCEINLINE FHybridVector Scale(const FHybridVector& Other) const
    {
        return FHybridVector(X * Other.X, Y * Other.Y, Z * Other.Z);
    }

    FORCEINLINE FHybridNumber Dot(const FHybridVector& Other) const
    {
        return X * Other.X + Y * Other.Y + Z * Other.Z;
    }

    FORCEINLINE FHybridVector Cross(const FHybridVector& Other) const
    {
        return FHybridVector(
            Y * Other.Z - Z * Other.Y,
            Z * Other.X - X * Other.Z,
            X * Other.Y - Y * Other.X
        );
    }

    FORCEINLINE FHybridNumber Size() const
    {
        return (X * X + Y * Y + Z * Z).Sqrt();
    }

    FORCEINLINE FHybridNumber SizeSquared() const
    {
        return X * X + Y * Y + Z * Z;
    }

    FORCEINLINE FHybridVector GetSafeNormal() const
    {
        FHybridNumber Mag = Size();
        if (Mag > FHybridNumber(0))
            return *this / Mag;
        return FHybridVector(FHybridNumber(0), FHybridNumber(0), FHybridNumber(0));
    }

    FORCEINLINE FHybridNumber DistanceTo(const FHybridVector& Other) const
    {
        return (*this - Other).Size();
    }

    FORCEINLINE FHybridNumber DistanceSquared(const FHybridVector& Other) const
    {
        FHybridVector Delta = *this - Other;
        return Delta.SizeSquared();
    }

    FORCEINLINE FHybridVector ProjectOnVector(const FHybridVector& Other) const
    {
        FHybridNumber DotProd = this->Dot(Other);
        FHybridNumber OtherMagSq = Other.SizeSquared();
        return Other * (DotProd / OtherMagSq);
    }

    FORCEINLINE static FHybridVector Combine(const FHybridVector& A, const FHybridVector& B, const FHybridVector& C)
    {
        return FHybridVector(A.X * B.X + C.X, A.Y * B.Y + C.Y, A.Z * B.Z + C.Z);
    }

    // ------------------------------
    // Comparisons
    // ------------------------------
    FORCEINLINE bool operator==(const FHybridVector& Other) const
    {
        return X == Other.X && Y == Other.Y && Z == Other.Z;
    }

    FORCEINLINE bool operator!=(const FHybridVector& Other) const
    {
        return !(*this == Other);
    }

    // ------------------------------
    // NetSerialize
    // ------------------------------
    FORCEINLINE bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
    {
        bool SuccessX, SuccessY, SuccessZ;
        X.NetSerialize(Ar, Map, SuccessX);
        Y.NetSerialize(Ar, Map, SuccessY);
        Z.NetSerialize(Ar, Map, SuccessZ);
        bOutSuccess = SuccessX && SuccessY && SuccessZ;
        return bOutSuccess;
    }
};

// ------------------------------
// NetSerialize trait
// ------------------------------
template<>
struct TStructOpsTypeTraits<FHybridVector> : public TStructOpsTypeTraitsBase2<FHybridVector>
{
    enum { WithNetSerializer = true, WithCopy = true };
};
