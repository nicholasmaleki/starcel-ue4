#include "LargeTensor.h"
#pragma push_macro("check")
#undef check
#include <xtensor/containers/xarray.hpp>
#include <xtensor/io/xio.hpp>
#pragma pop_macro("check")

FLargeTensor::FLargeTensor()
{
    Tensor = xt::ones<double>({ 3, 3 }); // simple 3x3 tensor
}

void FLargeTensor::FillWithOnes()
{
    Tensor = xt::ones<double>({ 3, 3 });
}


//// Save Unreal macros
//#ifdef check
//#undef check
//#define RESTORE_CHECK
//#endif
//
//#include "xtensor/xarray.hpp"
//#include "xtensor/xmath.hpp"
//#include "xtensor/xadapt.hpp"
//
//// Restore Unreal macro
//#ifdef RESTORE_CHECK
//#define check(expr) UE_CHECK(expr)  // Or whatever UE uses
//#undef RESTORE_CHECK
//#endif


//#include "LargeTensor.h"
//#include "Net/UnrealNetwork.h"
//THIRD_PARTY_INCLUDES_START
//#pragma push_macro("check")
//#undef check
//#include <xtensor/containers/xarray.hpp>
//#include <xtensor/containers/xtensor.hpp>
//#include <xtensor/containers/xadapt.hpp>
//#include <xtensor/io/xio.hpp>
//#include <xtensor/views/xview.hpp>
//#include <boost/multiprecision/cpp_int.hpp>
//#pragma warning(push)
//#pragma warning(disable : 4146)
//#include <gmp.h>
//#pragma warning(pop)
//#include <mpfr.h>
//#pragma pop_macro("check")
//THIRD_PARTY_INCLUDES_END
//
//void ULargeTensor::SerializeToBytes(TArray<uint8>& Out) const
//{
//    for (auto v : Tensor)
//    {
//        double D = v;
//        Out.Append((uint8*)&D, sizeof(double));
//    }
//}
//
//void ULargeTensor::DeserializeFromBytes(const TArray<uint8>& In)
//{
//    int64 Count = In.Num() / sizeof(double);
//    Tensor = xt::xarray<double>::from_shape({ Count });
//
//    FMemory::Memcpy(Tensor.data(), In.GetData(), In.Num());
//}
//
//void ULargeTensor::UpdateRegion(
//    const TArray<int64>& Start,
//    const TArray<int64>& Extent,
//    const TArray<uint8>& RawData)
//{
//    FLargeTensorRegionUpdate U;
//    U.Start = Start;
//    U.Extent = Extent;
//    U.RawData = RawData;
//    U.Hash = FCrc::MemCrc32(RawData.GetData(), RawData.Num());
//
//    RegionUpdates.Add(U);
//    ApplyRegion(U);
//}
//
//void ULargeTensor::ApplyRegion(const FLargeTensorRegionUpdate& U)
//{
//    xt::xstrided_slice_vector S;
//    for (int32 i = 0; i < U.Start.Num(); ++i)
//        S.push_back(xt::range(U.Start[i], U.Start[i] + U.Extent[i]));
//
//    auto Region = xt::adapt(
//        (double*)U.RawData.GetData(),
//        U.RawData.Num() / sizeof(double),
//        xt::no_ownership(),
//        U.Extent
//    );
//
//    xt::view(Tensor, S) = Region;
//}
