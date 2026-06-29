// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from krac_interfaces:msg/TargetInfo.idl
// generated code does not contain a copyright notice

#ifndef KRAC_INTERFACES__MSG__DETAIL__TARGET_INFO__FUNCTIONS_H_
#define KRAC_INTERFACES__MSG__DETAIL__TARGET_INFO__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "krac_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "krac_interfaces/msg/detail/target_info__struct.h"

/// Initialize msg/TargetInfo message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * krac_interfaces__msg__TargetInfo
 * )) before or use
 * krac_interfaces__msg__TargetInfo__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
bool
krac_interfaces__msg__TargetInfo__init(krac_interfaces__msg__TargetInfo * msg);

/// Finalize msg/TargetInfo message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
void
krac_interfaces__msg__TargetInfo__fini(krac_interfaces__msg__TargetInfo * msg);

/// Create msg/TargetInfo message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * krac_interfaces__msg__TargetInfo__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
krac_interfaces__msg__TargetInfo *
krac_interfaces__msg__TargetInfo__create();

/// Destroy msg/TargetInfo message.
/**
 * It calls
 * krac_interfaces__msg__TargetInfo__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
void
krac_interfaces__msg__TargetInfo__destroy(krac_interfaces__msg__TargetInfo * msg);

/// Check for msg/TargetInfo message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
bool
krac_interfaces__msg__TargetInfo__are_equal(const krac_interfaces__msg__TargetInfo * lhs, const krac_interfaces__msg__TargetInfo * rhs);

/// Copy a msg/TargetInfo message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
bool
krac_interfaces__msg__TargetInfo__copy(
  const krac_interfaces__msg__TargetInfo * input,
  krac_interfaces__msg__TargetInfo * output);

/// Initialize array of msg/TargetInfo messages.
/**
 * It allocates the memory for the number of elements and calls
 * krac_interfaces__msg__TargetInfo__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
bool
krac_interfaces__msg__TargetInfo__Sequence__init(krac_interfaces__msg__TargetInfo__Sequence * array, size_t size);

/// Finalize array of msg/TargetInfo messages.
/**
 * It calls
 * krac_interfaces__msg__TargetInfo__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
void
krac_interfaces__msg__TargetInfo__Sequence__fini(krac_interfaces__msg__TargetInfo__Sequence * array);

/// Create array of msg/TargetInfo messages.
/**
 * It allocates the memory for the array and calls
 * krac_interfaces__msg__TargetInfo__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
krac_interfaces__msg__TargetInfo__Sequence *
krac_interfaces__msg__TargetInfo__Sequence__create(size_t size);

/// Destroy array of msg/TargetInfo messages.
/**
 * It calls
 * krac_interfaces__msg__TargetInfo__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
void
krac_interfaces__msg__TargetInfo__Sequence__destroy(krac_interfaces__msg__TargetInfo__Sequence * array);

/// Check for msg/TargetInfo message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
bool
krac_interfaces__msg__TargetInfo__Sequence__are_equal(const krac_interfaces__msg__TargetInfo__Sequence * lhs, const krac_interfaces__msg__TargetInfo__Sequence * rhs);

/// Copy an array of msg/TargetInfo messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
bool
krac_interfaces__msg__TargetInfo__Sequence__copy(
  const krac_interfaces__msg__TargetInfo__Sequence * input,
  krac_interfaces__msg__TargetInfo__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // KRAC_INTERFACES__MSG__DETAIL__TARGET_INFO__FUNCTIONS_H_
