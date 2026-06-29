# generated from rosidl_generator_py/resource/_idl.py.em
# with input from krac_interfaces:msg/TargetError.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_TargetError(type):
    """Metaclass of message 'TargetError'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('krac_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'krac_interfaces.msg.TargetError')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__target_error
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__target_error
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__target_error
            cls._TYPE_SUPPORT = module.type_support_msg__msg__target_error
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__target_error

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class TargetError(metaclass=Metaclass_TargetError):
    """Message class 'TargetError'."""

    __slots__ = [
        '_is_detected',
        '_pixel_err_x',
        '_pixel_err_y',
        '_yaw_err_rad',
    ]

    _fields_and_field_types = {
        'is_detected': 'boolean',
        'pixel_err_x': 'float',
        'pixel_err_y': 'float',
        'yaw_err_rad': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.is_detected = kwargs.get('is_detected', bool())
        self.pixel_err_x = kwargs.get('pixel_err_x', float())
        self.pixel_err_y = kwargs.get('pixel_err_y', float())
        self.yaw_err_rad = kwargs.get('yaw_err_rad', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.is_detected != other.is_detected:
            return False
        if self.pixel_err_x != other.pixel_err_x:
            return False
        if self.pixel_err_y != other.pixel_err_y:
            return False
        if self.yaw_err_rad != other.yaw_err_rad:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def is_detected(self):
        """Message field 'is_detected'."""
        return self._is_detected

    @is_detected.setter
    def is_detected(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'is_detected' field must be of type 'bool'"
        self._is_detected = value

    @builtins.property
    def pixel_err_x(self):
        """Message field 'pixel_err_x'."""
        return self._pixel_err_x

    @pixel_err_x.setter
    def pixel_err_x(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'pixel_err_x' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'pixel_err_x' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._pixel_err_x = value

    @builtins.property
    def pixel_err_y(self):
        """Message field 'pixel_err_y'."""
        return self._pixel_err_y

    @pixel_err_y.setter
    def pixel_err_y(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'pixel_err_y' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'pixel_err_y' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._pixel_err_y = value

    @builtins.property
    def yaw_err_rad(self):
        """Message field 'yaw_err_rad'."""
        return self._yaw_err_rad

    @yaw_err_rad.setter
    def yaw_err_rad(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'yaw_err_rad' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'yaw_err_rad' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._yaw_err_rad = value
