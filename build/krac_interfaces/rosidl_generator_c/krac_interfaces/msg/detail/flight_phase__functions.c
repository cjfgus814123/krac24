// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from krac_interfaces:msg/FlightPhase.idl
// generated code does not contain a copyright notice
#include "krac_interfaces/msg/detail/flight_phase__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
krac_interfaces__msg__FlightPhase__init(krac_interfaces__msg__FlightPhase * msg)
{
  if (!msg) {
    return false;
  }
  // current_phase
  return true;
}

void
krac_interfaces__msg__FlightPhase__fini(krac_interfaces__msg__FlightPhase * msg)
{
  if (!msg) {
    return;
  }
  // current_phase
}

bool
krac_interfaces__msg__FlightPhase__are_equal(const krac_interfaces__msg__FlightPhase * lhs, const krac_interfaces__msg__FlightPhase * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // current_phase
  if (lhs->current_phase != rhs->current_phase) {
    return false;
  }
  return true;
}

bool
krac_interfaces__msg__FlightPhase__copy(
  const krac_interfaces__msg__FlightPhase * input,
  krac_interfaces__msg__FlightPhase * output)
{
  if (!input || !output) {
    return false;
  }
  // current_phase
  output->current_phase = input->current_phase;
  return true;
}

krac_interfaces__msg__FlightPhase *
krac_interfaces__msg__FlightPhase__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  krac_interfaces__msg__FlightPhase * msg = (krac_interfaces__msg__FlightPhase *)allocator.allocate(sizeof(krac_interfaces__msg__FlightPhase), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(krac_interfaces__msg__FlightPhase));
  bool success = krac_interfaces__msg__FlightPhase__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
krac_interfaces__msg__FlightPhase__destroy(krac_interfaces__msg__FlightPhase * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    krac_interfaces__msg__FlightPhase__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
krac_interfaces__msg__FlightPhase__Sequence__init(krac_interfaces__msg__FlightPhase__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  krac_interfaces__msg__FlightPhase * data = NULL;

  if (size) {
    data = (krac_interfaces__msg__FlightPhase *)allocator.zero_allocate(size, sizeof(krac_interfaces__msg__FlightPhase), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = krac_interfaces__msg__FlightPhase__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        krac_interfaces__msg__FlightPhase__fini(&data[i - 1]);
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
krac_interfaces__msg__FlightPhase__Sequence__fini(krac_interfaces__msg__FlightPhase__Sequence * array)
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
      krac_interfaces__msg__FlightPhase__fini(&array->data[i]);
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

krac_interfaces__msg__FlightPhase__Sequence *
krac_interfaces__msg__FlightPhase__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  krac_interfaces__msg__FlightPhase__Sequence * array = (krac_interfaces__msg__FlightPhase__Sequence *)allocator.allocate(sizeof(krac_interfaces__msg__FlightPhase__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = krac_interfaces__msg__FlightPhase__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
krac_interfaces__msg__FlightPhase__Sequence__destroy(krac_interfaces__msg__FlightPhase__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    krac_interfaces__msg__FlightPhase__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
krac_interfaces__msg__FlightPhase__Sequence__are_equal(const krac_interfaces__msg__FlightPhase__Sequence * lhs, const krac_interfaces__msg__FlightPhase__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!krac_interfaces__msg__FlightPhase__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
krac_interfaces__msg__FlightPhase__Sequence__copy(
  const krac_interfaces__msg__FlightPhase__Sequence * input,
  krac_interfaces__msg__FlightPhase__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(krac_interfaces__msg__FlightPhase);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    krac_interfaces__msg__FlightPhase * data =
      (krac_interfaces__msg__FlightPhase *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!krac_interfaces__msg__FlightPhase__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          krac_interfaces__msg__FlightPhase__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!krac_interfaces__msg__FlightPhase__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
