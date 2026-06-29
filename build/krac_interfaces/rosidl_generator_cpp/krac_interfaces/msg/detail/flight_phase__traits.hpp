// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from krac_interfaces:msg/FlightPhase.idl
// generated code does not contain a copyright notice

#ifndef KRAC_INTERFACES__MSG__DETAIL__FLIGHT_PHASE__TRAITS_HPP_
#define KRAC_INTERFACES__MSG__DETAIL__FLIGHT_PHASE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "krac_interfaces/msg/detail/flight_phase__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace krac_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const FlightPhase & msg,
  std::ostream & out)
{
  out << "{";
  // member: current_phase
  {
    out << "current_phase: ";
    rosidl_generator_traits::value_to_yaml(msg.current_phase, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const FlightPhase & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: current_phase
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_phase: ";
    rosidl_generator_traits::value_to_yaml(msg.current_phase, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const FlightPhase & msg, bool use_flow_style = false)
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
  const krac_interfaces::msg::FlightPhase & msg,
  std::ostream & out, size_t indentation = 0)
{
  krac_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use krac_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const krac_interfaces::msg::FlightPhase & msg)
{
  return krac_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<krac_interfaces::msg::FlightPhase>()
{
  return "krac_interfaces::msg::FlightPhase";
}

template<>
inline const char * name<krac_interfaces::msg::FlightPhase>()
{
  return "krac_interfaces/msg/FlightPhase";
}

template<>
struct has_fixed_size<krac_interfaces::msg::FlightPhase>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<krac_interfaces::msg::FlightPhase>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<krac_interfaces::msg::FlightPhase>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // KRAC_INTERFACES__MSG__DETAIL__FLIGHT_PHASE__TRAITS_HPP_
