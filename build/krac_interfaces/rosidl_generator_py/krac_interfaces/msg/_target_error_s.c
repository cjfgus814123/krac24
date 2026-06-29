// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from krac_interfaces:msg/TargetError.idl
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
#include "krac_interfaces/msg/detail/target_error__struct.h"
#include "krac_interfaces/msg/detail/target_error__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool krac_interfaces__msg__target_error__convert_from_py(PyObject * _pymsg, void * _ros_message)
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
    assert(strncmp("krac_interfaces.msg._target_error.TargetError", full_classname_dest, 45) == 0);
  }
  krac_interfaces__msg__TargetError * ros_message = _ros_message;
  {  // is_detected
    PyObject * field = PyObject_GetAttrString(_pymsg, "is_detected");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->is_detected = (Py_True == field);
    Py_DECREF(field);
  }
  {  // pixel_err_x
    PyObject * field = PyObject_GetAttrString(_pymsg, "pixel_err_x");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->pixel_err_x = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // pixel_err_y
    PyObject * field = PyObject_GetAttrString(_pymsg, "pixel_err_y");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->pixel_err_y = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // yaw_err_rad
    PyObject * field = PyObject_GetAttrString(_pymsg, "yaw_err_rad");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->yaw_err_rad = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * krac_interfaces__msg__target_error__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of TargetError */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("krac_interfaces.msg._target_error");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "TargetError");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  krac_interfaces__msg__TargetError * ros_message = (krac_interfaces__msg__TargetError *)raw_ros_message;
  {  // is_detected
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->is_detected ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "is_detected", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pixel_err_x
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->pixel_err_x);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pixel_err_x", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // pixel_err_y
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->pixel_err_y);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pixel_err_y", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // yaw_err_rad
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->yaw_err_rad);
    {
      int rc = PyObject_SetAttrString(_pymessage, "yaw_err_rad", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
