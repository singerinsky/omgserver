# Generated by the protocol buffer compiler.  DO NOT EDIT!

from google.protobuf import descriptor
from google.protobuf import message
from google.protobuf import reflection
from google.protobuf import descriptor_pb2
# @@protoc_insertion_point(imports)



DESCRIPTOR = descriptor.FileDescriptor(
  name='message.proto',
  package='',
  serialized_pb='\n\rmessage.proto\",\n\x17SoccerPlayerInfoRequest\x12\x11\n\tplayer_id\x18\x01 \x02(\x05\"O\n\x18SoccerPlayerInfoResponse\x12\x11\n\tplayer_id\x18\x01 \x02(\x05\x12\x13\n\x0bplayer_name\x18\x02 \x02(\t\x12\x0b\n\x03\x61ge\x18\x03 \x02(\x05\"-\n\x16\x43lientHeartBeatRequest\x12\x13\n\x0b\x63lient_time\x18\x01 \x02(\x05\".\n\x17\x43lientHeartBeatResponse\x12\x13\n\x0bserver_time\x18\x01 \x02(\x05\"M\n\x12\x43lientLoginRequest\x12\x11\n\tplayer_id\x18\x01 \x02(\x05\x12\x12\n\nplayer_pwd\x18\x02 \x02(\t\x12\x10\n\x08md5_code\x18\x03 \x02(\t\"J\n\x13\x43lientLoginResponse\x12\x0b\n\x03ret\x18\x01 \x02(\x05\x12\x11\n\tplayer_id\x18\x02 \x02(\x05\x12\x13\n\x0bplayer_name\x18\x03 \x02(\t\"1\n\x19GateServerRegisterRequest\x12\x14\n\x0cserver_index\x18\x01 \x02(\x05\")\n\x1aGateServerRegisterResponse\x12\x0b\n\x03ret\x18\x02 \x02(\x05*D\n\x0fMSG_ACTION_TYPE\x12\x0f\n\x0bMSG_REQUEST\x10\x00\x12\x10\n\x0cMSG_RESPONSE\x10\x01\x12\x0e\n\nMSG_NOTIFY\x10\x02*q\n\x0bMessageType\x12\x1a\n\x16MSG_SOCCER_PLAYER_INFO\x10\x01\x12\x12\n\x0eMSG_HEART_BEAT\x10\x02\x12\x14\n\x10MSG_CLIENT_LOGIN\x10\x03\x12\x1c\n\x18MSG_GATE_SERVER_REGISTER\x10\x04')

