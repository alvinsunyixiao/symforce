//  ----------------------------------------------------------------------------
// This file was autogenerated by symforce. Do NOT modify by hand.
// -----------------------------------------------------------------------------

#include "./storage_ops.h"

namespace geo {
namespace pose3 {

template <typename ScalarType>
void StorageOps<ScalarType>::ToStorage(const geo::Pose3<ScalarType>& a, ScalarType* out) {
  assert(out != nullptr);
  std::copy_n(a.Data().data(), a.StorageDim(), out);
}

template <typename ScalarType>
geo::Pose3<ScalarType> StorageOps<ScalarType>::FromStorage(const ScalarType* data) {
  assert(data != nullptr);
  return geo::Pose3<ScalarType>(
    Eigen::Map<const typename geo::Pose3<ScalarType>::DataVec>(data));
}

}  // namespace pose3
}  // namespace geo


// Explicit instantiation
template struct geo::pose3::StorageOps<double>;
template struct geo::pose3::StorageOps<float>;
