// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from krac_interfaces:msg/TargetError.idl
// generated code does not contain a copyright notice
#include "krac_interfaces/msg/detail/target_error__rosidl_typesupport_fastrtps_cpp.hpp"
#include "krac_interfaces/msg/detail/target_error__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace krac_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_krac_interfaces
cdr_serialize(
  const krac_interfaces::msg::TargetError & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: is_detected
  cdr << (ros_message.is_detected ? true : false);
  // Member: pixel_err_x
  cdr << ros_message.pixel_err_x;
  // Member: pixel_err_y
  cdr << ros_message.pixel_err_y;
  // Member: yaw_err_rad
  cdr << ros_message.yaw_err_rad;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_krac_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  krac_interfaces::msg::TargetError & ros_message)
{
  // Member: is_detected
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.is_detected = tmp ? true : false;
  }

  // Member: pixel_err_x
  cdr >> ros_message.pixel_err_x;

  // Member: pixel_err_y
  cdr >> ros_message.pixel_err_y;

  // Member: yaw_err_rad
  cdr >> ros_message.yaw_err_rad;

  return true;
}  // NOLINT(readability/fn_size)

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_krac_interfaces
get_serialized_size(
  const krac_interfaces::msg::TargetError & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: is_detected
  {
    size_t item_size = sizeof(ros_message.is_detected);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: pixel_err_x
  {
    size_t item_size = sizeof(ros_message.pixel_err_x);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: pixel_err_y
  {
    size_t item_size = sizeof(ros_message.pixel_err_y);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: yaw_err_rad
  {
    size_t item_size = sizeof(ros_message.yaw_err_rad);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_krac_interfaces
max_serialized_size_TargetError(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;


  // Member: is_detected
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: pixel_err_x
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: pixel_err_y
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: yaw_err_rad
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = krac_interfaces::msg::TargetError;
    is_plain =
      (
      offsetof(DataType, yaw_err_rad) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _TargetError__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const krac_interfaces::msg::TargetError *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _TargetError__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<krac_interfaces::msg::TargetError *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _TargetError__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const krac_interfaces::msg::TargetError *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _TargetError__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_TargetError(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _TargetError__callbacks = {
  "krac_interfaces::msg",
  "TargetError",
  _TargetError__cdr_serialize,
  _TargetError__cdr_deserialize,
  _TargetError__get_serialized_size,
  _TargetError__max_serialized_size
};

static rosidl_message_type_support_t _TargetError__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_TargetError__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace krac_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_krac_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<krac_interfaces::msg::TargetError>()
{
  return &krac_interfaces::msg::typesupport_fastrtps_cpp::_TargetError__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, krac_interfaces, msg, TargetError)() {
  return &krac_interfaces::msg::typesupport_fastrtps_cpp::_TargetError__handle;
}

#ifdef __cplusplus
}
#endif
