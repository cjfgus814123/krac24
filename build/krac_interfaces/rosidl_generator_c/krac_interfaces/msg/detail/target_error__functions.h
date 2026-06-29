// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from krac_interfaces:msg/TargetError.idl
// generated code does not contain a copyright notice

#ifndef KRAC_INTERFACES__MSG__DETAIL__TARGET_ERROR__FUNCTIONS_H_
#define KRAC_INTERFACES__MSG__DETAIL__TARGET_ERROR__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "krac_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "krac_interfaces/msg/detail/target_error__struct.h"

/// Initialize msg/TargetError message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * krac_interfaces__msg__TargetError
 * )) before or use
 * krac_interfaces__msg__TargetError__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
bool
krac_interfaces__msg__TargetError__init(krac_interfaces__msg__TargetError * msg);

/// Finalize msg/TargetError message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
void
krac_interfaces__msg__TargetError__fini(krac_interfaces__msg__TargetError * msg);

/// Create msg/TargetError message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * krac_interfaces__msg__TargetError__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
krac_interfaces__msg__TargetError *
krac_interfaces__msg__TargetError__create();

/// Destroy msg/TargetError message.
/**
 * It calls
 * krac_interfaces__msg__TargetError__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
void
krac_interfaces__msg__TargetError__destroy(krac_interfaces__msg__TargetError * msg);

/// Check for msg/TargetError message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
bool
krac_interfaces__msg__TargetError__are_equal(const krac_interfaces__msg__TargetError * lhs, const krac_interfaces__msg__TargetError * rhs);

/// Copy a msg/TargetError message.
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
krac_interfaces__msg__TargetError__copy(
  const krac_interfaces__msg__TargetError * input,
  krac_interfaces__msg__TargetError * output);

/// Initialize array of msg/TargetError messages.
/**
 * It allocates the memory for the number of elements and calls
 * krac_interfaces__msg__TargetError__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
bool
krac_interfaces__msg__TargetError__Sequence__init(krac_interfaces__msg__TargetError__Sequence * array, size_t size);

/// Finalize array of msg/TargetError messages.
/**
 * It calls
 * krac_interfaces__msg__TargetError__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
void
krac_interfaces__msg__TargetError__Sequence__fini(krac_interfaces__msg__TargetError__Sequence * array);

/// Create array of msg/TargetError messages.
/**
 * It allocates the memory for the array and calls
 * krac_interfaces__msg__TargetError__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
krac_interfaces__msg__TargetError__Sequence *
krac_interfaces__msg__TargetError__Sequence__create(size_t size);

/// Destroy array of msg/TargetError messages.
/**
 * It calls
 * krac_interfaces__msg__TargetError__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
void
krac_interfaces__msg__TargetError__Sequence__destroy(krac_interfaces__msg__TargetError__Sequence * array);

/// Check for msg/TargetError message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_krac_interfaces
bool
krac_interfaces__msg__TargetError__Sequence__are_equal(const krac_interfaces__msg__TargetError__Sequence * lhs, const krac_interfaces__msg__TargetError__Sequence * rhs);

/// Copy an array of msg/TargetError messages.
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
krac_interfaces__msg__TargetError__Sequence__copy(
  const krac_interfaces__msg__TargetError__Sequence * input,
  krac_interfaces__msg__TargetError__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // KRAC_INTERFACES__MSG__DETAIL__TARGET_ERROR__FUNCTIONS_H_