_MSG_ACTION_TYPE = descriptor.EnumDescriptor(
  name='MSG_ACTION_TYPE',
  full_name='MSG_ACTION_TYPE',
  filename=None,
  file=DESCRIPTOR,
  values=[
    descriptor.EnumValueDescriptor(
      name='MSG_REQUEST', index=0, number=0,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='MSG_RESPONSE', index=1, number=1,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='MSG_NOTIFY', index=2, number=2,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=488,
  serialized_end=556,
)


_MESSAGETYPE = descriptor.EnumDescriptor(
  name='MessageType',
  full_name='MessageType',
  filename=None,
  file=DESCRIPTOR,
  values=[
    descriptor.EnumValueDescriptor(
      name='MSG_SOCCER_PLAYER_INFO', index=0, number=1,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='MSG_HEART_BEAT', index=1, number=2,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='MSG_CLIENT_LOGIN', index=2, number=3,
      options=None,
      type=None),
    descriptor.EnumValueDescriptor(
      name='MSG_GATE_SERVER_REGISTER', index=3, number=4,
      options=None,
      type=None),
  ],
  containing_type=None,
  options=None,
  serialized_start=558,
  serialized_end=671,
)


MSG_REQUEST = 0
MSG_RESPONSE = 1
MSG_NOTIFY = 2
MSG_SOCCER_PLAYER_INFO = 1
MSG_HEART_BEAT = 2
MSG_CLIENT_LOGIN = 3
MSG_GATE_SERVER_REGISTER = 4



_SOCCERPLAYERINFOREQUEST = descriptor.Descriptor(
  name='SoccerPlayerInfoRequest',
  full_name='SoccerPlayerInfoRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
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


_SOCCERPLAYERINFORESPONSE = descriptor.Descriptor(
  name='SoccerPlayerInfoResponse',
  full_name='SoccerPlayerInfoResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='player_id', full_name='SoccerPlayerInfoResponse.player_id', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='player_name', full_name='SoccerPlayerInfoResponse.player_name', index=1,
      number=2, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
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


_CLIENTHEARTBEATREQUEST = descriptor.Descriptor(
  name='ClientHeartBeatRequest',
  full_name='ClientHeartBeatRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
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


_CLIENTHEARTBEATRESPONSE = descriptor.Descriptor(
  name='ClientHeartBeatResponse',
  full_name='ClientHeartBeatResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
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


_CLIENTLOGINREQUEST = descriptor.Descriptor(
  name='ClientLoginRequest',
  full_name='ClientLoginRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='player_id', full_name='ClientLoginRequest.player_id', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='player_pwd', full_name='ClientLoginRequest.player_pwd', index=1,
      number=2, type=9, cpp_type=9, label=2,
      has_default_value=False, default_value=unicode("", "utf-8"),
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
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


_CLIENTLOGINRESPONSE = descriptor.Descriptor(
  name='ClientLoginResponse',
  full_name='ClientLoginResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='ret', full_name='ClientLoginResponse.ret', index=0,
      number=1, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='player_id', full_name='ClientLoginResponse.player_id', index=1,
      number=2, type=5, cpp_type=1, label=2,
      has_default_value=False, default_value=0,
      message_type=None, enum_type=None, containing_type=None,
      is_extension=False, extension_scope=None,
      options=None),
    descriptor.FieldDescriptor(
      name='player_name', full_name='ClientLoginResponse.player_name', index=2,
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
  serialized_start=318,
  serialized_end=392,
)


_GATESERVERREGISTERREQUEST = descriptor.Descriptor(
  name='GateServerRegisterRequest',
  full_name='GateServerRegisterRequest',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='server_index', full_name='GateServerRegisterRequest.server_index', index=0,
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
  serialized_start=394,
  serialized_end=443,
)


_GATESERVERREGISTERRESPONSE = descriptor.Descriptor(
  name='GateServerRegisterResponse',
  full_name='GateServerRegisterResponse',
  filename=None,
  file=DESCRIPTOR,
  containing_type=None,
  fields=[
    descriptor.FieldDescriptor(
      name='ret', full_name='GateServerRegisterResponse.ret', index=0,
      number=2, type=5, cpp_type=1, label=2,
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
  serialized_start=445,
  serialized_end=486,
)

DESCRIPTOR.message_types_by_name['SoccerPlayerInfoRequest'] = _SOCCERPLAYERINFOREQUEST
DESCRIPTOR.message_types_by_name['SoccerPlayerInfoResponse'] = _SOCCERPLAYERINFORESPONSE
DESCRIPTOR.message_types_by_name['ClientHeartBeatRequest'] = _CLIENTHEARTBEATREQUEST
DESCRIPTOR.message_types_by_name['ClientHeartBeatResponse'] = _CLIENTHEARTBEATRESPONSE
DESCRIPTOR.message_types_by_name['ClientLoginRequest'] = _CLIENTLOGINREQUEST
DESCRIPTOR.message_types_by_name['ClientLoginResponse'] = _CLIENTLOGINRESPONSE
DESCRIPTOR.message_types_by_name['GateServerRegisterRequest'] = _GATESERVERREGISTERREQUEST
DESCRIPTOR.message_types_by_name['GateServerRegisterResponse'] = _GATESERVERREGISTERRESPONSE

class SoccerPlayerInfoRequest(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _SOCCERPLAYERINFOREQUEST
  
  # @@protoc_insertion_point(class_scope:SoccerPlayerInfoRequest)

class SoccerPlayerInfoResponse(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _SOCCERPLAYERINFORESPONSE
  
  # @@protoc_insertion_point(class_scope:SoccerPlayerInfoResponse)

class ClientHeartBeatRequest(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _CLIENTHEARTBEATREQUEST
  
  # @@protoc_insertion_point(class_scope:ClientHeartBeatRequest)

class ClientHeartBeatResponse(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _CLIENTHEARTBEATRESPONSE
  
  # @@protoc_insertion_point(class_scope:ClientHeartBeatResponse)

class ClientLoginRequest(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _CLIENTLOGINREQUEST
  
  # @@protoc_insertion_point(class_scope:ClientLoginRequest)

class ClientLoginResponse(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _CLIENTLOGINRESPONSE
  
  # @@protoc_insertion_point(class_scope:ClientLoginResponse)

class GateServerRegisterRequest(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _GATESERVERREGISTERREQUEST
  
  # @@protoc_insertion_point(class_scope:GateServerRegisterRequest)

class GateServerRegisterResponse(message.Message):
  __metaclass__ = reflection.GeneratedProtocolMessageType
  DESCRIPTOR = _GATESERVERREGISTERRESPONSE
  
  # @@protoc_insertion_point(class_scope:GateServerRegisterResponse)

# @@protoc_insertion_point(module_scope)
