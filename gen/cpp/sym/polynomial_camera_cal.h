// -----------------------------------------------------------------------------
// This file was autogenerated by symforce from template:
//     cam_package/CLASS.h.jinja
// Do NOT modify by hand.
// -----------------------------------------------------------------------------

#pragma once

#include <ostream>
#include <random>
#include <vector>

#include <Eigen/Dense>

#include <sym/ops/storage_ops.h>

namespace sym {

/**
 * Autogenerated C++ implementation of <class
 * 'symforce.cam.polynomial_camera_cal.PolynomialCameraCal'>.
 *
 * Polynomial camera model in the style of OpenCV
 *
 * Distortion is a multiplicative factor applied to the image plane coordinates in the camera
 * frame. Mapping between distorted image plane coordinates and image coordinates is done using
 * a standard linear model.
 *
 * The distortion function is a 6th order even polynomial that is a function of the radius of the
 * image plane coordinates::
 *
 *     r = (p_img[0] ** 2 + p_img[1] ** 2) ** 0.5
 *     distorted_weight = 1 + c0 * r^2 + c1 * r^4 + c2 * r^6
 *     uv = p_img * distorted_weight
 */
template <typename ScalarType>
class PolynomialCameraCal {
 public:
  // Typedefs
  using Scalar = ScalarType;
  using Self = PolynomialCameraCal<Scalar>;
  using DataVec = Eigen::Matrix<Scalar, 8, 1>;

  // Construct from focal_length, principal_point, critical_undistorted_radius, and
  // distortion_coeffs.
  PolynomialCameraCal(const Eigen::Matrix<Scalar, 2, 1>& focal_length,
                      const Eigen::Matrix<Scalar, 2, 1>& principal_point,
                      const Scalar critical_undistorted_radius,
                      const Eigen::Matrix<Scalar, 3, 1>& distortion_coeffs)
      : PolynomialCameraCal(
            (Eigen::Matrix<Scalar, sym::StorageOps<Self>::StorageDim(), 1>() << focal_length,
             principal_point, critical_undistorted_radius, distortion_coeffs)
                .finished()) {}

  // Construct from data vec
  explicit PolynomialCameraCal(const DataVec& data) : data_(data) {}

  // Access underlying storage as const
  inline const DataVec& Data() const {
    return data_;
  }

  // --------------------------------------------------------------------------
  // StorageOps concept
  // --------------------------------------------------------------------------

  static constexpr int32_t StorageDim() {
    return sym::StorageOps<Self>::StorageDim();
  }

  void ToStorage(Scalar* const vec) const {
    return sym::StorageOps<Self>::ToStorage(*this, vec);
  }

  static PolynomialCameraCal FromStorage(const Scalar* const vec) {
    return sym::StorageOps<Self>::FromStorage(vec);
  }

  // --------------------------------------------------------------------------
  // Camera model methods
  // --------------------------------------------------------------------------

  /**
   * Return the focal length.
   */
  Eigen::Matrix<Scalar, 2, 1> FocalLength() const;

  /**
   * Return the principal point.
   */
  Eigen::Matrix<Scalar, 2, 1> PrincipalPoint() const;

  /**
   * Project a 3D point in the camera frame into 2D pixel coordinates.
   *
   * Returns:
   *     pixel: (x, y) coordinate in pixels if valid
   *     is_valid: 1 if the operation is within bounds else 0
   */
  Eigen::Matrix<Scalar, 2, 1> PixelFromCameraPoint(const Eigen::Matrix<Scalar, 3, 1>& point,
                                                   const Scalar epsilon,
                                                   Scalar* const is_valid = nullptr) const;

  /**
   * Project a 3D point in the camera frame into 2D pixel coordinates.
   *
   * Return:
   *     pixel: (x, y) coordinate in pixels if valid
   *     is_valid: 1 if the operation is within bounds else 0
   *     pixel_D_cal: Derivative of pixel with respect to intrinsic calibration parameters
   *     pixel_D_point: Derivative of pixel with respect to point
   */
  Eigen::Matrix<Scalar, 2, 1> PixelFromCameraPointWithJacobians(
      const Eigen::Matrix<Scalar, 3, 1>& point, const Scalar epsilon,
      Scalar* const is_valid = nullptr, Eigen::Matrix<Scalar, 2, 7>* const pixel_D_cal = nullptr,
      Eigen::Matrix<Scalar, 2, 3>* const pixel_D_point = nullptr) const;

  // --------------------------------------------------------------------------
  // General Helpers
  // --------------------------------------------------------------------------

  bool IsApprox(const Self& b, const Scalar tol) const {
    // isApprox is multiplicative so we check the norm for the exact zero case
    // https://eigen.tuxfamily.org/dox/classEigen_1_1DenseBase.html#ae8443357b808cd393be1b51974213f9c
    if (b.Data() == DataVec::Zero()) {
      return Data().norm() < tol;
    }

    return Data().isApprox(b.Data(), tol);
  }

  template <typename ToScalar>
  PolynomialCameraCal<ToScalar> Cast() const {
    return PolynomialCameraCal<ToScalar>(Data().template cast<ToScalar>());
  }

  bool operator==(const PolynomialCameraCal& rhs) const {
    return data_ == rhs.Data();
  }

 protected:
  DataVec data_;
};

// Shorthand for scalar types
using PolynomialCameraCald = PolynomialCameraCal<double>;
using PolynomialCameraCalf = PolynomialCameraCal<float>;

// Print definitions
std::ostream& operator<<(std::ostream& os, const PolynomialCameraCal<double>& a);
std::ostream& operator<<(std::ostream& os, const PolynomialCameraCal<float>& a);

}  // namespace sym

// Externs to reduce duplicate instantiation
extern template class sym::PolynomialCameraCal<double>;
extern template class sym::PolynomialCameraCal<float>;

// Concept implementations for this class
#include "./ops/polynomial_camera_cal/group_ops.h"
#include "./ops/polynomial_camera_cal/lie_group_ops.h"
#include "./ops/polynomial_camera_cal/storage_ops.h"
