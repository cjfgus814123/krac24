# generated from rosidl_generator_py/resource/_idl.py.em
# with input from krac_interfaces:msg/FlightPhase.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_FlightPhase(type):
    """Metaclass of message 'FlightPhase'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'READY': 0,
        'TAKEOFF_VERTICAL': 1,
        'HOVERING_WP1': 2,
        'TRANSITION_TO_FW': 3,
        'CRUISE_WP2_TO_WP3': 4,
        'CRUISE_WP3_TO_WP4': 5,
        'CRUISE_WP4_TO_WP2': 6,
        'TRANSITION_TO_MC': 7,
        'RESCUE_OPERATION': 8,
        'DROP_RESCUEE': 9,
        'LANDING_VERTICAL': 10,
        'MISSION_COMPLETE': 11,
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
                'krac_interfaces.msg.FlightPhase')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__flight_phase
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__flight_phase
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__flight_phase
            cls._TYPE_SUPPORT = module.type_support_msg__msg__flight_phase
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__flight_phase

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'READY': cls.__constants['READY'],
            'TAKEOFF_VERTICAL': cls.__constants['TAKEOFF_VERTICAL'],
            'HOVERING_WP1': cls.__constants['HOVERING_WP1'],
            'TRANSITION_TO_FW': cls.__constants['TRANSITION_TO_FW'],
            'CRUISE_WP2_TO_WP3': cls.__constants['CRUISE_WP2_TO_WP3'],
            'CRUISE_WP3_TO_WP4': cls.__constants['CRUISE_WP3_TO_WP4'],
            'CRUISE_WP4_TO_WP2': cls.__constants['CRUISE_WP4_TO_WP2'],
            'TRANSITION_TO_MC': cls.__constants['TRANSITION_TO_MC'],
            'RESCUE_OPERATION': cls.__constants['RESCUE_OPERATION'],
            'DROP_RESCUEE': cls.__constants['DROP_RESCUEE'],
            'LANDING_VERTICAL': cls.__constants['LANDING_VERTICAL'],
            'MISSION_COMPLETE': cls.__constants['MISSION_COMPLETE'],
        }

    @property
    def READY(self):
        """Message constant 'READY'."""
        return Metaclass_FlightPhase.__constants['READY']

    @property
    def TAKEOFF_VERTICAL(self):
        """Message constant 'TAKEOFF_VERTICAL'."""
        return Metaclass_FlightPhase.__constants['TAKEOFF_VERTICAL']

    @property
    def HOVERING_WP1(self):
        """Message constant 'HOVERING_WP1'."""
        return Metaclass_FlightPhase.__constants['HOVERING_WP1']

    @property
    def TRANSITION_TO_FW(self):
        """Message constant 'TRANSITION_TO_FW'."""
        return Metaclass_FlightPhase.__constants['TRANSITION_TO_FW']

    @property
    def CRUISE_WP2_TO_WP3(self):
        """Message constant 'CRUISE_WP2_TO_WP3'."""
        return Metaclass_FlightPhase.__constants['CRUISE_WP2_TO_WP3']

    @property
    def CRUISE_WP3_TO_WP4(self):
        """Message constant 'CRUISE_WP3_TO_WP4'."""
        return Metaclass_FlightPhase.__constants['CRUISE_WP3_TO_WP4']

    @property
    def CRUISE_WP4_TO_WP2(self):
        """Message constant 'CRUISE_WP4_TO_WP2'."""
        return Metaclass_FlightPhase.__constants['CRUISE_WP4_TO_WP2']

    @property
    def TRANSITION_TO_MC(self):
        """Message constant 'TRANSITION_TO_MC'."""
        return Metaclass_FlightPhase.__constants['TRANSITION_TO_MC']

    @property
    def RESCUE_OPERATION(self):
        """Message constant 'RESCUE_OPERATION'."""
        return Metaclass_FlightPhase.__constants['RESCUE_OPERATION']

    @property
    def DROP_RESCUEE(self):
        """Message constant 'DROP_RESCUEE'."""
        return Metaclass_FlightPhase.__constants['DROP_RESCUEE']

    @property
    def LANDING_VERTICAL(self):
        """Message constant 'LANDING_VERTICAL'."""
        return Metaclass_FlightPhase.__constants['LANDING_VERTICAL']

    @property
    def MISSION_COMPLETE(self):
        """Message constant 'MISSION_COMPLETE'."""
        return Metaclass_FlightPhase.__constants['MISSION_COMPLETE']


class FlightPhase(metaclass=Metaclass_FlightPhase):
    """
    Message class 'FlightPhase'.

    Constants:
      READY
      TAKEOFF_VERTICAL
      HOVERING_WP1
      TRANSITION_TO_FW
      CRUISE_WP2_TO_WP3
      CRUISE_WP3_TO_WP4
      CRUISE_WP4_TO_WP2
      TRANSITION_TO_MC
      RESCUE_OPERATION
      DROP_RESCUEE
      LANDING_VERTICAL
      MISSION_COMPLETE
    """

    __slots__ = [
        '_current_phase',
    ]

    _fields_and_field_types = {
        'current_phase': 'uint8',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.current_phase = kwargs.get('current_phase', int())

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
        if self.current_phase != other.current_phase:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def current_phase(self):
        """Message field 'current_phase'."""
        return self._current_phase

    @current_phase.setter
    def current_phase(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'current_phase' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'current_phase' field must be an unsigned integer in [0, 255]"
        self._current_phase = value
