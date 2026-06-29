// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from krac_interfaces:msg/FlightPhase.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "krac_interfaces/msg/detail/flight_phase__struct.h"
#include "krac_interfaces/msg/detail/flight_phase__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool krac_interfaces__msg__flight_phase__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[46];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("krac_interfaces.msg._flight_phase.FlightPhase", full_classname_dest, 45) == 0);
  }
  krac_interfaces__msg__FlightPhase * ros_message = _ros_message;
  {  // current_phase
    PyObject * field = PyObject_GetAttrString(_pymsg, "current_phase");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->current_phase = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * krac_interfaces__msg__flight_phase__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of FlightPhase */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("krac_interfaces.msg._flight_phase");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "FlightPhase");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  krac_interfaces__msg__FlightPhase * ros_message = (krac_interfaces__msg__FlightPhase *)raw_ros_message;
  {  // current_phase
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->current_phase);
    {
      int rc = PyObject_SetAttrString(_pymessage, "current_phase", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
