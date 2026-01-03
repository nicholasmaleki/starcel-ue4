#include "LargeTensorMPFRDataObject.h"
#include "Misc/Crc.h"
#include <string>
#include <vector>
#include <ios>

/** Set the tensor and build replication chunks */
void ULargeTensorMPFRDataObject::SetTensor(const xt::xarray<mpfr_float>& InTensor)
{
    Tensor = InTensor;

    // Serialize tensor to bytes and build replication chunks
    TArray<uint8> Bytes;
    SerializeToBytes(Bytes);
    BuildChunks(); // parent class method
}

/** Get the tensor */
const xt::xarray<mpfr_float>& ULargeTensorMPFRDataObject::GetTensor() const
{
    return Tensor;
}

/** Serialize tensor to bytes */
void ULargeTensorMPFRDataObject::SerializeToBytes(TArray<uint8>& OutBytes) const
{
    OutBytes.Empty();

    // Serialize shape
    auto shape = Tensor.shape();
    int32 Rank = static_cast<int32>(shape.size());
    OutBytes.Append(reinterpret_cast<const uint8*>(&Rank), sizeof(int32));
    for (auto dim : shape)
    {
        int32 Dim = static_cast<int32>(dim);
        OutBytes.Append(reinterpret_cast<const uint8*>(&Dim), sizeof(int32));
    }

    // Serialize each mpfr_float to string
    for (auto it = Tensor.begin(); it != Tensor.end(); ++it)
    {
        std::string s = it->str(0, std::ios::scientific); // full precision
        int32 Len = static_cast<int32>(s.size());
        OutBytes.Append(reinterpret_cast<const uint8*>(&Len), sizeof(int32));
        OutBytes.Append(reinterpret_cast<const uint8*>(s.data()), Len);
    }
}

/** Deserialize tensor from bytes */
void ULargeTensorMPFRDataObject::DeserializeFromBytes(const TArray<uint8>& InBytes)
{
    Tensor = xt::xarray<mpfr_float>(); // reset tensor

    int32 Offset = 0;

    auto ReadInt32 = [&](int32& Out)
    {
        check(Offset + sizeof(int32) <= InBytes.Num());
        Out = *reinterpret_cast<const int32*>(InBytes.GetData() + Offset);
        Offset += sizeof(int32);
    };

    // Read rank and shape
    int32 Rank;
    ReadInt32(Rank);
    std::vector<size_t> shape(Rank);
    for (int32 i = 0; i < Rank; ++i)
    {
        int32 dim;
        ReadInt32(dim);
        shape[i] = static_cast<size_t>(dim);
    }

    Tensor.resize(shape);

    // Read elements
    for (auto it = Tensor.begin(); it != Tensor.end(); ++it)
    {
        int32 Len;
        ReadInt32(Len);
        check(Offset + Len <= InBytes.Num());
        std::string s(reinterpret_cast<const char*>(InBytes.GetData() + Offset), Len);
        Offset += Len;

        *it = mpfr_float(s);
    }
}
