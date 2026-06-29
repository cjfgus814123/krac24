// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from krac_interfaces:msg/TargetError.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "krac_interfaces/msg/detail/target_error__rosidl_typesupport_introspection_c.h"
#include "krac_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "krac_interfaces/msg/detail/target_error__functions.h"
#include "krac_interfaces/msg/detail/target_error__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void krac_interfaces__msg__TargetError__rosidl_typesupport_introspection_c__TargetError_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  krac_interfaces__msg__TargetError__init(message_memory);
}

void krac_interfaces__msg__TargetError__rosidl_typesupport_introspection_c__TargetError_fini_function(void * message_memory)
{
  krac_interfaces__msg__TargetError__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember krac_interfaces__msg__TargetError__rosidl_typesupport_introspection_c__TargetError_message_member_array[4] = {
  {
    "is_detected",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(krac_interfaces__msg__TargetError, is_detected),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pixel_err_x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(krac_interfaces__msg__TargetError, pixel_err_x),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pixel_err_y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(krac_interfaces__msg__TargetError, pixel_err_y),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "yaw_err_rad",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(krac_interfaces__msg__TargetError, yaw_err_rad),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers krac_interfaces__msg__TargetError__rosidl_typesupport_introspection_c__TargetError_message_members = {
  "krac_interfaces__msg",  // message namespace
  "TargetError",  // message name
  4,  // number of fields
  sizeof(krac_interfaces__msg__TargetError),
  krac_interfaces__msg__TargetError__rosidl_typesupport_introspection_c__TargetError_message_member_array,  // message members
  krac_interfaces__msg__TargetError__rosidl_typesupport_introspection_c__TargetError_init_function,  // function to initialize message memory (memory has to be allocated)
  krac_interfaces__msg__TargetError__rosidl_typesupport_introspection_c__TargetError_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t krac_interfaces__msg__TargetError__rosidl_typesupport_introspection_c__TargetError_message_type_support_handle = {
  0,
  &krac_interfaces__msg__TargetError__rosidl_typesupport_introspection_c__TargetError_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_krac_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, krac_interfaces, msg, TargetError)() {
  if (!krac_interfaces__msg__TargetError__rosidl_typesupport_introspection_c__TargetError_message_type_support_handle.typesupport_identifier) {
    krac_interfaces__msg__TargetError__rosidl_typesupport_introspection_c__TargetError_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &krac_interfaces__msg__TargetError__rosidl_typesupport_introspection_c__TargetError_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
