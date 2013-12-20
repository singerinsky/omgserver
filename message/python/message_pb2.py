# Generated by the protocol buffer compiler.  DO NOT EDIT!
# source: message.proto

from google.protobuf.internal import enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from google.protobuf import reflection as _reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)




DESCRIPTOR = _descriptor.FileDescriptor(
  name='message.proto',
  package='',
  serialized_pb='\n\rmessage.proto\",\n\x17SoccerPlayerInfoRequest\x12\x11\n\tplayer_id\x18\x01 \x02(\x05\"N\n\x17SoccerPlayerInfoReponse\x12\x11\n\tplayer_id\x18\x01 \x02(\x05\x12\x13\n\x0bplayer_name\x18\x02 \x02(\t\x12\x0b\n\x03\x61ge\x18\x03 \x02(\x05*#\n\x0bMessageType\x12\x14\n\x10SoccerPlayerInfo\x10\x01')

_MESSAGETYPE = _descriptor.EnumDescriptor(
  name='MessageType',
  full_name='MessageType',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='SoccerPlayerInfo', index=0, number=1,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=143,
  serialized_end=178,
)

MessageType = enum_type_wrapper.EnumTypeWrapper(_MESSAGETYPE)
SoccerPlayerInfo = 1



_SOCCERPLAYERINFOREQUEST = _descriptor.Descriptor(
  name='SoccerPlayerInfoRequest',
  full_name='SoccerPlayerInfoRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='player_id', full_name='SoccerPlayerInfoRequest.player_id', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=17,
  serialized_end=61,
)


_SOCCERPLAYERINFOREPONSE = _descriptor.Descriptor(
  name='SoccerPlayerInfoReponse',
  full_name='SoccerPlayerInfoReponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='player_id', full_name='SoccerPlayerInfoReponse.player_id', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='player_name', full_name='SoccerPlayerInfoReponse.player_name', index=1,
      number=2, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='age', full_name='SoccerPlayerInfoReponse.age', index=2,
      number=3, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
  ],
  extensions=[
  ],
  nested_types=[],
  enum_types=[
  ],
  options=None,
  is_extendable=False,
  extension_ranges=[],
  serialized_start=63,
  serialized_end=141,
)

DESCRIPTOR.message_types_by_name['SoccerPlayerInfoRequest'] = _SOCCERPLAYERINFOREQUEST
DESCRIPTOR.message_types_by_name['SoccerPlayerInfoReponse'] = _SOCCERPLAYERINFOREPONSE

class SoccerPlayerInfoRequest(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _SOCCERPLAYERINFOREQUEST

  # @@protoc_insertion_point(class_scope:SoccerPlayerInfoRequest)

class SoccerPlayerInfoReponse(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _SOCCERPLAYERINFOREPONSE

  # @@protoc_insertion_point(class_scope:SoccerPlayerInfoReponse)


# @@protoc_insertion_point(module_scope)