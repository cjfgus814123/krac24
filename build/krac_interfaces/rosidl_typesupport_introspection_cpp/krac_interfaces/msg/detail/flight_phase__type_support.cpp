// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from krac_interfaces:msg/FlightPhase.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "krac_interfaces/msg/detail/flight_phase__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace krac_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void FlightPhase_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) krac_interfaces::msg::FlightPhase(_init);
}

void FlightPhase_fini_function(void * message_memory)
{
  auto typed_message = static_cast<krac_interfaces::msg::FlightPhase *>(message_memory);
  typed_message->~FlightPhase();
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember FlightPhase_message_member_array[1] = {
  {
    "current_phase",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(krac_interfaces::msg::FlightPhase, current_phase),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers FlightPhase_message_members = {
  "krac_interfaces::msg",  // message namespace
  "FlightPhase",  // message name
  1,  // number of fields
  sizeof(krac_interfaces::msg::FlightPhase),
  FlightPhase_message_member_array,  // message members
  FlightPhase_init_function,  // function to initialize message memory (memory has to be allocated)
  FlightPhase_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t FlightPhase_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &FlightPhase_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace krac_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<krac_interfaces::msg::FlightPhase>()
{
  return &::krac_interfaces::msg::rosidl_typesupport_introspection_cpp::FlightPhase_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, krac_interfaces, msg, FlightPhase)() {
  return &::krac_interfaces::msg::rosidl_typesupport_introspection_cpp::FlightPhase_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
