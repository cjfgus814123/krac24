// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from krac_interfaces:msg/FlightPhase.idl
// generated code does not contain a copyright notice

#ifndef KRAC_INTERFACES__MSG__DETAIL__FLIGHT_PHASE__BUILDER_HPP_
#define KRAC_INTERFACES__MSG__DETAIL__FLIGHT_PHASE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "krac_interfaces/msg/detail/flight_phase__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace krac_interfaces
{

namespace msg
{

namespace builder
{

class Init_FlightPhase_current_phase
{
public:
  Init_FlightPhase_current_phase()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::krac_interfaces::msg::FlightPhase current_phase(::krac_interfaces::msg::FlightPhase::_current_phase_type arg)
  {
    msg_.current_phase = std::move(arg);
    return std::move(msg_);
  }

private:
  ::krac_interfaces::msg::FlightPhase msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::krac_interfaces::msg::FlightPhase>()
{
  return krac_interfaces::msg::builder::Init_FlightPhase_current_phase();
}

}  // namespace krac_interfaces

#endif  // KRAC_INTERFACES__MSG__DETAIL__FLIGHT_PHASE__BUILDER_HPP_
