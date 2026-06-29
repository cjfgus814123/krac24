// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from krac_interfaces:msg/TargetInfo.idl
// generated code does not contain a copyright notice

#ifndef KRAC_INTERFACES__MSG__DETAIL__TARGET_INFO__BUILDER_HPP_
#define KRAC_INTERFACES__MSG__DETAIL__TARGET_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "krac_interfaces/msg/detail/target_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace krac_interfaces
{

namespace msg
{

namespace builder
{

class Init_TargetInfo_location_xyz
{
public:
  explicit Init_TargetInfo_location_xyz(::krac_interfaces::msg::TargetInfo & msg)
  : msg_(msg)
  {}
  ::krac_interfaces::msg::TargetInfo location_xyz(::krac_interfaces::msg::TargetInfo::_location_xyz_type arg)
  {
    msg_.location_xyz = std::move(arg);
    return std::move(msg_);
  }

private:
  ::krac_interfaces::msg::TargetInfo msg_;
};

class Init_TargetInfo_distance
{
public:
  explicit Init_TargetInfo_distance(::krac_interfaces::msg::TargetInfo & msg)
  : msg_(msg)
  {}
  Init_TargetInfo_location_xyz distance(::krac_interfaces::msg::TargetInfo::_distance_type arg)
  {
    msg_.distance = std::move(arg);
    return Init_TargetInfo_location_xyz(msg_);
  }

private:
  ::krac_interfaces::msg::TargetInfo msg_;
};

class Init_TargetInfo_image_y
{
public:
  explicit Init_TargetInfo_image_y(::krac_interfaces::msg::TargetInfo & msg)
  : msg_(msg)
  {}
  Init_TargetInfo_distance image_y(::krac_interfaces::msg::TargetInfo::_image_y_type arg)
  {
    msg_.image_y = std::move(arg);
    return Init_TargetInfo_distance(msg_);
  }

private:
  ::krac_interfaces::msg::TargetInfo msg_;
};

class Init_TargetInfo_image_x
{
public:
  explicit Init_TargetInfo_image_x(::krac_interfaces::msg::TargetInfo & msg)
  : msg_(msg)
  {}
  Init_TargetInfo_image_y image_x(::krac_interfaces::msg::TargetInfo::_image_x_type arg)
  {
    msg_.image_x = std::move(arg);
    return Init_TargetInfo_image_y(msg_);
  }

private:
  ::krac_interfaces::msg::TargetInfo msg_;
};

class Init_TargetInfo_target_type
{
public:
  explicit Init_TargetInfo_target_type(::krac_interfaces::msg::TargetInfo & msg)
  : msg_(msg)
  {}
  Init_TargetInfo_image_x target_type(::krac_interfaces::msg::TargetInfo::_target_type_type arg)
  {
    msg_.target_type = std::move(arg);
    return Init_TargetInfo_image_x(msg_);
  }

private:
  ::krac_interfaces::msg::TargetInfo msg_;
};

class Init_TargetInfo_detected
{
public:
  explicit Init_TargetInfo_detected(::krac_interfaces::msg::TargetInfo & msg)
  : msg_(msg)
  {}
  Init_TargetInfo_target_type detected(::krac_interfaces::msg::TargetInfo::_detected_type arg)
  {
    msg_.detected = std::move(arg);
    return Init_TargetInfo_target_type(msg_);
  }

private:
  ::krac_interfaces::msg::TargetInfo msg_;
};

class Init_TargetInfo_header
{
public:
  Init_TargetInfo_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_TargetInfo_detected header(::krac_interfaces::msg::TargetInfo::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_TargetInfo_detected(msg_);
  }

private:
  ::krac_interfaces::msg::TargetInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::krac_interfaces::msg::TargetInfo>()
{
  return krac_interfaces::msg::builder::Init_TargetInfo_header();
}

}  // namespace krac_interfaces

#endif  // KRAC_INTERFACES__MSG__DETAIL__TARGET_INFO__BUILDER_HPP_
