// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hgNavigatChannel.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "hgNavigatChannel.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace {

const ::google::protobuf::Descriptor* hgNavigatChannel_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  hgNavigatChannel_reflection_ = NULL;
const ::google::protobuf::Descriptor* hgNavigatChannelRepsone_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  hgNavigatChannelRepsone_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_hgNavigatChannel_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_hgNavigatChannel_2eproto() {
  protobuf_AddDesc_hgNavigatChannel_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "hgNavigatChannel.proto");
  GOOGLE_CHECK(file != NULL);
  hgNavigatChannel_descriptor_ = file->message_type(0);
  static const int hgNavigatChannel_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgNavigatChannel, mmsi_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgNavigatChannel, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgNavigatChannel, type_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgNavigatChannel, channel_),
  };
  hgNavigatChannel_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      hgNavigatChannel_descriptor_,
      hgNavigatChannel::internal_default_instance(),
      hgNavigatChannel_offsets_,
      -1,
      -1,
      -1,
      sizeof(hgNavigatChannel),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgNavigatChannel, _internal_metadata_));
  hgNavigatChannelRepsone_descriptor_ = file->message_type(1);
  static const int hgNavigatChannelRepsone_offsets_[1] = {
  };
  hgNavigatChannelRepsone_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      hgNavigatChannelRepsone_descriptor_,
      hgNavigatChannelRepsone::internal_default_instance(),
      hgNavigatChannelRepsone_offsets_,
      -1,
      -1,
      -1,
      sizeof(hgNavigatChannelRepsone),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgNavigatChannelRepsone, _internal_metadata_));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_hgNavigatChannel_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      hgNavigatChannel_descriptor_, hgNavigatChannel::internal_default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      hgNavigatChannelRepsone_descriptor_, hgNavigatChannelRepsone::internal_default_instance());
}

}  // namespace

void protobuf_ShutdownFile_hgNavigatChannel_2eproto() {
  hgNavigatChannel_default_instance_.Shutdown();
  delete hgNavigatChannel_reflection_;
  hgNavigatChannelRepsone_default_instance_.Shutdown();
  delete hgNavigatChannelRepsone_reflection_;
}

void protobuf_InitDefaults_hgNavigatChannel_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::GetEmptyString();
  hgNavigatChannel_default_instance_.DefaultConstruct();
  hgNavigatChannelRepsone_default_instance_.DefaultConstruct();
  hgNavigatChannel_default_instance_.get_mutable()->InitAsDefaultInstance();
  hgNavigatChannelRepsone_default_instance_.get_mutable()->InitAsDefaultInstance();
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_InitDefaults_hgNavigatChannel_2eproto_once_);
void protobuf_InitDefaults_hgNavigatChannel_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_InitDefaults_hgNavigatChannel_2eproto_once_,
                 &protobuf_InitDefaults_hgNavigatChannel_2eproto_impl);
}
void protobuf_AddDesc_hgNavigatChannel_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  protobuf_InitDefaults_hgNavigatChannel_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\026hgNavigatChannel.proto\"K\n\020hgNavigatCha"
    "nnel\022\014\n\004MMSI\030\001 \001(\t\022\n\n\002ID\030\002 \001(\t\022\014\n\004Type\030\003"
    " \001(\005\022\017\n\007Channel\030\004 \001(\010\"\031\n\027hgNavigatChanne"
    "lRepsoneb\006proto3", 136);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "hgNavigatChannel.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_hgNavigatChannel_2eproto);
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_hgNavigatChannel_2eproto_once_);
void protobuf_AddDesc_hgNavigatChannel_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_hgNavigatChannel_2eproto_once_,
                 &protobuf_AddDesc_hgNavigatChannel_2eproto_impl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_hgNavigatChannel_2eproto {
  StaticDescriptorInitializer_hgNavigatChannel_2eproto() {
    protobuf_AddDesc_hgNavigatChannel_2eproto();
  }
} static_descriptor_initializer_hgNavigatChannel_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD GOOGLE_ATTRIBUTE_NORETURN;
static void MergeFromFail(int line) {
  ::google::protobuf::internal::MergeFromFail(__FILE__, line);
}

}  // namespace


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int hgNavigatChannel::kMMSIFieldNumber;
const int hgNavigatChannel::kIDFieldNumber;
const int hgNavigatChannel::kTypeFieldNumber;
const int hgNavigatChannel::kChannelFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

hgNavigatChannel::hgNavigatChannel()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (this != internal_default_instance()) protobuf_InitDefaults_hgNavigatChannel_2eproto();
  SharedCtor();
  // @@protoc_insertion_point(constructor:hgNavigatChannel)
}

