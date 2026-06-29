// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from krac_interfaces:msg/TargetError.idl
// generated code does not contain a copyright notice

#ifndef KRAC_INTERFACES__MSG__DETAIL__TARGET_ERROR__BUILDER_HPP_
#define KRAC_INTERFACES__MSG__DETAIL__TARGET_ERROR__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "krac_interfaces/msg/detail/target_error__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace krac_interfaces
{

namespace msg
{

namespace builder
{

class Init_TargetError_yaw_err_rad
{
public:
  explicit Init_TargetError_yaw_err_rad(::krac_interfaces::msg::TargetError & msg)
  : msg_(msg)
  {}
  ::krac_interfaces::msg::TargetError yaw_err_rad(::krac_interfaces::msg::TargetError::_yaw_err_rad_type arg)
  {
    msg_.yaw_err_rad = std::move(arg);
    return std::move(msg_);
  }

private:
  ::krac_interfaces::msg::TargetError msg_;
};

class Init_TargetError_pixel_err_y
{
public:
  explicit Init_TargetError_pixel_err_y(::krac_interfaces::msg::TargetError & msg)
  : msg_(msg)
  {}
  Init_TargetError_yaw_err_rad pixel_err_y(::krac_interfaces::msg::TargetError::_pixel_err_y_type arg)
  {
    msg_.pixel_err_y = std::move(arg);
    return Init_TargetError_yaw_err_rad(msg_);
  }

private:
  ::krac_interfaces::msg::TargetError msg_;
};

class Init_TargetError_pixel_err_x
{
public:
  explicit Init_TargetError_pixel_err_x(::krac_interfaces::msg::TargetError & msg)
  : msg_(msg)
  {}
  Init_TargetError_pixel_err_y pixel_err_x(::krac_interfaces::msg::TargetError::_pixel_err_x_type arg)
  {
    msg_.pixel_err_x = std::move(arg);
    return Init_TargetError_pixel_err_y(msg_);
  }

private:
  ::krac_interfaces::msg::TargetError msg_;
};

class Init_TargetError_is_detected
{
public:
  Init_TargetError_is_detected()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TargetError_pixel_err_x is_detected(::krac_interfaces::msg::TargetError::_is_detected_type arg)
  {
    msg_.is_detected = std::move(arg);
    return Init_TargetError_pixel_err_x(msg_);
  }

private:
  ::krac_interfaces::msg::TargetError msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::krac_interfaces::msg::TargetError>()
{
  return krac_interfaces::msg::builder::Init_TargetError_is_detected();
}

}  // namespace krac_interfaces

#endif  // KRAC_INTERFACES__MSG__DETAIL__TARGET_ERROR__BUILDER_HPP_
