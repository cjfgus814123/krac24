// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from krac_interfaces:msg/TargetInfo.idl
// generated code does not contain a copyright notice
#include "krac_interfaces/msg/detail/target_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `target_type`
#include "rosidl_runtime_c/string_functions.h"
// Member `location_xyz`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
krac_interfaces__msg__TargetInfo__init(krac_interfaces__msg__TargetInfo * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    krac_interfaces__msg__TargetInfo__fini(msg);
    return false;
  }
  // detected
  // target_type
  if (!rosidl_runtime_c__String__init(&msg->target_type)) {
    krac_interfaces__msg__TargetInfo__fini(msg);
    return false;
  }
  // image_x
  // image_y
  // distance
  // location_xyz
  if (!rosidl_runtime_c__float__Sequence__init(&msg->location_xyz, 0)) {
    krac_interfaces__msg__TargetInfo__fini(msg);
    return false;
  }
  return true;
}

void
krac_interfaces__msg__TargetInfo__fini(krac_interfaces__msg__TargetInfo * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // detected
  // target_type
  rosidl_runtime_c__String__fini(&msg->target_type);
  // image_x
  // image_y
  // distance
  // location_xyz
  rosidl_runtime_c__float__Sequence__fini(&msg->location_xyz);
}

bool
krac_interfaces__msg__TargetInfo__are_equal(const krac_interfaces__msg__TargetInfo * lhs, const krac_interfaces__msg__TargetInfo * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // detected
  if (lhs->detected != rhs->detected) {
    return false;
  }
  // target_type
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->target_type), &(rhs->target_type)))
  {
    return false;
  }
  // image_x
  if (lhs->image_x != rhs->image_x) {
    return false;
  }
  // image_y
  if (lhs->image_y != rhs->image_y) {
    return false;
  }
  // distance
  if (lhs->distance != rhs->distance) {
    return false;
  }
  // location_xyz
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->location_xyz), &(rhs->location_xyz)))
  {
    return false;
  }
  return true;
}

bool
krac_interfaces__msg__TargetInfo__copy(
  const krac_interfaces__msg__TargetInfo * input,
  krac_interfaces__msg__TargetInfo * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // detected
  output->detected = input->detected;
  // target_type
  if (!rosidl_runtime_c__String__copy(
      &(input->target_type), &(output->target_type)))
  {
    return false;
  }
  // image_x
  output->image_x = input->image_x;
  // image_y
  output->image_y = input->image_y;
  // distance
  output->distance = input->distance;
  // location_xyz
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->location_xyz), &(output->location_xyz)))
  {
    return false;
  }
  return true;
}

krac_interfaces__msg__TargetInfo *
krac_interfaces__msg__TargetInfo__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  krac_interfaces__msg__TargetInfo * msg = (krac_interfaces__msg__TargetInfo *)allocator.allocate(sizeof(krac_interfaces__msg__TargetInfo), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(krac_interfaces__msg__TargetInfo));
  bool success = krac_interfaces__msg__TargetInfo__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
krac_interfaces__msg__TargetInfo__destroy(krac_interfaces__msg__TargetInfo * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    krac_interfaces__msg__TargetInfo__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
krac_interfaces__msg__TargetInfo__Sequence__init(krac_interfaces__msg__TargetInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  krac_interfaces__msg__TargetInfo * data = NULL;

  if (size) {
    data = (krac_interfaces__msg__TargetInfo *)allocator.zero_allocate(size, sizeof(krac_interfaces__msg__TargetInfo), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = krac_interfaces__msg__TargetInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        krac_interfaces__msg__TargetInfo__fini(&data[i - 1]);
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
krac_interfaces__msg__TargetInfo__Sequence__fini(krac_interfaces__msg__TargetInfo__Sequence * array)
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
      krac_interfaces__msg__TargetInfo__fini(&array->data[i]);
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

krac_interfaces__msg__TargetInfo__Sequence *
krac_interfaces__msg__TargetInfo__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  krac_interfaces__msg__TargetInfo__Sequence * array = (krac_interfaces__msg__TargetInfo__Sequence *)allocator.allocate(sizeof(krac_interfaces__msg__TargetInfo__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = krac_interfaces__msg__TargetInfo__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
krac_interfaces__msg__TargetInfo__Sequence__destroy(krac_interfaces__msg__TargetInfo__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    krac_interfaces__msg__TargetInfo__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
krac_interfaces__msg__TargetInfo__Sequence__are_equal(const krac_interfaces__msg__TargetInfo__Sequence * lhs, const krac_interfaces__msg__TargetInfo__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!krac_interfaces__msg__TargetInfo__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
krac_interfaces__msg__TargetInfo__Sequence__copy(
  const krac_interfaces__msg__TargetInfo__Sequence * input,
  krac_interfaces__msg__TargetInfo__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(krac_interfaces__msg__TargetInfo);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    krac_interfaces__msg__TargetInfo * data =
      (krac_interfaces__msg__TargetInfo *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!krac_interfaces__msg__TargetInfo__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          krac_interfaces__msg__TargetInfo__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!krac_interfaces__msg__TargetInfo__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