void hgNavigatChannel::InitAsDefaultInstance() {
}

hgNavigatChannel::hgNavigatChannel(const hgNavigatChannel& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  UnsafeMergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:hgNavigatChannel)
}

void hgNavigatChannel::SharedCtor() {
  mmsi_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  id_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&type_, 0, reinterpret_cast<char*>(&channel_) -
    reinterpret_cast<char*>(&type_) + sizeof(channel_));
  _cached_size_ = 0;
}

hgNavigatChannel::~hgNavigatChannel() {
  // @@protoc_insertion_point(destructor:hgNavigatChannel)
  SharedDtor();
}

void hgNavigatChannel::SharedDtor() {
  mmsi_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  id_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void hgNavigatChannel::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* hgNavigatChannel::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return hgNavigatChannel_descriptor_;
}

const hgNavigatChannel& hgNavigatChannel::default_instance() {
  protobuf_InitDefaults_hgNavigatChannel_2eproto();
  return *internal_default_instance();
}

::google::protobuf::internal::ExplicitlyConstructed<hgNavigatChannel> hgNavigatChannel_default_instance_;

hgNavigatChannel* hgNavigatChannel::New(::google::protobuf::Arena* arena) const {
  hgNavigatChannel* n = new hgNavigatChannel;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void hgNavigatChannel::Clear() {
// @@protoc_insertion_point(message_clear_start:hgNavigatChannel)
#if defined(__clang__)
#define ZR_HELPER_(f) \
  _Pragma("clang diagnostic push") \
  _Pragma("clang diagnostic ignored \"-Winvalid-offsetof\"") \
  __builtin_offsetof(hgNavigatChannel, f) \
  _Pragma("clang diagnostic pop")
#else
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<hgNavigatChannel*>(16)->f)
#endif

#define ZR_(first, last) do {\
  ::memset(&(first), 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  ZR_(type_, channel_);
  mmsi_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());

#undef ZR_HELPER_
#undef ZR_

}

bool hgNavigatChannel::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:hgNavigatChannel)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string MMSI = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_mmsi()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->mmsi().data(), this->mmsi().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "hgNavigatChannel.MMSI"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_ID;
        break;
      }

      // optional string ID = 2;
      case 2: {
        if (tag == 18) {
         parse_ID:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_id()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->id().data(), this->id().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "hgNavigatChannel.ID"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(24)) goto parse_Type;
        break;
      }

      // optional int32 Type = 3;
      case 3: {
        if (tag == 24) {
         parse_Type:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &type_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(32)) goto parse_Channel;
        break;
      }

      // optional bool Channel = 4;
      case 4: {
        if (tag == 32) {
         parse_Channel:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &channel_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:hgNavigatChannel)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:hgNavigatChannel)
  return false;
#undef DO_
}

void hgNavigatChannel::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:hgNavigatChannel)
  // optional string MMSI = 1;
  if (this->mmsi().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->mmsi().data(), this->mmsi().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "hgNavigatChannel.MMSI");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->mmsi(), output);
  }

  // optional string ID = 2;
  if (this->id().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->id().data(), this->id().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "hgNavigatChannel.ID");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      2, this->id(), output);
  }

  // optional int32 Type = 3;
  if (this->type() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->type(), output);
  }

  // optional bool Channel = 4;
  if (this->channel() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(4, this->channel(), output);
  }

  // @@protoc_insertion_point(serialize_end:hgNavigatChannel)
}

::google::protobuf::uint8* hgNavigatChannel::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:hgNavigatChannel)
  // optional string MMSI = 1;
  if (this->mmsi().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->mmsi().data(), this->mmsi().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "hgNavigatChannel.MMSI");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->mmsi(), target);
  }

  // optional string ID = 2;
  if (this->id().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->id().data(), this->id().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "hgNavigatChannel.ID");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->id(), target);
  }

  // optional int32 Type = 3;
  if (this->type() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->type(), target);
  }

  // optional bool Channel = 4;
  if (this->channel() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(4, this->channel(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:hgNavigatChannel)
  return target;
}

size_t hgNavigatChannel::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:hgNavigatChannel)
  size_t total_size = 0;

  // optional string MMSI = 1;
  if (this->mmsi().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->mmsi());
  }

  // optional string ID = 2;
  if (this->id().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->id());
  }

  // optional int32 Type = 3;
  if (this->type() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->type());
  }

  // optional bool Channel = 4;
  if (this->channel() != 0) {
    total_size += 1 + 1;
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void hgNavigatChannel::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:hgNavigatChannel)
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const hgNavigatChannel* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const hgNavigatChannel>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:hgNavigatChannel)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:hgNavigatChannel)
    UnsafeMergeFrom(*source);
  }
}

