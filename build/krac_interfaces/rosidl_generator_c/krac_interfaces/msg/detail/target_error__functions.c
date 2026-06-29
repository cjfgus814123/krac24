// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from krac_interfaces:msg/TargetError.idl
// generated code does not contain a copyright notice
#include "krac_interfaces/msg/detail/target_error__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
krac_interfaces__msg__TargetError__init(krac_interfaces__msg__TargetError * msg)
{
  if (!msg) {
    return false;
  }
  // is_detected
  // pixel_err_x
  // pixel_err_y
  // yaw_err_rad
  return true;
}

void
krac_interfaces__msg__TargetError__fini(krac_interfaces__msg__TargetError * msg)
{
  if (!msg) {
    return;
  }
  // is_detected
  // pixel_err_x
  // pixel_err_y
  // yaw_err_rad
}

bool
krac_interfaces__msg__TargetError__are_equal(const krac_interfaces__msg__TargetError * lhs, const krac_interfaces__msg__TargetError * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // is_detected
  if (lhs->is_detected != rhs->is_detected) {
    return false;
  }
  // pixel_err_x
  if (lhs->pixel_err_x != rhs->pixel_err_x) {
    return false;
  }
  // pixel_err_y
  if (lhs->pixel_err_y != rhs->pixel_err_y) {
    return false;
  }
  // yaw_err_rad
  if (lhs->yaw_err_rad != rhs->yaw_err_rad) {
    return false;
  }
  return true;
}

bool
krac_interfaces__msg__TargetError__copy(
  const krac_interfaces__msg__TargetError * input,
  krac_interfaces__msg__TargetError * output)
{
  if (!input || !output) {
    return false;
  }
  // is_detected
  output->is_detected = input->is_detected;
  // pixel_err_x
  output->pixel_err_x = input->pixel_err_x;
  // pixel_err_y
  output->pixel_err_y = input->pixel_err_y;
  // yaw_err_rad
  output->yaw_err_rad = input->yaw_err_rad;
  return true;
}

krac_interfaces__msg__TargetError *
krac_interfaces__msg__TargetError__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  krac_interfaces__msg__TargetError * msg = (krac_interfaces__msg__TargetError *)allocator.allocate(sizeof(krac_interfaces__msg__TargetError), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(krac_interfaces__msg__TargetError));
  bool success = krac_interfaces__msg__TargetError__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
krac_interfaces__msg__TargetError__destroy(krac_interfaces__msg__TargetError * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    krac_interfaces__msg__TargetError__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
krac_interfaces__msg__TargetError__Sequence__init(krac_interfaces__msg__TargetError__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  krac_interfaces__msg__TargetError * data = NULL;

  if (size) {
    data = (krac_interfaces__msg__TargetError *)allocator.zero_allocate(size, sizeof(krac_interfaces__msg__TargetError), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = krac_interfaces__msg__TargetError__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        krac_interfaces__msg__TargetError__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
krac_interfaces__msg__TargetError__Sequence__fini(krac_interfaces__msg__TargetError__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      krac_interfaces__msg__TargetError__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

krac_interfaces__msg__TargetError__Sequence *
krac_interfaces__msg__TargetError__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  krac_interfaces__msg__TargetError__Sequence * array = (krac_interfaces__msg__TargetError__Sequence *)allocator.allocate(sizeof(krac_interfaces__msg__TargetError__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = krac_interfaces__msg__TargetError__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
krac_interfaces__msg__TargetError__Sequence__destroy(krac_interfaces__msg__TargetError__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    krac_interfaces__msg__TargetError__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
krac_interfaces__msg__TargetError__Sequence__are_equal(const krac_interfaces__msg__TargetError__Sequence * lhs, const krac_interfaces__msg__TargetError__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!krac_interfaces__msg__TargetError__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
krac_interfaces__msg__TargetError__Sequence__copy(
  const krac_interfaces__msg__TargetError__Sequence * input,
  krac_interfaces__msg__TargetError__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(krac_interfaces__msg__TargetError);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    krac_interfaces__msg__TargetError * data =
      (krac_interfaces__msg__TargetError *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!krac_interfaces__msg__TargetError__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          krac_interfaces__msg__TargetError__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!krac_interfaces__msg__TargetError__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
