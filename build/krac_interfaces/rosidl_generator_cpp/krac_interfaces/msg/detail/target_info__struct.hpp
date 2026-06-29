// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from krac_interfaces:msg/TargetInfo.idl
// generated code does not contain a copyright notice

#ifndef KRAC_INTERFACES__MSG__DETAIL__TARGET_INFO__STRUCT_HPP_
#define KRAC_INTERFACES__MSG__DETAIL__TARGET_INFO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__krac_interfaces__msg__TargetInfo __attribute__((deprecated))
#else
# define DEPRECATED__krac_interfaces__msg__TargetInfo __declspec(deprecated)
#endif

namespace krac_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TargetInfo_
{
  using Type = TargetInfo_<ContainerAllocator>;

  explicit TargetInfo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->detected = false;
      this->target_type = "";
      this->image_x = 0.0f;
      this->image_y = 0.0f;
      this->distance = 0.0f;
    }
  }

  explicit TargetInfo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    target_type(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->detected = false;
      this->target_type = "";
      this->image_x = 0.0f;
      this->image_y = 0.0f;
      this->distance = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _detected_type =
    bool;
  _detected_type detected;
  using _target_type_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _target_type_type target_type;
  using _image_x_type =
    float;
  _image_x_type image_x;
  using _image_y_type =
    float;
  _image_y_type image_y;
  using _distance_type =
    float;
  _distance_type distance;
  using _location_xyz_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _location_xyz_type location_xyz;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__detected(
    const bool & _arg)
  {
    this->detected = _arg;
    return *this;
  }
  Type & set__target_type(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->target_type = _arg;
    return *this;
  }
  Type & set__image_x(
    const float & _arg)
  {
    this->image_x = _arg;
    return *this;
  }
  Type & set__image_y(
    const float & _arg)
  {
    this->image_y = _arg;
    return *this;
  }
  Type & set__distance(
    const float & _arg)
  {
    this->distance = _arg;
    return *this;
  }
  Type & set__location_xyz(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->location_xyz = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    krac_interfaces::msg::TargetInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const krac_interfaces::msg::TargetInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<krac_interfaces::msg::TargetInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<krac_interfaces::msg::TargetInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      krac_interfaces::msg::TargetInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<krac_interfaces::msg::TargetInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      krac_interfaces::msg::TargetInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<krac_interfaces::msg::TargetInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<krac_interfaces::msg::TargetInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<krac_interfaces::msg::TargetInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__krac_interfaces__msg__TargetInfo
    std::shared_ptr<krac_interfaces::msg::TargetInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__krac_interfaces__msg__TargetInfo
    std::shared_ptr<krac_interfaces::msg::TargetInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TargetInfo_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->detected != other.detected) {
      return false;
    }
    if (this->target_type != other.target_type) {
      return false;
    }
    if (this->image_x != other.image_x) {
      return false;
    }
    if (this->image_y != other.image_y) {
      return false;
    }
    if (this->distance != other.distance) {
      return false;
    }
    if (this->location_xyz != other.location_xyz) {
      return false;
    }
    return true;
  }
  bool operator!=(const TargetInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TargetInfo_

// alias to use template instance with default allocator
using TargetInfo =
  krac_interfaces::msg::TargetInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace krac_interfaces

#endif  // KRAC_INTERFACES__MSG__DETAIL__TARGET_INFO__STRUCT_HPP_
