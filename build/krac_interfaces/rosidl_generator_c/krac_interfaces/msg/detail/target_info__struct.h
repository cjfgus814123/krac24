// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from krac_interfaces:msg/TargetInfo.idl
// generated code does not contain a copyright notice

#ifndef KRAC_INTERFACES__MSG__DETAIL__TARGET_INFO__STRUCT_H_
#define KRAC_INTERFACES__MSG__DETAIL__TARGET_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'target_type'
#include "rosidl_runtime_c/string.h"
// Member 'location_xyz'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/TargetInfo in the package krac_interfaces.
typedef struct krac_interfaces__msg__TargetInfo
{
  std_msgs__msg__Header header;
  /// 인식 성공 여부
  bool detected;
  /// "survivor" or "marker_v"
  rosidl_runtime_c__String target_type;
  /// 영상 내 X 좌표 (-1.0 ~ 1.0)
  float image_x;
  /// 영상 내 Y 좌표 (-1.0 ~ 1.0)
  float image_y;
  /// 타겟까지의 거리 (m)
  float distance;
  /// 3차원 좌표 (상대 좌표)
  rosidl_runtime_c__float__Sequence location_xyz;
} krac_interfaces__msg__TargetInfo;

// Struct for a sequence of krac_interfaces__msg__TargetInfo.
typedef struct krac_interfaces__msg__TargetInfo__Sequence
{
  krac_interfaces__msg__TargetInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} krac_interfaces__msg__TargetInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // KRAC_INTERFACES__MSG__DETAIL__TARGET_INFO__STRUCT_H_
