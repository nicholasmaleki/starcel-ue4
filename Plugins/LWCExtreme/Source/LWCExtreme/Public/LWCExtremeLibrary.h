#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FHybridNumber.h"
#include "FHybridVector.h"
#include "FHybridQuaternion.h"
#include "FHybridTransform.h"
#include "LWCExtremeLibrary.generated.h"

UCLASS()
class LWCEXTREME_API ULWCExtremeLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:

    // -------------------------------
    // FHybridNumber math
    // -------------------------------
    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Math")
        static FHybridNumber Sqrt(const FHybridNumber& Num) { return Num.Sqrt(); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Math")
        static FHybridNumber Ln(const FHybridNumber& Num) { return Num.Ln(); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Math")
        static FHybridNumber Exp(const FHybridNumber& Num) { return Num.Exp(); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Math")
        static FHybridNumber Sin(const FHybridNumber& Num) { return Num.Sin(); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Math")
        static FHybridNumber Cos(const FHybridNumber& Num) { return Num.Cos(); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Math")
        static FHybridNumber Tan(const FHybridNumber& Num) { return Num.Tan(); }

    // -------------------------------
    // FHybridVector math
    // -------------------------------
    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Vector")
        static FHybridNumber VectorDot(const FHybridVector& A, const FHybridVector& B) { return A.Dot(B); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Vector")
        static FHybridVector VectorCross(const FHybridVector& A, const FHybridVector& B) { return A.Cross(B); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Vector")
        static FHybridVector VectorAdd(const FHybridVector& A, const FHybridVector& B) { return A + B; }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Vector")
        static FHybridVector VectorSubtract(const FHybridVector& A, const FHybridVector& B) { return A - B; }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Vector")
        static FHybridVector VectorScale(const FHybridVector& Vec, const FHybridNumber& Scalar) { return Vec * Scalar; }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Vector")
        static FHybridVector VectorComponentScale(const FHybridVector& Vec, const FHybridVector& ScaleVec) { return Vec.Scale(ScaleVec); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Vector")
        static FHybridVector VectorCombine(const FHybridVector& A, const FHybridVector& B, const FHybridVector& C) { return FHybridVector::Combine(A, B, C); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Vector")
        static FHybridNumber VectorSize(const FHybridVector& Vec) { return Vec.Size(); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Vector")
        static FHybridVector VectorNormalize(const FHybridVector& Vec) { return Vec.GetSafeNormal(); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Vector")
        static FHybridVector VectorLerp(const FHybridVector& A, const FHybridVector& B, const FHybridNumber& Alpha) { return A * (FHybridNumber(1) - Alpha) + B * Alpha; }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Vector")
        static FHybridNumber VectorDistance(const FHybridVector& A, const FHybridVector& B) { return A.DistanceTo(B); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Vector")
        static FHybridNumber VectorDistanceSquared(const FHybridVector& A, const FHybridVector& B) { return A.DistanceSquared(B); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Vector")
        static FHybridVector VectorProjectOn(const FHybridVector& Vec, const FHybridVector& Target) { return Vec.ProjectOnVector(Target); }

    // -------------------------------
    // FHybridQuaternion math
    // -------------------------------
    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Quaternion")
        static FHybridQuaternion QuatMultiply(const FHybridQuaternion& A, const FHybridQuaternion& B) { return A * B; }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Quaternion")
        static FHybridQuaternion QuatAdd(const FHybridQuaternion& A, const FHybridQuaternion& B) { return A + B; }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Quaternion")
        static FHybridQuaternion QuatSubtract(const FHybridQuaternion& A, const FHybridQuaternion& B) { return A - B; }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Quaternion")
        static FHybridQuaternion QuatScalarMultiply(const FHybridQuaternion& Quat, const FHybridNumber& Scalar) { return Quat * Scalar; }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Quaternion")
        static FHybridQuaternion QuatNormalize(const FHybridQuaternion& Quat) { return Quat.Normalize(); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Quaternion")
        static FHybridQuaternion QuatConjugate(const FHybridQuaternion& Quat) { return Quat.Conjugate(); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Quaternion")
        static FHybridQuaternion QuatInverse(const FHybridQuaternion& Quat) { return Quat.Inverse(); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Quaternion")
        static FHybridQuaternion QuatSlerp(const FHybridQuaternion& From, const FHybridQuaternion& To, const FHybridNumber& Alpha) { return From.Slerp(To, Alpha); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Quaternion")
        static FHybridVector QuatRotateVector(const FHybridQuaternion& Quat, const FHybridVector& Vec) { return Quat.RotateVector(Vec); }

    // -------------------------------
    // FHybridTransform math
    // -------------------------------
    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Transform")
        static FHybridTransform TransformMultiply(const FHybridTransform& A, const FHybridTransform& B) { return A * B; }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Transform")
        static FHybridTransform TransformInverse(const FHybridTransform& T) { return T.Inverse(); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Transform")
        static FHybridVector TransformPosition(const FHybridTransform& T, const FHybridVector& Point) { return T.TransformPosition(Point); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Transform")
        static FHybridVector TransformVector(const FHybridTransform& T, const FHybridVector& Vec) { return T.TransformVector(Vec); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Transform")
        static FHybridVector TransformGetLocation(const FHybridTransform& T) { return T.GetLocation(); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Transform")
        static FHybridQuaternion TransformGetRotation(const FHybridTransform& T) { return T.GetRotation(); }

    UFUNCTION(BlueprintPure, Category = "LWCExtreme|Transform")
        static FHybridVector TransformGetScale(const FHybridTransform& T) { return T.GetScale(); }
};
