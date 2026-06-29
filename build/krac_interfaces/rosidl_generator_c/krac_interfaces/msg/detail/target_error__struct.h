// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from krac_interfaces:msg/TargetError.idl
// generated code does not contain a copyright notice

#ifndef KRAC_INTERFACES__MSG__DETAIL__TARGET_ERROR__STRUCT_H_
#define KRAC_INTERFACES__MSG__DETAIL__TARGET_ERROR__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/TargetError in the package krac_interfaces.
typedef struct krac_interfaces__msg__TargetError
{
  bool is_detected;
  float pixel_err_x;
  float pixel_err_y;
  float yaw_err_rad;
} krac_interfaces__msg__TargetError;

// Struct for a sequence of krac_interfaces__msg__TargetError.
typedef struct krac_interfaces__msg__TargetError__Sequence
{
  krac_interfaces__msg__TargetError * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} krac_interfaces__msg__TargetError__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // KRAC_INTERFACES__MSG__DETAIL__TARGET_ERROR__STRUCT_H_
