// NOLINT: This file starts with a BOM since it contain non-ASCII characters
// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from krac_interfaces:msg/FlightPhase.idl
// generated code does not contain a copyright notice

#ifndef KRAC_INTERFACES__MSG__DETAIL__FLIGHT_PHASE__STRUCT_H_
#define KRAC_INTERFACES__MSG__DETAIL__FLIGHT_PHASE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'READY'.
enum
{
  krac_interfaces__msg__FlightPhase__READY = 0
};

/// Constant 'TAKEOFF_VERTICAL'.
/**
  * ① 버티포트 수직 이륙
 */
enum
{
  krac_interfaces__msg__FlightPhase__TAKEOFF_VERTICAL = 1
};

/// Constant 'HOVERING_WP1'.
/**
  * ② WP1 이동 및 호버링
 */
enum
{
  krac_interfaces__msg__FlightPhase__HOVERING_WP1 = 2
};

/// Constant 'TRANSITION_TO_FW'.
/**
  * ③ 전진 비행 및 고정익 천이 (WP2 이동 중)
 */
enum
{
  krac_interfaces__msg__FlightPhase__TRANSITION_TO_FW = 3
};

/// Constant 'CRUISE_WP2_TO_WP3'.
/**
  * ④ WP2 -> WP3 (고정익)
 */
enum
{
  krac_interfaces__msg__FlightPhase__CRUISE_WP2_TO_WP3 = 4
};

/// Constant 'CRUISE_WP3_TO_WP4'.
/**
  * ⑤ WP3 -> WP4 (고정익)
 */
enum
{
  krac_interfaces__msg__FlightPhase__CRUISE_WP3_TO_WP4 = 5
};

/// Constant 'CRUISE_WP4_TO_WP2'.
/**
  * ⑥ WP4 -> WP2 (고정익)
 */
enum
{
  krac_interfaces__msg__FlightPhase__CRUISE_WP4_TO_WP2 = 6
};

/// Constant 'TRANSITION_TO_MC'.
/**
  * ⑦ 조난자 위치로 감속 및 회전익 천이
 */
enum
{
  krac_interfaces__msg__FlightPhase__TRANSITION_TO_MC = 7
};

/// Constant 'RESCUE_OPERATION'.
/**
  * ⑧ 조난자 구조 (정밀 접근 및 구조)
 */
enum
{
  krac_interfaces__msg__FlightPhase__RESCUE_OPERATION = 8
};

/// Constant 'DROP_RESCUEE'.
/**
  * ⑨ 하기 위치 이동 및 하기
 */
enum
{
  krac_interfaces__msg__FlightPhase__DROP_RESCUEE = 9
};

/// Constant 'LANDING_VERTICAL'.
/**
  * ⑩ 버티포트 수직 착륙
 */
enum
{
  krac_interfaces__msg__FlightPhase__LANDING_VERTICAL = 10
};

/// Constant 'MISSION_COMPLETE'.
enum
{
  krac_interfaces__msg__FlightPhase__MISSION_COMPLETE = 11
};

/// Struct defined in msg/FlightPhase in the package krac_interfaces.
/**
  * Mission Phases based on KRAC Rulebook
 */
typedef struct krac_interfaces__msg__FlightPhase
{
  uint8_t current_phase;
} krac_interfaces__msg__FlightPhase;

// Struct for a sequence of krac_interfaces__msg__FlightPhase.
typedef struct krac_interfaces__msg__FlightPhase__Sequence
{
  krac_interfaces__msg__FlightPhase * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} krac_interfaces__msg__FlightPhase__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // KRAC_INTERFACES__MSG__DETAIL__FLIGHT_PHASE__STRUCT_H_
