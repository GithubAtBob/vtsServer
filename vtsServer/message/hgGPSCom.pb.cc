// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hgGPSCom.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "hgGPSCom.pb.h"

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

const ::google::protobuf::Descriptor* hgGPSCom_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  hgGPSCom_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_hgGPSCom_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_hgGPSCom_2eproto() {
  protobuf_AddDesc_hgGPSCom_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "hgGPSCom.proto");
  GOOGLE_CHECK(file != NULL);
  hgGPSCom_descriptor_ = file->message_type(0);
  static const int hgGPSCom_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgGPSCom, gps_),
  };
  hgGPSCom_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      hgGPSCom_descriptor_,
      hgGPSCom::internal_default_instance(),
      hgGPSCom_offsets_,
      -1,
      -1,
      -1,
      sizeof(hgGPSCom),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgGPSCom, _internal_metadata_));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_hgGPSCom_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      hgGPSCom_descriptor_, hgGPSCom::internal_default_instance());
}

}  // namespace

void protobuf_ShutdownFile_hgGPSCom_2eproto() {
  hgGPSCom_default_instance_.Shutdown();
  delete hgGPSCom_reflection_;
}

void protobuf_InitDefaults_hgGPSCom_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::GetEmptyString();
  hgGPSCom_default_instance_.DefaultConstruct();
  hgGPSCom_default_instance_.get_mutable()->InitAsDefaultInstance();
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_InitDefaults_hgGPSCom_2eproto_once_);
void protobuf_InitDefaults_hgGPSCom_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_InitDefaults_hgGPSCom_2eproto_once_,
                 &protobuf_InitDefaults_hgGPSCom_2eproto_impl);
}
void protobuf_AddDesc_hgGPSCom_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  protobuf_InitDefaults_hgGPSCom_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\016hgGPSCom.proto\"\027\n\010hgGPSCom\022\013\n\003gps\030\001 \001("
    "\tb\006proto3", 49);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "hgGPSCom.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_hgGPSCom_2eproto);
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_hgGPSCom_2eproto_once_);
void protobuf_AddDesc_hgGPSCom_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_hgGPSCom_2eproto_once_,
                 &protobuf_AddDesc_hgGPSCom_2eproto_impl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_hgGPSCom_2eproto {
  StaticDescriptorInitializer_hgGPSCom_2eproto() {
    protobuf_AddDesc_hgGPSCom_2eproto();
  }
} static_descriptor_initializer_hgGPSCom_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD GOOGLE_ATTRIBUTE_NORETURN;
static void MergeFromFail(int line) {
  ::google::protobuf::internal::MergeFromFail(__FILE__, line);
}

}  // namespace


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int hgGPSCom::kGpsFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

hgGPSCom::hgGPSCom()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (this != internal_default_instance()) protobuf_InitDefaults_hgGPSCom_2eproto();
  SharedCtor();
  // @@protoc_insertion_point(constructor:hgGPSCom)
}

void hgGPSCom::InitAsDefaultInstance() {
}

hgGPSCom::hgGPSCom(const hgGPSCom& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  UnsafeMergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:hgGPSCom)
}

void hgGPSCom::SharedCtor() {
  gps_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  _cached_size_ = 0;
}

hgGPSCom::~hgGPSCom() {
  // @@protoc_insertion_point(destructor:hgGPSCom)
  SharedDtor();
}

void hgGPSCom::SharedDtor() {
  gps_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void hgGPSCom::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* hgGPSCom::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return hgGPSCom_descriptor_;
}

const hgGPSCom& hgGPSCom::default_instance() {
  protobuf_InitDefaults_hgGPSCom_2eproto();
  return *internal_default_instance();
}

::google::protobuf::internal::ExplicitlyConstructed<hgGPSCom> hgGPSCom_default_instance_;

hgGPSCom* hgGPSCom::New(::google::protobuf::Arena* arena) const {
  hgGPSCom* n = new hgGPSCom;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void hgGPSCom::Clear() {
// @@protoc_insertion_point(message_clear_start:hgGPSCom)
  gps_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

bool hgGPSCom::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:hgGPSCom)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string gps = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_gps()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->gps().data(), this->gps().length(),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "hgGPSCom.gps"));
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
  // @@protoc_insertion_point(parse_success:hgGPSCom)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:hgGPSCom)
  return false;
#undef DO_
}

void hgGPSCom::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:hgGPSCom)
  // optional string gps = 1;
  if (this->gps().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->gps().data(), this->gps().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "hgGPSCom.gps");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->gps(), output);
  }

  // @@protoc_insertion_point(serialize_end:hgGPSCom)
}

::google::protobuf::uint8* hgGPSCom::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:hgGPSCom)
  // optional string gps = 1;
  if (this->gps().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->gps().data(), this->gps().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "hgGPSCom.gps");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->gps(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:hgGPSCom)
  return target;
}

size_t hgGPSCom::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:hgGPSCom)
  size_t total_size = 0;

  // optional string gps = 1;
  if (this->gps().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->gps());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void hgGPSCom::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:hgGPSCom)
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const hgGPSCom* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const hgGPSCom>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:hgGPSCom)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:hgGPSCom)
    UnsafeMergeFrom(*source);
  }
}

void hgGPSCom::MergeFrom(const hgGPSCom& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:hgGPSCom)
  if (GOOGLE_PREDICT_TRUE(&from != this)) {
    UnsafeMergeFrom(from);
  } else {
    MergeFromFail(__LINE__);
  }
}

void hgGPSCom::UnsafeMergeFrom(const hgGPSCom& from) {
  GOOGLE_DCHECK(&from != this);
  if (from.gps().size() > 0) {

    gps_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.gps_);
  }
}

void hgGPSCom::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:hgGPSCom)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void hgGPSCom::CopyFrom(const hgGPSCom& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:hgGPSCom)
  if (&from == this) return;
  Clear();
  UnsafeMergeFrom(from);
}

bool hgGPSCom::IsInitialized() const {

  return true;
}

void hgGPSCom::Swap(hgGPSCom* other) {
  if (other == this) return;
  InternalSwap(other);
}
void hgGPSCom::InternalSwap(hgGPSCom* other) {
  gps_.Swap(&other->gps_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata hgGPSCom::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = hgGPSCom_descriptor_;
  metadata.reflection = hgGPSCom_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// hgGPSCom

// optional string gps = 1;
void hgGPSCom::clear_gps() {
  gps_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& hgGPSCom::gps() const {
  // @@protoc_insertion_point(field_get:hgGPSCom.gps)
  return gps_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void hgGPSCom::set_gps(const ::std::string& value) {
  
  gps_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgGPSCom.gps)
}
void hgGPSCom::set_gps(const char* value) {
  
  gps_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgGPSCom.gps)
}
void hgGPSCom::set_gps(const char* value, size_t size) {
  
  gps_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgGPSCom.gps)
}
::std::string* hgGPSCom::mutable_gps() {
  
  // @@protoc_insertion_point(field_mutable:hgGPSCom.gps)
  return gps_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* hgGPSCom::release_gps() {
  // @@protoc_insertion_point(field_release:hgGPSCom.gps)
  
  return gps_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void hgGPSCom::set_allocated_gps(::std::string* gps) {
  if (gps != NULL) {
    
  } else {
    
  }
  gps_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), gps);
  // @@protoc_insertion_point(field_set_allocated:hgGPSCom.gps)
}

inline const hgGPSCom* hgGPSCom::internal_default_instance() {
  return &hgGPSCom_default_instance_.get();
}
#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
