// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message.proto

#ifndef PROTOBUF_message_2eproto__INCLUDED
#define PROTOBUF_message_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_message_2eproto();
void protobuf_AssignDesc_message_2eproto();
void protobuf_ShutdownFile_message_2eproto();

class SoccerPlayerInfoRequest;
class SoccerPlayerInfoResponse;
class ClientHeartBeatRequest;
class ClientHeartBeatResponse;
class ClientLoginRequest;
class ClientLoginResponse;

enum MSG_ACTION_TYPE {
  MSG_REQUEST = 0,
  MSG_RESPONSE = 1,
  MSG_NOTIFY = 2
};
bool MSG_ACTION_TYPE_IsValid(int value);
const MSG_ACTION_TYPE MSG_ACTION_TYPE_MIN = MSG_REQUEST;
const MSG_ACTION_TYPE MSG_ACTION_TYPE_MAX = MSG_NOTIFY;
const int MSG_ACTION_TYPE_ARRAYSIZE = MSG_ACTION_TYPE_MAX + 1;

const ::google::protobuf::EnumDescriptor* MSG_ACTION_TYPE_descriptor();
inline const ::std::string& MSG_ACTION_TYPE_Name(MSG_ACTION_TYPE value) {
  return ::google::protobuf::internal::NameOfEnum(
    MSG_ACTION_TYPE_descriptor(), value);
}
inline bool MSG_ACTION_TYPE_Parse(
    const ::std::string& name, MSG_ACTION_TYPE* value) {
  return ::google::protobuf::internal::ParseNamedEnum<MSG_ACTION_TYPE>(
    MSG_ACTION_TYPE_descriptor(), name, value);
}
enum MessageType {
  MSG_SOCCER_PLAYER_INFO = 1,
  MSG_HEART_BEAT = 2,
  MSG_CLIENT_LOGIN = 3
};
bool MessageType_IsValid(int value);
const MessageType MessageType_MIN = MSG_SOCCER_PLAYER_INFO;
const MessageType MessageType_MAX = MSG_CLIENT_LOGIN;
const int MessageType_ARRAYSIZE = MessageType_MAX + 1;

const ::google::protobuf::EnumDescriptor* MessageType_descriptor();
inline const ::std::string& MessageType_Name(MessageType value) {
  return ::google::protobuf::internal::NameOfEnum(
    MessageType_descriptor(), value);
}
inline bool MessageType_Parse(
    const ::std::string& name, MessageType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<MessageType>(
    MessageType_descriptor(), name, value);
}
// ===================================================================

class SoccerPlayerInfoRequest : public ::google::protobuf::Message {
 public:
  SoccerPlayerInfoRequest();
  virtual ~SoccerPlayerInfoRequest();

  SoccerPlayerInfoRequest(const SoccerPlayerInfoRequest& from);

  inline SoccerPlayerInfoRequest& operator=(const SoccerPlayerInfoRequest& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const SoccerPlayerInfoRequest& default_instance();

  void Swap(SoccerPlayerInfoRequest* other);

  // implements Message ----------------------------------------------

  SoccerPlayerInfoRequest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SoccerPlayerInfoRequest& from);
  void MergeFrom(const SoccerPlayerInfoRequest& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 player_id = 1;
  inline bool has_player_id() const;
  inline void clear_player_id();
  static const int kPlayerIdFieldNumber = 1;
  inline ::google::protobuf::int32 player_id() const;
  inline void set_player_id(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:SoccerPlayerInfoRequest)
 private:
  inline void set_has_player_id();
  inline void clear_has_player_id();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 player_id_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_message_2eproto();
  friend void protobuf_AssignDesc_message_2eproto();
  friend void protobuf_ShutdownFile_message_2eproto();

  void InitAsDefaultInstance();
  static SoccerPlayerInfoRequest* default_instance_;
};
// -------------------------------------------------------------------

class SoccerPlayerInfoResponse : public ::google::protobuf::Message {
 public:
  SoccerPlayerInfoResponse();
  virtual ~SoccerPlayerInfoResponse();

  SoccerPlayerInfoResponse(const SoccerPlayerInfoResponse& from);

