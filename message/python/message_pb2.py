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
  serialized_pb='\n\rmessage.proto\",\n\x17SoccerPlayerInfoRequest\x12\x11\n\tplayer_id\x18\x01 \x02(\x05\"O\n\x18SoccerPlayerInfoResponse\x12\x11\n\tplayer_id\x18\x01 \x02(\x05\x12\x13\n\x0bplayer_name\x18\x02 \x02(\t\x12\x0b\n\x03\x61ge\x18\x03 \x02(\x05\"-\n\x16\x43lientHeartBeatRequest\x12\x13\n\x0b\x63lient_time\x18\x01 \x02(\x05\".\n\x17\x43lientHeartBeatResponse\x12\x13\n\x0bserver_time\x18\x01 \x02(\x05\"M\n\x12\x43lientLoginRequest\x12\x11\n\tplayer_id\x18\x01 \x02(\x05\x12\x12\n\nplayer_pwd\x18\x02 \x02(\t\x12\x10\n\x08md5_code\x18\x03 \x02(\t\"7\n\x13\x43lientLoginResponse\x12\x0b\n\x03ret\x18\x01 \x02(\x05\x12\x13\n\x0bplayer_name\x18\x02 \x02(\t*D\n\x0fMSG_ACTION_TYPE\x12\x0f\n\x0bMSG_REQUEST\x10\x00\x12\x10\n\x0cMSG_RESPONSE\x10\x01\x12\x0e\n\nMSG_NOTIFY\x10\x02*S\n\x0bMessageType\x12\x1a\n\x16MSG_SOCCER_PLAYER_INFO\x10\x01\x12\x12\n\x0eMSG_HEART_BEAT\x10\x02\x12\x14\n\x10MSG_CLIENT_LOGIN\x10\x03')

_MSG_ACTION_TYPE = _descriptor.EnumDescriptor(
  name='MSG_ACTION_TYPE',
  full_name='MSG_ACTION_TYPE',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='MSG_REQUEST', index=0, number=0,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_RESPONSE', index=1, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_NOTIFY', index=2, number=2,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=375,
  serialized_end=443,
)

MSG_ACTION_TYPE = enum_type_wrapper.EnumTypeWrapper(_MSG_ACTION_TYPE)
_MESSAGETYPE = _descriptor.EnumDescriptor(
  name='MessageType',
  full_name='MessageType',
  filename=None,
  file=DESCRIPTOR,
  values=[
    _descriptor.EnumValueDescriptor(
      name='MSG_SOCCER_PLAYER_INFO', index=0, number=1,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_HEART_BEAT', index=1, number=2,
      options=None,
      type=None),
    _descriptor.EnumValueDescriptor(
      name='MSG_CLIENT_LOGIN', index=2, number=3,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=445,
  serialized_end=528,
)

MessageType = enum_type_wrapper.EnumTypeWrapper(_MESSAGETYPE)
MSG_REQUEST = 0
MSG_RESPONSE = 1
MSG_NOTIFY = 2
MSG_SOCCER_PLAYER_INFO = 1
MSG_HEART_BEAT = 2
MSG_CLIENT_LOGIN = 3



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


_SOCCERPLAYERINFORESPONSE = _descriptor.Descriptor(
  name='SoccerPlayerInfoResponse',
  full_name='SoccerPlayerInfoResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='player_id', full_name='SoccerPlayerInfoResponse.player_id', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='player_name', full_name='SoccerPlayerInfoResponse.player_name', index=1,
      number=2, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='age', full_name='SoccerPlayerInfoResponse.age', index=2,
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
  serialized_end=142,
)


_CLIENTHEARTBEATREQUEST = _descriptor.Descriptor(
  name='ClientHeartBeatRequest',
  full_name='ClientHeartBeatRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='client_time', full_name='ClientHeartBeatRequest.client_time', index=0,
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
  serialized_start=144,
  serialized_end=189,
)


_CLIENTHEARTBEATRESPONSE = _descriptor.Descriptor(
  name='ClientHeartBeatResponse',
  full_name='ClientHeartBeatResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='server_time', full_name='ClientHeartBeatResponse.server_time', index=0,
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
  serialized_start=191,
  serialized_end=237,
)


_CLIENTLOGINREQUEST = _descriptor.Descriptor(
  name='ClientLoginRequest',
  full_name='ClientLoginRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='player_id', full_name='ClientLoginRequest.player_id', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='player_pwd', full_name='ClientLoginRequest.player_pwd', index=1,
      number=2, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='md5_code', full_name='ClientLoginRequest.md5_code', index=2,
      number=3, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=unicode("", "utf-8"),
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
  serialized_start=239,
  serialized_end=316,
)


_CLIENTLOGINRESPONSE = _descriptor.Descriptor(
  name='ClientLoginResponse',
  full_name='ClientLoginResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    _descriptor.FieldDescriptor(
      name='ret', full_name='ClientLoginResponse.ret', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    _descriptor.FieldDescriptor(
      name='player_name', full_name='ClientLoginResponse.player_name', index=1,
      number=2, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=unicode("", "utf-8"),
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
  serialized_start=318,
  serialized_end=373,
)

DESCRIPTOR.message_types_by_name['SoccerPlayerInfoRequest'] = _SOCCERPLAYERINFOREQUEST
DESCRIPTOR.message_types_by_name['SoccerPlayerInfoResponse'] = _SOCCERPLAYERINFORESPONSE
DESCRIPTOR.message_types_by_name['ClientHeartBeatRequest'] = _CLIENTHEARTBEATREQUEST
DESCRIPTOR.message_types_by_name['ClientHeartBeatResponse'] = _CLIENTHEARTBEATRESPONSE
DESCRIPTOR.message_types_by_name['ClientLoginRequest'] = _CLIENTLOGINREQUEST
DESCRIPTOR.message_types_by_name['ClientLoginResponse'] = _CLIENTLOGINRESPONSE

class SoccerPlayerInfoRequest(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _SOCCERPLAYERINFOREQUEST

  # @@protoc_insertion_point(class_scope:SoccerPlayerInfoRequest)

class SoccerPlayerInfoResponse(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _SOCCERPLAYERINFORESPONSE

  # @@protoc_insertion_point(class_scope:SoccerPlayerInfoResponse)

class ClientHeartBeatRequest(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _CLIENTHEARTBEATREQUEST

  # @@protoc_insertion_point(class_scope:ClientHeartBeatRequest)

class ClientHeartBeatResponse(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _CLIENTHEARTBEATRESPONSE

  # @@protoc_insertion_point(class_scope:ClientHeartBeatResponse)

class ClientLoginRequest(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _CLIENTLOGINREQUEST

  # @@protoc_insertion_point(class_scope:ClientLoginRequest)

class ClientLoginResponse(_message.Message):
  __metaclass__ = _reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _CLIENTLOGINRESPONSE

  # @@protoc_insertion_point(class_scope:ClientLoginResponse)


# @@protoc_insertion_point(module_scope)
