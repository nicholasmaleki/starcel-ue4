#pragma once
#include "CoreMinimal.h"
#include "FHybridVector.h"
#include "FHybridQuaternion.h"
#include "FHybridTransform.generated.h"

USTRUCT(BlueprintType)
struct LWCEXTREME_API FHybridTransform
{
    GENERATED_BODY()

public:
    FHybridVector Location;
    FHybridQuaternion Rotation;
    FHybridVector Scale;

    // Constructors
    FHybridTransform()
        : Location(FHybridNumber(0), FHybridNumber(0), FHybridNumber(0)),
        Rotation(FHybridNumber(0), FHybridNumber(0), FHybridNumber(0), FHybridNumber(1)),
        Scale(FHybridNumber(1), FHybridNumber(1), FHybridNumber(1))
    {}

    FHybridTransform(const FHybridVector& InLocation, const FHybridQuaternion& InRotation, const FHybridVector& InScale)
        : Location(InLocation), Rotation(InRotation), Scale(InScale)
    {}

    // Arithmetic / Transform functions
    FORCEINLINE FHybridTransform operator*(const FHybridTransform& Other) const
    {
        // Combine transforms: scale, rotate, translate
        FHybridVector NewLocation = Rotation.RotateVector(Other.Location * Scale) + Location;
        FHybridQuaternion NewRotation = Rotation * Other.Rotation;
        FHybridVector NewScale = FHybridVector(Scale.X * Other.Scale.X, Scale.Y * Other.Scale.Y, Scale.Z * Other.Scale.Z);
        return FHybridTransform(NewLocation, NewRotation, NewScale);
    }

    FORCEINLINE FHybridTransform Inverse() const
    {
        FHybridVector InvScale(FHybridNumber(1) / Scale.X, FHybridNumber(1) / Scale.Y, FHybridNumber(1) / Scale.Z);
        FHybridQuaternion InvRotation = Rotation.Inverse();
        FHybridVector InvLocation = InvRotation.RotateVector((Location * FHybridVector(-1, -1, -1)) * InvScale);
        return FHybridTransform(InvLocation, InvRotation, InvScale);
    }

    FORCEINLINE FHybridVector TransformPosition(const FHybridVector& Point) const
    {
        return Rotation.RotateVector(Point * Scale) + Location;
    }

    FORCEINLINE FHybridVector TransformVector(const FHybridVector& Vector) const
    {
        return Rotation.RotateVector(Vector * Scale);
    }

    FORCEINLINE FHybridVector GetLocation() const { return Location; }
    FORCEINLINE FHybridQuaternion GetRotation() const { return Rotation; }
    FORCEINLINE FHybridVector GetScale() const { return Scale; }

    // NetSerialize for replication
    FORCEINLINE bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess)
    {
        bool bLoc, bRot, bScale;
        bLoc = Location.NetSerialize(Ar, Map, bLoc);
        bRot = Rotation.NetSerialize(Ar, Map, bRot);
        bScale = Scale.NetSerialize(Ar, Map, bScale);
        bOutSuccess = bLoc && bRot && bScale;
        return bOutSuccess;
    }
};

// NetSerialize trait
template<>
struct TStructOpsTypeTraits<FHybridTransform> : public TStructOpsTypeTraitsBase2<FHybridTransform>
{
    enum { WithNetSerializer = true, WithCopy = true };
};