  inline SoccerPlayerInfoResponse& operator=(const SoccerPlayerInfoResponse& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const SoccerPlayerInfoResponse& default_instance();

  void Swap(SoccerPlayerInfoResponse* other);

  // implements Message ----------------------------------------------

  SoccerPlayerInfoResponse* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const SoccerPlayerInfoResponse& from);
  void MergeFrom(const SoccerPlayerInfoResponse& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 player_id = 1;
  inline bool has_player_id() const;
  inline void clear_player_id();
  static const int kPlayerIdFieldNumber = 1;
  inline ::google::protobuf::int32 player_id() const;
  inline void set_player_id(::google::protobuf::int32 value);

  // required string player_name = 2;
  inline bool has_player_name() const;
  inline void clear_player_name();
  static const int kPlayerNameFieldNumber = 2;
  inline const ::std::string& player_name() const;
  inline void set_player_name(const ::std::string& value);
  inline void set_player_name(const char* value);
  inline void set_player_name(const char* value, size_t size);
  inline ::std::string* mutable_player_name();
  inline ::std::string* release_player_name();
  inline void set_allocated_player_name(::std::string* player_name);

  // required int32 age = 3;
  inline bool has_age() const;
  inline void clear_age();
  static const int kAgeFieldNumber = 3;
  inline ::google::protobuf::int32 age() const;
  inline void set_age(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:SoccerPlayerInfoResponse)
 private:
  inline void set_has_player_id();
  inline void clear_has_player_id();
  inline void set_has_player_name();
  inline void clear_has_player_name();
  inline void set_has_age();
  inline void clear_has_age();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* player_name_;
  ::google::protobuf::int32 player_id_;
  ::google::protobuf::int32 age_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_message_2eproto();
  friend void protobuf_AssignDesc_message_2eproto();
  friend void protobuf_ShutdownFile_message_2eproto();

  void InitAsDefaultInstance();
  static SoccerPlayerInfoResponse* default_instance_;
};
// -------------------------------------------------------------------

class ClientHeartBeatRequest : public ::google::protobuf::Message {
 public:
  ClientHeartBeatRequest();
  virtual ~ClientHeartBeatRequest();

  ClientHeartBeatRequest(const ClientHeartBeatRequest& from);

  inline ClientHeartBeatRequest& operator=(const ClientHeartBeatRequest& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ClientHeartBeatRequest& default_instance();

  void Swap(ClientHeartBeatRequest* other);

  // implements Message ----------------------------------------------

  ClientHeartBeatRequest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ClientHeartBeatRequest& from);
  void MergeFrom(const ClientHeartBeatRequest& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 client_time = 1;
  inline bool has_client_time() const;
  inline void clear_client_time();
  static const int kClientTimeFieldNumber = 1;
  inline ::google::protobuf::int32 client_time() const;
  inline void set_client_time(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:ClientHeartBeatRequest)
 private:
  inline void set_has_client_time();
  inline void clear_has_client_time();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 client_time_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_message_2eproto();
  friend void protobuf_AssignDesc_message_2eproto();
  friend void protobuf_ShutdownFile_message_2eproto();

  void InitAsDefaultInstance();
  static ClientHeartBeatRequest* default_instance_;
};
// -------------------------------------------------------------------

class ClientHeartBeatResponse : public ::google::protobuf::Message {
 public:
  ClientHeartBeatResponse();
  virtual ~ClientHeartBeatResponse();

  ClientHeartBeatResponse(const ClientHeartBeatResponse& from);

  inline ClientHeartBeatResponse& operator=(const ClientHeartBeatResponse& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ClientHeartBeatResponse& default_instance();

  void Swap(ClientHeartBeatResponse* other);

  // implements Message ----------------------------------------------

  ClientHeartBeatResponse* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ClientHeartBeatResponse& from);
  void MergeFrom(const ClientHeartBeatResponse& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 server_time = 1;
  inline bool has_server_time() const;
  inline void clear_server_time();
  static const int kServerTimeFieldNumber = 1;
  inline ::google::protobuf::int32 server_time() const;
  inline void set_server_time(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:ClientHeartBeatResponse)
 private:
  inline void set_has_server_time();
  inline void clear_has_server_time();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::int32 server_time_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];

  friend void  protobuf_AddDesc_message_2eproto();
  friend void protobuf_AssignDesc_message_2eproto();
  friend void protobuf_ShutdownFile_message_2eproto();

  void InitAsDefaultInstance();
  static ClientHeartBeatResponse* default_instance_;
};
// -------------------------------------------------------------------

class ClientLoginRequest : public ::google::protobuf::Message {
 public:
  ClientLoginRequest();
  virtual ~ClientLoginRequest();

