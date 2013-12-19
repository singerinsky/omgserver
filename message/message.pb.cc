// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: message.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "message.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* SoccerPlayerInfo_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  SoccerPlayerInfo_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_message_2eproto() {
  protobuf_AddDesc_message_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "message.proto");
  GOOGLE_CHECK(file != NULL);
  SoccerPlayerInfo_descriptor_ = file->message_type(0);
  static const int SoccerPlayerInfo_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SoccerPlayerInfo, player_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SoccerPlayerInfo, player_name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SoccerPlayerInfo, age_),
  };
  SoccerPlayerInfo_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      SoccerPlayerInfo_descriptor_,
      SoccerPlayerInfo::default_instance_,
      SoccerPlayerInfo_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SoccerPlayerInfo, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(SoccerPlayerInfo, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(SoccerPlayerInfo));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_message_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    SoccerPlayerInfo_descriptor_, &SoccerPlayerInfo::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_message_2eproto() {
  delete SoccerPlayerInfo::default_instance_;
  delete SoccerPlayerInfo_reflection_;
}

void protobuf_AddDesc_message_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\rmessage.proto\"G\n\020SoccerPlayerInfo\022\021\n\tp"
    "layer_id\030\001 \002(\005\022\023\n\013player_name\030\002 \002(\t\022\013\n\003a"
    "ge\030\003 \002(\005", 88);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "message.proto", &protobuf_RegisterTypes);
  SoccerPlayerInfo::default_instance_ = new SoccerPlayerInfo();
  SoccerPlayerInfo::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_message_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_message_2eproto {
  StaticDescriptorInitializer_message_2eproto() {
    protobuf_AddDesc_message_2eproto();
  }
} static_descriptor_initializer_message_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int SoccerPlayerInfo::kPlayerIdFieldNumber;
const int SoccerPlayerInfo::kPlayerNameFieldNumber;
const int SoccerPlayerInfo::kAgeFieldNumber;
#endif  // !_MSC_VER

SoccerPlayerInfo::SoccerPlayerInfo()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void SoccerPlayerInfo::InitAsDefaultInstance() {
}

SoccerPlayerInfo::SoccerPlayerInfo(const SoccerPlayerInfo& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void SoccerPlayerInfo::SharedCtor() {
  _cached_size_ = 0;
  player_id_ = 0;
  player_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  age_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

SoccerPlayerInfo::~SoccerPlayerInfo() {
  SharedDtor();
}

void SoccerPlayerInfo::SharedDtor() {
  if (player_name_ != &::google::protobuf::internal::kEmptyString) {
    delete player_name_;
  }
  if (this != default_instance_) {
  }
}

void SoccerPlayerInfo::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* SoccerPlayerInfo::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return SoccerPlayerInfo_descriptor_;
}

const SoccerPlayerInfo& SoccerPlayerInfo::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_message_2eproto();
  return *default_instance_;
}

SoccerPlayerInfo* SoccerPlayerInfo::default_instance_ = NULL;

SoccerPlayerInfo* SoccerPlayerInfo::New() const {
  return new SoccerPlayerInfo;
}

void SoccerPlayerInfo::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    player_id_ = 0;
    if (has_player_name()) {
      if (player_name_ != &::google::protobuf::internal::kEmptyString) {
        player_name_->clear();
      }
    }
    age_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool SoccerPlayerInfo::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required int32 player_id = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &player_id_)));
          set_has_player_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_player_name;
        break;
      }

      // required string player_name = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_player_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_player_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->player_name().data(), this->player_name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_age;
        break;
      }

      // required int32 age = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_age:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &age_)));
          set_has_age();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void SoccerPlayerInfo::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required int32 player_id = 1;
  if (has_player_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->player_id(), output);
  }

  // required string player_name = 2;
  if (has_player_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->player_name().data(), this->player_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->player_name(), output);
  }

  // required int32 age = 3;
  if (has_age()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->age(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* SoccerPlayerInfo::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required int32 player_id = 1;
  if (has_player_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->player_id(), target);
  }

  // required string player_name = 2;
  if (has_player_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->player_name().data(), this->player_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->player_name(), target);
  }

  // required int32 age = 3;
  if (has_age()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->age(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int SoccerPlayerInfo::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required int32 player_id = 1;
    if (has_player_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->player_id());
    }

    // required string player_name = 2;
    if (has_player_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->player_name());
    }

    // required int32 age = 3;
    if (has_age()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->age());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void SoccerPlayerInfo::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const SoccerPlayerInfo* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const SoccerPlayerInfo*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void SoccerPlayerInfo::MergeFrom(const SoccerPlayerInfo& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_player_id()) {
      set_player_id(from.player_id());
    }
    if (from.has_player_name()) {
      set_player_name(from.player_name());
    }
    if (from.has_age()) {
      set_age(from.age());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void SoccerPlayerInfo::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SoccerPlayerInfo::CopyFrom(const SoccerPlayerInfo& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SoccerPlayerInfo::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  return true;
}

void SoccerPlayerInfo::Swap(SoccerPlayerInfo* other) {
  if (other != this) {
    std::swap(player_id_, other->player_id_);
    std::swap(player_name_, other->player_name_);
    std::swap(age_, other->age_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata SoccerPlayerInfo::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = SoccerPlayerInfo_descriptor_;
  metadata.reflection = SoccerPlayerInfo_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
