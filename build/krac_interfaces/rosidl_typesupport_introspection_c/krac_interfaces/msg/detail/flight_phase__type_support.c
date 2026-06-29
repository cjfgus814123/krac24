// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from krac_interfaces:msg/FlightPhase.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "krac_interfaces/msg/detail/flight_phase__rosidl_typesupport_introspection_c.h"
#include "krac_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "krac_interfaces/msg/detail/flight_phase__functions.h"
#include "krac_interfaces/msg/detail/flight_phase__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void krac_interfaces__msg__FlightPhase__rosidl_typesupport_introspection_c__FlightPhase_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  krac_interfaces__msg__FlightPhase__init(message_memory);
}

void krac_interfaces__msg__FlightPhase__rosidl_typesupport_introspection_c__FlightPhase_fini_function(void * message_memory)
{
  krac_interfaces__msg__FlightPhase__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember krac_interfaces__msg__FlightPhase__rosidl_typesupport_introspection_c__FlightPhase_message_member_array[1] = {
  {
    "current_phase",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(krac_interfaces__msg__FlightPhase, current_phase),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers krac_interfaces__msg__FlightPhase__rosidl_typesupport_introspection_c__FlightPhase_message_members = {
  "krac_interfaces__msg",  // message namespace
  "FlightPhase",  // message name
  1,  // number of fields
  sizeof(krac_interfaces__msg__FlightPhase),
  krac_interfaces__msg__FlightPhase__rosidl_typesupport_introspection_c__FlightPhase_message_member_array,  // message members
  krac_interfaces__msg__FlightPhase__rosidl_typesupport_introspection_c__FlightPhase_init_function,  // function to initialize message memory (memory has to be allocated)
  krac_interfaces__msg__FlightPhase__rosidl_typesupport_introspection_c__FlightPhase_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t krac_interfaces__msg__FlightPhase__rosidl_typesupport_introspection_c__FlightPhase_message_type_support_handle = {
  0,
  &krac_interfaces__msg__FlightPhase__rosidl_typesupport_introspection_c__FlightPhase_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_krac_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, krac_interfaces, msg, FlightPhase)() {
  if (!krac_interfaces__msg__FlightPhase__rosidl_typesupport_introspection_c__FlightPhase_message_type_support_handle.typesupport_identifier) {
    krac_interfaces__msg__FlightPhase__rosidl_typesupport_introspection_c__FlightPhase_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &krac_interfaces__msg__FlightPhase__rosidl_typesupport_introspection_c__FlightPhase_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