  ClientLoginRequest(const ClientLoginRequest& from);

  inline ClientLoginRequest& operator=(const ClientLoginRequest& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ClientLoginRequest& default_instance();

  void Swap(ClientLoginRequest* other);

  // implements Message ----------------------------------------------

  ClientLoginRequest* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ClientLoginRequest& from);
  void MergeFrom(const ClientLoginRequest& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 player_id = 1;
  inline bool has_player_id() const;
  inline void clear_player_id();
  static const int kPlayerIdFieldNumber = 1;
  inline ::google::protobuf::int32 player_id() const;
  inline void set_player_id(::google::protobuf::int32 value);

  // required string player_pwd = 2;
  inline bool has_player_pwd() const;
  inline void clear_player_pwd();
  static const int kPlayerPwdFieldNumber = 2;
  inline const ::std::string& player_pwd() const;
  inline void set_player_pwd(const ::std::string& value);
  inline void set_player_pwd(const char* value);
  inline void set_player_pwd(const char* value, size_t size);
  inline ::std::string* mutable_player_pwd();
  inline ::std::string* release_player_pwd();
  inline void set_allocated_player_pwd(::std::string* player_pwd);

  // required string md5_code = 3;
  inline bool has_md5_code() const;
  inline void clear_md5_code();
  static const int kMd5CodeFieldNumber = 3;
  inline const ::std::string& md5_code() const;
  inline void set_md5_code(const ::std::string& value);
  inline void set_md5_code(const char* value);
  inline void set_md5_code(const char* value, size_t size);
  inline ::std::string* mutable_md5_code();
  inline ::std::string* release_md5_code();
  inline void set_allocated_md5_code(::std::string* md5_code);

  // @@protoc_insertion_point(class_scope:ClientLoginRequest)
 private:
  inline void set_has_player_id();
  inline void clear_has_player_id();
  inline void set_has_player_pwd();
  inline void clear_has_player_pwd();
  inline void set_has_md5_code();
  inline void clear_has_md5_code();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* player_pwd_;
  ::std::string* md5_code_;
  ::google::protobuf::int32 player_id_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(3 + 31) / 32];

  friend void  protobuf_AddDesc_message_2eproto();
  friend void protobuf_AssignDesc_message_2eproto();
  friend void protobuf_ShutdownFile_message_2eproto();

  void InitAsDefaultInstance();
  static ClientLoginRequest* default_instance_;
};
// -------------------------------------------------------------------

class ClientLoginResponse : public ::google::protobuf::Message {
 public:
  ClientLoginResponse();
  virtual ~ClientLoginResponse();

  ClientLoginResponse(const ClientLoginResponse& from);

