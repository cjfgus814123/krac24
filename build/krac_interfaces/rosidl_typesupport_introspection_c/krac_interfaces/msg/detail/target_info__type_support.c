// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from krac_interfaces:msg/TargetInfo.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "krac_interfaces/msg/detail/target_info__rosidl_typesupport_introspection_c.h"
#include "krac_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "krac_interfaces/msg/detail/target_info__functions.h"
#include "krac_interfaces/msg/detail/target_info__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `target_type`
#include "rosidl_runtime_c/string_functions.h"
// Member `location_xyz`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__TargetInfo_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  krac_interfaces__msg__TargetInfo__init(message_memory);
}

void krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__TargetInfo_fini_function(void * message_memory)
{
  krac_interfaces__msg__TargetInfo__fini(message_memory);
}

size_t krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__size_function__TargetInfo__location_xyz(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__get_const_function__TargetInfo__location_xyz(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__get_function__TargetInfo__location_xyz(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__fetch_function__TargetInfo__location_xyz(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__get_const_function__TargetInfo__location_xyz(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__assign_function__TargetInfo__location_xyz(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__get_function__TargetInfo__location_xyz(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__resize_function__TargetInfo__location_xyz(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__TargetInfo_message_member_array[7] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(krac_interfaces__msg__TargetInfo, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "detected",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(krac_interfaces__msg__TargetInfo, detected),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "target_type",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(krac_interfaces__msg__TargetInfo, target_type),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "image_x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(krac_interfaces__msg__TargetInfo, image_x),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "image_y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(krac_interfaces__msg__TargetInfo, image_y),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "distance",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(krac_interfaces__msg__TargetInfo, distance),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "location_xyz",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(krac_interfaces__msg__TargetInfo, location_xyz),  // bytes offset in struct
    NULL,  // default value
    krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__size_function__TargetInfo__location_xyz,  // size() function pointer
    krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__get_const_function__TargetInfo__location_xyz,  // get_const(index) function pointer
    krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__get_function__TargetInfo__location_xyz,  // get(index) function pointer
    krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__fetch_function__TargetInfo__location_xyz,  // fetch(index, &value) function pointer
    krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__assign_function__TargetInfo__location_xyz,  // assign(index, value) function pointer
    krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__resize_function__TargetInfo__location_xyz  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__TargetInfo_message_members = {
  "krac_interfaces__msg",  // message namespace
  "TargetInfo",  // message name
  7,  // number of fields
  sizeof(krac_interfaces__msg__TargetInfo),
  krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__TargetInfo_message_member_array,  // message members
  krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__TargetInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__TargetInfo_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__TargetInfo_message_type_support_handle = {
  0,
  &krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__TargetInfo_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_krac_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, krac_interfaces, msg, TargetInfo)() {
  krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__TargetInfo_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  if (!krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__TargetInfo_message_type_support_handle.typesupport_identifier) {
    krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__TargetInfo_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &krac_interfaces__msg__TargetInfo__rosidl_typesupport_introspection_c__TargetInfo_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
