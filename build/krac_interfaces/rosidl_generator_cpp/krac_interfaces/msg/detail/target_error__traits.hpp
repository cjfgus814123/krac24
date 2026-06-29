// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from krac_interfaces:msg/TargetError.idl
// generated code does not contain a copyright notice

#ifndef KRAC_INTERFACES__MSG__DETAIL__TARGET_ERROR__TRAITS_HPP_
#define KRAC_INTERFACES__MSG__DETAIL__TARGET_ERROR__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "krac_interfaces/msg/detail/target_error__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace krac_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const TargetError & msg,
  std::ostream & out)
{
  out << "{";
  // member: is_detected
  {
    out << "is_detected: ";
    rosidl_generator_traits::value_to_yaml(msg.is_detected, out);
    out << ", ";
  }

  // member: pixel_err_x
  {
    out << "pixel_err_x: ";
    rosidl_generator_traits::value_to_yaml(msg.pixel_err_x, out);
    out << ", ";
  }

  // member: pixel_err_y
  {
    out << "pixel_err_y: ";
    rosidl_generator_traits::value_to_yaml(msg.pixel_err_y, out);
    out << ", ";
  }

  // member: yaw_err_rad
  {
    out << "yaw_err_rad: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw_err_rad, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TargetError & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: is_detected
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "is_detected: ";
    rosidl_generator_traits::value_to_yaml(msg.is_detected, out);
    out << "\n";
  }

  // member: pixel_err_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pixel_err_x: ";
    rosidl_generator_traits::value_to_yaml(msg.pixel_err_x, out);
    out << "\n";
  }

  // member: pixel_err_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pixel_err_y: ";
    rosidl_generator_traits::value_to_yaml(msg.pixel_err_y, out);
    out << "\n";
  }

  // member: yaw_err_rad
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw_err_rad: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw_err_rad, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TargetError & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace krac_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use krac_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const krac_interfaces::msg::TargetError & msg,
  std::ostream & out, size_t indentation = 0)
{
  krac_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use krac_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const krac_interfaces::msg::TargetError & msg)
{
  return krac_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<krac_interfaces::msg::TargetError>()
{
  return "krac_interfaces::msg::TargetError";
}

template<>
inline const char * name<krac_interfaces::msg::TargetError>()
{
  return "krac_interfaces/msg/TargetError";
}

template<>
struct has_fixed_size<krac_interfaces::msg::TargetError>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<krac_interfaces::msg::TargetError>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<krac_interfaces::msg::TargetError>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // KRAC_INTERFACES__MSG__DETAIL__TARGET_ERROR__TRAITS_HPP_
