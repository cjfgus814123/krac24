// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from krac_interfaces:msg/TargetError.idl
// generated code does not contain a copyright notice

#ifndef KRAC_INTERFACES__MSG__DETAIL__TARGET_ERROR__STRUCT_HPP_
#define KRAC_INTERFACES__MSG__DETAIL__TARGET_ERROR__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__krac_interfaces__msg__TargetError __attribute__((deprecated))
#else
# define DEPRECATED__krac_interfaces__msg__TargetError __declspec(deprecated)
#endif

namespace krac_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TargetError_
{
  using Type = TargetError_<ContainerAllocator>;

  explicit TargetError_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->is_detected = false;
      this->pixel_err_x = 0.0f;
      this->pixel_err_y = 0.0f;
      this->yaw_err_rad = 0.0f;
    }
  }

  explicit TargetError_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->is_detected = false;
      this->pixel_err_x = 0.0f;
      this->pixel_err_y = 0.0f;
      this->yaw_err_rad = 0.0f;
    }
  }

  // field types and members
  using _is_detected_type =
    bool;
  _is_detected_type is_detected;
  using _pixel_err_x_type =
    float;
  _pixel_err_x_type pixel_err_x;
  using _pixel_err_y_type =
    float;
  _pixel_err_y_type pixel_err_y;
  using _yaw_err_rad_type =
    float;
  _yaw_err_rad_type yaw_err_rad;

  // setters for named parameter idiom
  Type & set__is_detected(
    const bool & _arg)
  {
    this->is_detected = _arg;
    return *this;
  }
  Type & set__pixel_err_x(
    const float & _arg)
  {
    this->pixel_err_x = _arg;
    return *this;
  }
  Type & set__pixel_err_y(
    const float & _arg)
  {
    this->pixel_err_y = _arg;
    return *this;
  }
  Type & set__yaw_err_rad(
    const float & _arg)
  {
    this->yaw_err_rad = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    krac_interfaces::msg::TargetError_<ContainerAllocator> *;
  using ConstRawPtr =
    const krac_interfaces::msg::TargetError_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<krac_interfaces::msg::TargetError_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<krac_interfaces::msg::TargetError_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      krac_interfaces::msg::TargetError_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<krac_interfaces::msg::TargetError_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      krac_interfaces::msg::TargetError_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<krac_interfaces::msg::TargetError_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<krac_interfaces::msg::TargetError_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<krac_interfaces::msg::TargetError_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__krac_interfaces__msg__TargetError
    std::shared_ptr<krac_interfaces::msg::TargetError_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__krac_interfaces__msg__TargetError
    std::shared_ptr<krac_interfaces::msg::TargetError_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TargetError_ & other) const
  {
    if (this->is_detected != other.is_detected) {
      return false;
    }
    if (this->pixel_err_x != other.pixel_err_x) {
      return false;
    }
    if (this->pixel_err_y != other.pixel_err_y) {
      return false;
    }
    if (this->yaw_err_rad != other.yaw_err_rad) {
      return false;
    }
    return true;
  }
  bool operator!=(const TargetError_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TargetError_

// alias to use template instance with default allocator
using TargetError =
  krac_interfaces::msg::TargetError_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace krac_interfaces

#endif  // KRAC_INTERFACES__MSG__DETAIL__TARGET_ERROR__STRUCT_HPP_