  inline ClientLoginResponse& operator=(const ClientLoginResponse& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const ClientLoginResponse& default_instance();

  void Swap(ClientLoginResponse* other);

  // implements Message ----------------------------------------------

  ClientLoginResponse* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const ClientLoginResponse& from);
  void MergeFrom(const ClientLoginResponse& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 ret = 1;
  inline bool has_ret() const;
  inline void clear_ret();
  static const int kRetFieldNumber = 1;
  inline ::google::protobuf::int32 ret() const;
  inline void set_ret(::google::protobuf::int32 value);

  // required string player_name = 2;
  inline bool has_player_name() const;
  inline void clear_player_name();
  static const int kPlayerNameFieldNumber = 2;
  inline const ::std::string& player_name() const;
  inline void set_player_name(const ::std::string& value);
  inline void set_player_name(const char* value);
  inline void set_player_name(const char* value, size_t size);
  inline ::std::string* mutable_player_name();
  inline ::std::string* release_player_name();
  inline void set_allocated_player_name(::std::string* player_name);

  // @@protoc_insertion_point(class_scope:ClientLoginResponse)
 private:
  inline void set_has_ret();
  inline void clear_has_ret();
  inline void set_has_player_name();
  inline void clear_has_player_name();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* player_name_;
  ::google::protobuf::int32 ret_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_message_2eproto();
  friend void protobuf_AssignDesc_message_2eproto();
  friend void protobuf_ShutdownFile_message_2eproto();

  void InitAsDefaultInstance();
  static ClientLoginResponse* default_instance_;
};
// ===================================================================


// ===================================================================

// SoccerPlayerInfoRequest

// required int32 player_id = 1;
inline bool SoccerPlayerInfoRequest::has_player_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SoccerPlayerInfoRequest::set_has_player_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SoccerPlayerInfoRequest::clear_has_player_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SoccerPlayerInfoRequest::clear_player_id() {
  player_id_ = 0;
  clear_has_player_id();
}
inline ::google::protobuf::int32 SoccerPlayerInfoRequest::player_id() const {
  return player_id_;
}
inline void SoccerPlayerInfoRequest::set_player_id(::google::protobuf::int32 value) {
  set_has_player_id();
  player_id_ = value;
}

// -------------------------------------------------------------------

// SoccerPlayerInfoResponse

// required int32 player_id = 1;
inline bool SoccerPlayerInfoResponse::has_player_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void SoccerPlayerInfoResponse::set_has_player_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void SoccerPlayerInfoResponse::clear_has_player_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void SoccerPlayerInfoResponse::clear_player_id() {
  player_id_ = 0;
  clear_has_player_id();
}
inline ::google::protobuf::int32 SoccerPlayerInfoResponse::player_id() const {
  return player_id_;
}
inline void SoccerPlayerInfoResponse::set_player_id(::google::protobuf::int32 value) {
  set_has_player_id();
  player_id_ = value;
}

// required string player_name = 2;
inline bool SoccerPlayerInfoResponse::has_player_name() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void SoccerPlayerInfoResponse::set_has_player_name() {
  _has_bits_[0] |= 0x00000002u;
}
inline void SoccerPlayerInfoResponse::clear_has_player_name() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void SoccerPlayerInfoResponse::clear_player_name() {
  if (player_name_ != &::google::protobuf::internal::kEmptyString) {
    player_name_->clear();
  }
  clear_has_player_name();
}
inline const ::std::string& SoccerPlayerInfoResponse::player_name() const {
  return *player_name_;
}
inline void SoccerPlayerInfoResponse::set_player_name(const ::std::string& value) {
  set_has_player_name();
  if (player_name_ == &::google::protobuf::internal::kEmptyString) {
    player_name_ = new ::std::string;
  }
  player_name_->assign(value);
}
inline void SoccerPlayerInfoResponse::set_player_name(const char* value) {
  set_has_player_name();
  if (player_name_ == &::google::protobuf::internal::kEmptyString) {
    player_name_ = new ::std::string;
  }
  player_name_->assign(value);
}
inline void SoccerPlayerInfoResponse::set_player_name(const char* value, size_t size) {
  set_has_player_name();
  if (player_name_ == &::google::protobuf::internal::kEmptyString) {
    player_name_ = new ::std::string;
  }
  player_name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* SoccerPlayerInfoResponse::mutable_player_name() {
  set_has_player_name();
  if (player_name_ == &::google::protobuf::internal::kEmptyString) {
    player_name_ = new ::std::string;
  }
  return player_name_;
}
inline ::std::string* SoccerPlayerInfoResponse::release_player_name() {
  clear_has_player_name();
  if (player_name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = player_name_;
    player_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void SoccerPlayerInfoResponse::set_allocated_player_name(::std::string* player_name) {
  if (player_name_ != &::google::protobuf::internal::kEmptyString) {
    delete player_name_;
  }
  if (player_name) {
    set_has_player_name();
    player_name_ = player_name;
  } else {
    clear_has_player_name();
    player_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required int32 age = 3;
inline bool SoccerPlayerInfoResponse::has_age() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void SoccerPlayerInfoResponse::set_has_age() {
  _has_bits_[0] |= 0x00000004u;
}
inline void SoccerPlayerInfoResponse::clear_has_age() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void SoccerPlayerInfoResponse::clear_age() {
  age_ = 0;
  clear_has_age();
}
inline ::google::protobuf::int32 SoccerPlayerInfoResponse::age() const {
  return age_;
}
inline void SoccerPlayerInfoResponse::set_age(::google::protobuf::int32 value) {
  set_has_age();
  age_ = value;
}

// -------------------------------------------------------------------

// ClientHeartBeatRequest

// required int32 client_time = 1;
inline bool ClientHeartBeatRequest::has_client_time() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ClientHeartBeatRequest::set_has_client_time() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ClientHeartBeatRequest::clear_has_client_time() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ClientHeartBeatRequest::clear_client_time() {
  client_time_ = 0;
  clear_has_client_time();
}
inline ::google::protobuf::int32 ClientHeartBeatRequest::client_time() const {
  return client_time_;
}
inline void ClientHeartBeatRequest::set_client_time(::google::protobuf::int32 value) {
  set_has_client_time();
  client_time_ = value;
}

// -------------------------------------------------------------------

// ClientHeartBeatResponse

// required int32 server_time = 1;
inline bool ClientHeartBeatResponse::has_server_time() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ClientHeartBeatResponse::set_has_server_time() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ClientHeartBeatResponse::clear_has_server_time() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ClientHeartBeatResponse::clear_server_time() {
  server_time_ = 0;
  clear_has_server_time();
}
inline ::google::protobuf::int32 ClientHeartBeatResponse::server_time() const {
  return server_time_;
}
inline void ClientHeartBeatResponse::set_server_time(::google::protobuf::int32 value) {
  set_has_server_time();
  server_time_ = value;
}

// -------------------------------------------------------------------

// ClientLoginRequest

// required int32 player_id = 1;
inline bool ClientLoginRequest::has_player_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ClientLoginRequest::set_has_player_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ClientLoginRequest::clear_has_player_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ClientLoginRequest::clear_player_id() {
  player_id_ = 0;
  clear_has_player_id();
}
inline ::google::protobuf::int32 ClientLoginRequest::player_id() const {
  return player_id_;
}
inline void ClientLoginRequest::set_player_id(::google::protobuf::int32 value) {
  set_has_player_id();
  player_id_ = value;
}

// required string player_pwd = 2;
inline bool ClientLoginRequest::has_player_pwd() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ClientLoginRequest::set_has_player_pwd() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ClientLoginRequest::clear_has_player_pwd() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ClientLoginRequest::clear_player_pwd() {
  if (player_pwd_ != &::google::protobuf::internal::kEmptyString) {
    player_pwd_->clear();
  }
  clear_has_player_pwd();
}
inline const ::std::string& ClientLoginRequest::player_pwd() const {
  return *player_pwd_;
}
inline void ClientLoginRequest::set_player_pwd(const ::std::string& value) {
  set_has_player_pwd();
  if (player_pwd_ == &::google::protobuf::internal::kEmptyString) {
    player_pwd_ = new ::std::string;
  }
  player_pwd_->assign(value);
}
inline void ClientLoginRequest::set_player_pwd(const char* value) {
  set_has_player_pwd();
  if (player_pwd_ == &::google::protobuf::internal::kEmptyString) {
    player_pwd_ = new ::std::string;
  }
  player_pwd_->assign(value);
}
inline void ClientLoginRequest::set_player_pwd(const char* value, size_t size) {
  set_has_player_pwd();
  if (player_pwd_ == &::google::protobuf::internal::kEmptyString) {
    player_pwd_ = new ::std::string;
  }
  player_pwd_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* ClientLoginRequest::mutable_player_pwd() {
  set_has_player_pwd();
  if (player_pwd_ == &::google::protobuf::internal::kEmptyString) {
    player_pwd_ = new ::std::string;
  }
  return player_pwd_;
}
inline ::std::string* ClientLoginRequest::release_player_pwd() {
  clear_has_player_pwd();
  if (player_pwd_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = player_pwd_;
    player_pwd_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void ClientLoginRequest::set_allocated_player_pwd(::std::string* player_pwd) {
  if (player_pwd_ != &::google::protobuf::internal::kEmptyString) {
    delete player_pwd_;
  }
  if (player_pwd) {
    set_has_player_pwd();
    player_pwd_ = player_pwd;
  } else {
    clear_has_player_pwd();
    player_pwd_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string md5_code = 3;
inline bool ClientLoginRequest::has_md5_code() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void ClientLoginRequest::set_has_md5_code() {
  _has_bits_[0] |= 0x00000004u;
}
inline void ClientLoginRequest::clear_has_md5_code() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void ClientLoginRequest::clear_md5_code() {
  if (md5_code_ != &::google::protobuf::internal::kEmptyString) {
    md5_code_->clear();
  }
  clear_has_md5_code();
}
inline const ::std::string& ClientLoginRequest::md5_code() const {
  return *md5_code_;
}
inline void ClientLoginRequest::set_md5_code(const ::std::string& value) {
  set_has_md5_code();
  if (md5_code_ == &::google::protobuf::internal::kEmptyString) {
    md5_code_ = new ::std::string;
  }
  md5_code_->assign(value);
}
inline void ClientLoginRequest::set_md5_code(const char* value) {
  set_has_md5_code();
  if (md5_code_ == &::google::protobuf::internal::kEmptyString) {
    md5_code_ = new ::std::string;
  }
  md5_code_->assign(value);
}
inline void ClientLoginRequest::set_md5_code(const char* value, size_t size) {
  set_has_md5_code();
  if (md5_code_ == &::google::protobuf::internal::kEmptyString) {
    md5_code_ = new ::std::string;
  }
  md5_code_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* ClientLoginRequest::mutable_md5_code() {
  set_has_md5_code();
  if (md5_code_ == &::google::protobuf::internal::kEmptyString) {
    md5_code_ = new ::std::string;
  }
  return md5_code_;
}
inline ::std::string* ClientLoginRequest::release_md5_code() {
  clear_has_md5_code();
  if (md5_code_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = md5_code_;
    md5_code_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void ClientLoginRequest::set_allocated_md5_code(::std::string* md5_code) {
  if (md5_code_ != &::google::protobuf::internal::kEmptyString) {
    delete md5_code_;
  }
  if (md5_code) {
    set_has_md5_code();
    md5_code_ = md5_code;
  } else {
    clear_has_md5_code();
    md5_code_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// -------------------------------------------------------------------

// ClientLoginResponse

// required int32 ret = 1;
inline bool ClientLoginResponse::has_ret() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void ClientLoginResponse::set_has_ret() {
  _has_bits_[0] |= 0x00000001u;
}
inline void ClientLoginResponse::clear_has_ret() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void ClientLoginResponse::clear_ret() {
  ret_ = 0;
  clear_has_ret();
}
inline ::google::protobuf::int32 ClientLoginResponse::ret() const {
  return ret_;
}
inline void ClientLoginResponse::set_ret(::google::protobuf::int32 value) {
  set_has_ret();
  ret_ = value;
}

// required string player_name = 2;
inline bool ClientLoginResponse::has_player_name() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void ClientLoginResponse::set_has_player_name() {
  _has_bits_[0] |= 0x00000002u;
}
inline void ClientLoginResponse::clear_has_player_name() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void ClientLoginResponse::clear_player_name() {
  if (player_name_ != &::google::protobuf::internal::kEmptyString) {
    player_name_->clear();
  }
  clear_has_player_name();
}
inline const ::std::string& ClientLoginResponse::player_name() const {
  return *player_name_;
}
inline void ClientLoginResponse::set_player_name(const ::std::string& value) {
  set_has_player_name();
  if (player_name_ == &::google::protobuf::internal::kEmptyString) {
    player_name_ = new ::std::string;
  }
  player_name_->assign(value);
}
inline void ClientLoginResponse::set_player_name(const char* value) {
  set_has_player_name();
  if (player_name_ == &::google::protobuf::internal::kEmptyString) {
    player_name_ = new ::std::string;
  }
  player_name_->assign(value);
}
inline void ClientLoginResponse::set_player_name(const char* value, size_t size) {
  set_has_player_name();
  if (player_name_ == &::google::protobuf::internal::kEmptyString) {
    player_name_ = new ::std::string;
  }
  player_name_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* ClientLoginResponse::mutable_player_name() {
  set_has_player_name();
  if (player_name_ == &::google::protobuf::internal::kEmptyString) {
    player_name_ = new ::std::string;
  }
  return player_name_;
}
inline ::std::string* ClientLoginResponse::release_player_name() {
  clear_has_player_name();
  if (player_name_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = player_name_;
    player_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void ClientLoginResponse::set_allocated_player_name(::std::string* player_name) {
  if (player_name_ != &::google::protobuf::internal::kEmptyString) {
    delete player_name_;
  }
  if (player_name) {
    set_has_player_name();
    player_name_ = player_name;
  } else {
    clear_has_player_name();
    player_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {

template <>
inline const EnumDescriptor* GetEnumDescriptor< ::MSG_ACTION_TYPE>() {
  return ::MSG_ACTION_TYPE_descriptor();
}
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::MessageType>() {
  return ::MessageType_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_message_2eproto__INCLUDED