void hgNavigatChannel::MergeFrom(const hgNavigatChannel& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:hgNavigatChannel)
  if (GOOGLE_PREDICT_TRUE(&from != this)) {
    UnsafeMergeFrom(from);
  } else {
    MergeFromFail(__LINE__);
  }
}

void hgNavigatChannel::UnsafeMergeFrom(const hgNavigatChannel& from) {
  GOOGLE_DCHECK(&from != this);
  if (from.mmsi().size() > 0) {

    mmsi_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.mmsi_);
  }
  if (from.id().size() > 0) {

    id_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.id_);
  }
  if (from.type() != 0) {
    set_type(from.type());
  }
  if (from.channel() != 0) {
    set_channel(from.channel());
  }
}

void hgNavigatChannel::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:hgNavigatChannel)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void hgNavigatChannel::CopyFrom(const hgNavigatChannel& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:hgNavigatChannel)
  if (&from == this) return;
  Clear();
  UnsafeMergeFrom(from);
}

bool hgNavigatChannel::IsInitialized() const {

  return true;
}

void hgNavigatChannel::Swap(hgNavigatChannel* other) {
  if (other == this) return;
  InternalSwap(other);
}
void hgNavigatChannel::InternalSwap(hgNavigatChannel* other) {
  mmsi_.Swap(&other->mmsi_);
  id_.Swap(&other->id_);
  std::swap(type_, other->type_);
  std::swap(channel_, other->channel_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata hgNavigatChannel::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = hgNavigatChannel_descriptor_;
  metadata.reflection = hgNavigatChannel_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// hgNavigatChannel

// optional string MMSI = 1;
void hgNavigatChannel::clear_mmsi() {
  mmsi_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& hgNavigatChannel::mmsi() const {
  // @@protoc_insertion_point(field_get:hgNavigatChannel.MMSI)
  return mmsi_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void hgNavigatChannel::set_mmsi(const ::std::string& value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgNavigatChannel.MMSI)
}
void hgNavigatChannel::set_mmsi(const char* value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgNavigatChannel.MMSI)
}
void hgNavigatChannel::set_mmsi(const char* value, size_t size) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgNavigatChannel.MMSI)
}
::std::string* hgNavigatChannel::mutable_mmsi() {
  
  // @@protoc_insertion_point(field_mutable:hgNavigatChannel.MMSI)
  return mmsi_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* hgNavigatChannel::release_mmsi() {
  // @@protoc_insertion_point(field_release:hgNavigatChannel.MMSI)
  
  return mmsi_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void hgNavigatChannel::set_allocated_mmsi(::std::string* mmsi) {
  if (mmsi != NULL) {
    
  } else {
    
  }
  mmsi_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), mmsi);
  // @@protoc_insertion_point(field_set_allocated:hgNavigatChannel.MMSI)
}

// optional string ID = 2;
void hgNavigatChannel::clear_id() {
  id_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& hgNavigatChannel::id() const {
  // @@protoc_insertion_point(field_get:hgNavigatChannel.ID)
  return id_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void hgNavigatChannel::set_id(const ::std::string& value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgNavigatChannel.ID)
}
void hgNavigatChannel::set_id(const char* value) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgNavigatChannel.ID)
}
void hgNavigatChannel::set_id(const char* value, size_t size) {
  
  id_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgNavigatChannel.ID)
}
::std::string* hgNavigatChannel::mutable_id() {
  
  // @@protoc_insertion_point(field_mutable:hgNavigatChannel.ID)
  return id_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* hgNavigatChannel::release_id() {
  // @@protoc_insertion_point(field_release:hgNavigatChannel.ID)
  
  return id_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void hgNavigatChannel::set_allocated_id(::std::string* id) {
  if (id != NULL) {
    
  } else {
    
  }
  id_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), id);
  // @@protoc_insertion_point(field_set_allocated:hgNavigatChannel.ID)
}

// optional int32 Type = 3;
void hgNavigatChannel::clear_type() {
  type_ = 0;
}
::google::protobuf::int32 hgNavigatChannel::type() const {
  // @@protoc_insertion_point(field_get:hgNavigatChannel.Type)
  return type_;
}
void hgNavigatChannel::set_type(::google::protobuf::int32 value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:hgNavigatChannel.Type)
}

// optional bool Channel = 4;
void hgNavigatChannel::clear_channel() {
  channel_ = false;
}
bool hgNavigatChannel::channel() const {
  // @@protoc_insertion_point(field_get:hgNavigatChannel.Channel)
  return channel_;
}
void hgNavigatChannel::set_channel(bool value) {
  
  channel_ = value;
  // @@protoc_insertion_point(field_set:hgNavigatChannel.Channel)
}

