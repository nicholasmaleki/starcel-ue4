#pragma once
#include "CoreMinimal.h"
#include "FHybridNumber.h"
#include "FHybridVector.h"
#include "FHybridQuaternion.generated.h"

USTRUCT(BlueprintType)
struct LWCEXTREME_API FHybridQuaternion
{
    GENERATED_BODY()

public:
    FHybridNumber X;
    FHybridNumber Y;
    FHybridNumber Z;
    FHybridNumber W;

    // Constructors
    FHybridQuaternion() : X(0), Y(0), Z(0), W(1) {}
    FHybridQuaternion(FHybridNumber InX, FHybridNumber InY, FHybridNumber InZ, FHybridNumber InW)
        : X(InX), Y(InY), Z(InZ), W(InW) {}

    // Arithmetic operators
    FORCEINLINE FHybridQuaternion operator*(const FHybridQuaternion& Other) const
    {
        return FHybridQuaternion(
            W * Other.X + X * Other.W + Y * Other.Z - Z * Other.Y,
            W * Other.Y - X * Other.Z + Y * Other.W + Z * Other.X,
            W * Other.Z + X * Other.Y - Y * Other.X + Z * Other.W,
            W * Other.W - X * Other.X - Y * Other.Y - Z * Other.Z
        );
    }

    FORCEINLINE FHybridQuaternion operator*(const FHybridNumber& Scalar) const
    {
        return FHybridQuaternion(X * Scalar, Y * Scalar, Z * Scalar, W * Scalar);
    }

    FORCEINLINE FHybridQuaternion operator+(const FHybridQuaternion& Other) const
    {
        return FHybridQuaternion(X + Other.X, Y + Other.Y, Z + Other.Z, W + Other.W);
    }

    FORCEINLINE FHybridQuaternion operator-(const FHybridQuaternion& Other) const
    {
        return FHybridQuaternion(X - Other.X, Y - Other.Y, Z - Other.Z, W - Other.W);
    }

    // Normalize
    FORCEINLINE FHybridQuaternion Normalize() const
    {
        FHybridNumber Len = (X * X + Y * Y + Z * Z + W * W).Sqrt();
        return (Len != FHybridNumber(0)) ? (*this * (FHybridNumber(1) / Len)) : FHybridQuaternion();
    }

    // Conjugate
    FORCEINLINE FHybridQuaternion Conjugate() const
    {
        return FHybridQuaternion(-X, -Y, -Z, W);
    }

    // Inverse
    FORCEINLINE FHybridQuaternion Inverse() const
    {
        FHybridNumber NormSq = X * X + Y * Y + Z * Z + W * W;
        if (NormSq == FHybridNumber(0)) return FHybridQuaternion();
        FHybridQuaternion Conj = Conjugate();
        return FHybridQuaternion(Conj.X / NormSq, Conj.Y / NormSq, Conj.Z / NormSq, Conj.W / NormSq);
    }

    // SLERP (simplified linear fallback)
    FORCEINLINE FHybridQuaternion Slerp(const FHybridQuaternion& To, const FHybridNumber& Alpha) const
    {
        FHybridQuaternion Result = (*this * (FHybridNumber(1) - Alpha)) + (To * Alpha);
        return Result.Normalize();
    }

    // Rotate vector
    FORCEINLINE FHybridVector RotateVector(const FHybridVector& Vec) const
    {
        FHybridQuaternion VecQuat(Vec.X, Vec.Y, Vec.Z, FHybridNumber(0));
        FHybridQuaternion Result = (*this) * VecQuat * Inverse();
        return FHybridVector(Result.X, Result.Y, Result.Z);
    }

    // Comparison operators
    FORCEINLINE bool operator==(const FHybridQuaternion& Other) const
    {
        return X == Other.X && Y == Other.Y && Z == Other.Z && W == Other.W;
    }

    FORCEINLINE bool operator!=(const FHybridQuaternion& Other) const
    {
        return !(*this == Other);
    }

    // NetSerialize for replication
    FORCEINLINE bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
    {
        bool SuccessX, SuccessY, SuccessZ, SuccessW;
        X.NetSerialize(Ar, Map, SuccessX);
        Y.NetSerialize(Ar, Map, SuccessY);
        Z.NetSerialize(Ar, Map, SuccessZ);
        W.NetSerialize(Ar, Map, SuccessW);
        bOutSuccess = SuccessX && SuccessY && SuccessZ && SuccessW;
        return bOutSuccess;
    }
};

// NetSerialize trait
template<>
struct TStructOpsTypeTraits<FHybridQuaternion> : public TStructOpsTypeTraitsBase2<FHybridQuaternion>
{
    enum { WithNetSerializer = true, WithCopy = true };
};
