// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from krac_interfaces:msg/TargetInfo.idl
// generated code does not contain a copyright notice

#ifndef KRAC_INTERFACES__MSG__DETAIL__TARGET_INFO__TRAITS_HPP_
#define KRAC_INTERFACES__MSG__DETAIL__TARGET_INFO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "krac_interfaces/msg/detail/target_info__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace krac_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const TargetInfo & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: detected
  {
    out << "detected: ";
    rosidl_generator_traits::value_to_yaml(msg.detected, out);
    out << ", ";
  }

  // member: target_type
  {
    out << "target_type: ";
    rosidl_generator_traits::value_to_yaml(msg.target_type, out);
    out << ", ";
  }

  // member: image_x
  {
    out << "image_x: ";
    rosidl_generator_traits::value_to_yaml(msg.image_x, out);
    out << ", ";
  }

  // member: image_y
  {
    out << "image_y: ";
    rosidl_generator_traits::value_to_yaml(msg.image_y, out);
    out << ", ";
  }

  // member: distance
  {
    out << "distance: ";
    rosidl_generator_traits::value_to_yaml(msg.distance, out);
    out << ", ";
  }

  // member: location_xyz
  {
    if (msg.location_xyz.size() == 0) {
      out << "location_xyz: []";
    } else {
      out << "location_xyz: [";
      size_t pending_items = msg.location_xyz.size();
      for (auto item : msg.location_xyz) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TargetInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: detected
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "detected: ";
    rosidl_generator_traits::value_to_yaml(msg.detected, out);
    out << "\n";
  }

  // member: target_type
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_type: ";
    rosidl_generator_traits::value_to_yaml(msg.target_type, out);
    out << "\n";
  }

  // member: image_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "image_x: ";
    rosidl_generator_traits::value_to_yaml(msg.image_x, out);
    out << "\n";
  }

  // member: image_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "image_y: ";
    rosidl_generator_traits::value_to_yaml(msg.image_y, out);
    out << "\n";
  }

  // member: distance
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "distance: ";
    rosidl_generator_traits::value_to_yaml(msg.distance, out);
    out << "\n";
  }

  // member: location_xyz
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.location_xyz.size() == 0) {
      out << "location_xyz: []\n";
    } else {
      out << "location_xyz:\n";
      for (auto item : msg.location_xyz) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TargetInfo & msg, bool use_flow_style = false)
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
  const krac_interfaces::msg::TargetInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  krac_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use krac_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const krac_interfaces::msg::TargetInfo & msg)
{
  return krac_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<krac_interfaces::msg::TargetInfo>()
{
  return "krac_interfaces::msg::TargetInfo";
}

template<>
inline const char * name<krac_interfaces::msg::TargetInfo>()
{
  return "krac_interfaces/msg/TargetInfo";
}

template<>
struct has_fixed_size<krac_interfaces::msg::TargetInfo>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<krac_interfaces::msg::TargetInfo>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<krac_interfaces::msg::TargetInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // KRAC_INTERFACES__MSG__DETAIL__TARGET_INFO__TRAITS_HPP_
