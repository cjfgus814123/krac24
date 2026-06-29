// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from krac_interfaces:msg/FlightPhase.idl
// generated code does not contain a copyright notice

#ifndef KRAC_INTERFACES__MSG__DETAIL__FLIGHT_PHASE__STRUCT_HPP_
#define KRAC_INTERFACES__MSG__DETAIL__FLIGHT_PHASE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__krac_interfaces__msg__FlightPhase __attribute__((deprecated))
#else
# define DEPRECATED__krac_interfaces__msg__FlightPhase __declspec(deprecated)
#endif

namespace krac_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct FlightPhase_
{
  using Type = FlightPhase_<ContainerAllocator>;

  explicit FlightPhase_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->current_phase = 0;
    }
  }

  explicit FlightPhase_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->current_phase = 0;
    }
  }

  // field types and members
  using _current_phase_type =
    uint8_t;
  _current_phase_type current_phase;

  // setters for named parameter idiom
  Type & set__current_phase(
    const uint8_t & _arg)
  {
    this->current_phase = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t READY =
    0u;
  static constexpr uint8_t TAKEOFF_VERTICAL =
    1u;
  static constexpr uint8_t HOVERING_WP1 =
    2u;
  static constexpr uint8_t TRANSITION_TO_FW =
    3u;
  static constexpr uint8_t CRUISE_WP2_TO_WP3 =
    4u;
  static constexpr uint8_t CRUISE_WP3_TO_WP4 =
    5u;
  static constexpr uint8_t CRUISE_WP4_TO_WP2 =
    6u;
  static constexpr uint8_t TRANSITION_TO_MC =
    7u;
  static constexpr uint8_t RESCUE_OPERATION =
    8u;
  static constexpr uint8_t DROP_RESCUEE =
    9u;
  static constexpr uint8_t LANDING_VERTICAL =
    10u;
  static constexpr uint8_t MISSION_COMPLETE =
    11u;

  // pointer types
  using RawPtr =
    krac_interfaces::msg::FlightPhase_<ContainerAllocator> *;
  using ConstRawPtr =
    const krac_interfaces::msg::FlightPhase_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<krac_interfaces::msg::FlightPhase_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<krac_interfaces::msg::FlightPhase_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      krac_interfaces::msg::FlightPhase_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<krac_interfaces::msg::FlightPhase_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      krac_interfaces::msg::FlightPhase_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<krac_interfaces::msg::FlightPhase_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<krac_interfaces::msg::FlightPhase_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<krac_interfaces::msg::FlightPhase_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__krac_interfaces__msg__FlightPhase
    std::shared_ptr<krac_interfaces::msg::FlightPhase_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__krac_interfaces__msg__FlightPhase
    std::shared_ptr<krac_interfaces::msg::FlightPhase_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const FlightPhase_ & other) const
  {
    if (this->current_phase != other.current_phase) {
      return false;
    }
    return true;
  }
  bool operator!=(const FlightPhase_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct FlightPhase_

// alias to use template instance with default allocator
using FlightPhase =
  krac_interfaces::msg::FlightPhase_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t FlightPhase_<ContainerAllocator>::READY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t FlightPhase_<ContainerAllocator>::TAKEOFF_VERTICAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t FlightPhase_<ContainerAllocator>::HOVERING_WP1;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t FlightPhase_<ContainerAllocator>::TRANSITION_TO_FW;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t FlightPhase_<ContainerAllocator>::CRUISE_WP2_TO_WP3;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t FlightPhase_<ContainerAllocator>::CRUISE_WP3_TO_WP4;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t FlightPhase_<ContainerAllocator>::CRUISE_WP4_TO_WP2;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t FlightPhase_<ContainerAllocator>::TRANSITION_TO_MC;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t FlightPhase_<ContainerAllocator>::RESCUE_OPERATION;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t FlightPhase_<ContainerAllocator>::DROP_RESCUEE;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t FlightPhase_<ContainerAllocator>::LANDING_VERTICAL;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t FlightPhase_<ContainerAllocator>::MISSION_COMPLETE;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace krac_interfaces

#endif  // KRAC_INTERFACES__MSG__DETAIL__FLIGHT_PHASE__STRUCT_HPP_