inline const hgNavigatChannel* hgNavigatChannel::internal_default_instance() {
  return &hgNavigatChannel_default_instance_.get();
}
#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

hgNavigatChannelRepsone::hgNavigatChannelRepsone()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (this != internal_default_instance()) protobuf_InitDefaults_hgNavigatChannel_2eproto();
  SharedCtor();
  // @@protoc_insertion_point(constructor:hgNavigatChannelRepsone)
}

void hgNavigatChannelRepsone::InitAsDefaultInstance() {
}

hgNavigatChannelRepsone::hgNavigatChannelRepsone(const hgNavigatChannelRepsone& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  UnsafeMergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:hgNavigatChannelRepsone)
}

void hgNavigatChannelRepsone::SharedCtor() {
  _cached_size_ = 0;
}

hgNavigatChannelRepsone::~hgNavigatChannelRepsone() {
  // @@protoc_insertion_point(destructor:hgNavigatChannelRepsone)
  SharedDtor();
}

void hgNavigatChannelRepsone::SharedDtor() {
}

void hgNavigatChannelRepsone::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* hgNavigatChannelRepsone::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return hgNavigatChannelRepsone_descriptor_;
}

const hgNavigatChannelRepsone& hgNavigatChannelRepsone::default_instance() {
  protobuf_InitDefaults_hgNavigatChannel_2eproto();
  return *internal_default_instance();
}

::google::protobuf::internal::ExplicitlyConstructed<hgNavigatChannelRepsone> hgNavigatChannelRepsone_default_instance_;

hgNavigatChannelRepsone* hgNavigatChannelRepsone::New(::google::protobuf::Arena* arena) const {
  hgNavigatChannelRepsone* n = new hgNavigatChannelRepsone;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void hgNavigatChannelRepsone::Clear() {
// @@protoc_insertion_point(message_clear_start:hgNavigatChannelRepsone)
}

bool hgNavigatChannelRepsone::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:hgNavigatChannelRepsone)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
  handle_unusual:
    if (tag == 0 ||
        ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
        ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
      goto success;
    }
    DO_(::google::protobuf::internal::WireFormatLite::SkipField(input, tag));
  }
success:
  // @@protoc_insertion_point(parse_success:hgNavigatChannelRepsone)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:hgNavigatChannelRepsone)
  return false;
#undef DO_
}

void hgNavigatChannelRepsone::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:hgNavigatChannelRepsone)
  // @@protoc_insertion_point(serialize_end:hgNavigatChannelRepsone)
}

::google::protobuf::uint8* hgNavigatChannelRepsone::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:hgNavigatChannelRepsone)
  // @@protoc_insertion_point(serialize_to_array_end:hgNavigatChannelRepsone)
  return target;
}

size_t hgNavigatChannelRepsone::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:hgNavigatChannelRepsone)
  size_t total_size = 0;

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void hgNavigatChannelRepsone::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:hgNavigatChannelRepsone)
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const hgNavigatChannelRepsone* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const hgNavigatChannelRepsone>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:hgNavigatChannelRepsone)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:hgNavigatChannelRepsone)
    UnsafeMergeFrom(*source);
  }
}

void hgNavigatChannelRepsone::MergeFrom(const hgNavigatChannelRepsone& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:hgNavigatChannelRepsone)
  if (GOOGLE_PREDICT_TRUE(&from != this)) {
    UnsafeMergeFrom(from);
  } else {
    MergeFromFail(__LINE__);
  }
}

void hgNavigatChannelRepsone::UnsafeMergeFrom(const hgNavigatChannelRepsone& from) {
  GOOGLE_DCHECK(&from != this);
}

void hgNavigatChannelRepsone::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:hgNavigatChannelRepsone)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void hgNavigatChannelRepsone::CopyFrom(const hgNavigatChannelRepsone& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:hgNavigatChannelRepsone)
  if (&from == this) return;
  Clear();
  UnsafeMergeFrom(from);
}

bool hgNavigatChannelRepsone::IsInitialized() const {

  return true;
}

void hgNavigatChannelRepsone::Swap(hgNavigatChannelRepsone* other) {
  if (other == this) return;
  InternalSwap(other);
}
void hgNavigatChannelRepsone::InternalSwap(hgNavigatChannelRepsone* other) {
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata hgNavigatChannelRepsone::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = hgNavigatChannelRepsone_descriptor_;
  metadata.reflection = hgNavigatChannelRepsone_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// hgNavigatChannelRepsone

inline const hgNavigatChannelRepsone* hgNavigatChannelRepsone::internal_default_instance() {
  return &hgNavigatChannelRepsone_default_instance_.get();
}
#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)