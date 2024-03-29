// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: AlgorithmMode.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "AlgorithmMode.pb.h"

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

const ::google::protobuf::Descriptor* hgAlgorithmMode_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  hgAlgorithmMode_reflection_ = NULL;
const ::google::protobuf::EnumDescriptor* AlgorithmModeType_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_AlgorithmMode_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_AlgorithmMode_2eproto() {
  protobuf_AddDesc_AlgorithmMode_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "AlgorithmMode.proto");
  GOOGLE_CHECK(file != NULL);
  hgAlgorithmMode_descriptor_ = file->message_type(0);
  static const int hgAlgorithmMode_offsets_[4] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAlgorithmMode, mode_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAlgorithmMode, alarm1_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAlgorithmMode, alarm2_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAlgorithmMode, alarm3_),
  };
  hgAlgorithmMode_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      hgAlgorithmMode_descriptor_,
      hgAlgorithmMode::internal_default_instance(),
      hgAlgorithmMode_offsets_,
      -1,
      -1,
      -1,
      sizeof(hgAlgorithmMode),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAlgorithmMode, _internal_metadata_));
  AlgorithmModeType_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_AlgorithmMode_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      hgAlgorithmMode_descriptor_, hgAlgorithmMode::internal_default_instance());
}

}  // namespace

void protobuf_ShutdownFile_AlgorithmMode_2eproto() {
  hgAlgorithmMode_default_instance_.Shutdown();
  delete hgAlgorithmMode_reflection_;
}

void protobuf_InitDefaults_AlgorithmMode_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  hgAlgorithmMode_default_instance_.DefaultConstruct();
  hgAlgorithmMode_default_instance_.get_mutable()->InitAsDefaultInstance();
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_InitDefaults_AlgorithmMode_2eproto_once_);
void protobuf_InitDefaults_AlgorithmMode_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_InitDefaults_AlgorithmMode_2eproto_once_,
                 &protobuf_InitDefaults_AlgorithmMode_2eproto_impl);
}
void protobuf_AddDesc_AlgorithmMode_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  protobuf_InitDefaults_AlgorithmMode_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\023AlgorithmMode.proto\"O\n\017hgAlgorithmMode"
    "\022\014\n\004mode\030\001 \001(\005\022\016\n\006alarm1\030\002 \001(\001\022\016\n\006alarm2"
    "\030\003 \001(\001\022\016\n\006alarm3\030\004 \001(\001*\224\001\n\021AlgorithmMode"
    "Type\022\016\n\nEarlyModel\020\000\022\017\n\013ManualModel\020\001\022\r\n"
    "\tAutoModel\020\002\022\r\n\tNoneModel\020\003\022\014\n\010AskModel\020"
    "\004\022\014\n\010SetModel\020\005\022\022\n\016SetManualModel\020\006\022\020\n\014S"
    "etAutoModel\020\007b\006proto3", 261);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "AlgorithmMode.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_AlgorithmMode_2eproto);
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_AlgorithmMode_2eproto_once_);
void protobuf_AddDesc_AlgorithmMode_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_AlgorithmMode_2eproto_once_,
                 &protobuf_AddDesc_AlgorithmMode_2eproto_impl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_AlgorithmMode_2eproto {
  StaticDescriptorInitializer_AlgorithmMode_2eproto() {
    protobuf_AddDesc_AlgorithmMode_2eproto();
  }
} static_descriptor_initializer_AlgorithmMode_2eproto_;
const ::google::protobuf::EnumDescriptor* AlgorithmModeType_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return AlgorithmModeType_descriptor_;
}
bool AlgorithmModeType_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
      return true;
    default:
      return false;
  }
}


namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD GOOGLE_ATTRIBUTE_NORETURN;
static void MergeFromFail(int line) {
  ::google::protobuf::internal::MergeFromFail(__FILE__, line);
}

}  // namespace


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int hgAlgorithmMode::kModeFieldNumber;
const int hgAlgorithmMode::kAlarm1FieldNumber;
const int hgAlgorithmMode::kAlarm2FieldNumber;
const int hgAlgorithmMode::kAlarm3FieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

hgAlgorithmMode::hgAlgorithmMode()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (this != internal_default_instance()) protobuf_InitDefaults_AlgorithmMode_2eproto();
  SharedCtor();
  // @@protoc_insertion_point(constructor:hgAlgorithmMode)
}

void hgAlgorithmMode::InitAsDefaultInstance() {
}

hgAlgorithmMode::hgAlgorithmMode(const hgAlgorithmMode& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  UnsafeMergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:hgAlgorithmMode)
}

void hgAlgorithmMode::SharedCtor() {
  ::memset(&alarm1_, 0, reinterpret_cast<char*>(&mode_) -
    reinterpret_cast<char*>(&alarm1_) + sizeof(mode_));
  _cached_size_ = 0;
}

hgAlgorithmMode::~hgAlgorithmMode() {
  // @@protoc_insertion_point(destructor:hgAlgorithmMode)
  SharedDtor();
}

void hgAlgorithmMode::SharedDtor() {
}

void hgAlgorithmMode::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* hgAlgorithmMode::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return hgAlgorithmMode_descriptor_;
}

const hgAlgorithmMode& hgAlgorithmMode::default_instance() {
  protobuf_InitDefaults_AlgorithmMode_2eproto();
  return *internal_default_instance();
}

::google::protobuf::internal::ExplicitlyConstructed<hgAlgorithmMode> hgAlgorithmMode_default_instance_;

hgAlgorithmMode* hgAlgorithmMode::New(::google::protobuf::Arena* arena) const {
  hgAlgorithmMode* n = new hgAlgorithmMode;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void hgAlgorithmMode::Clear() {
// @@protoc_insertion_point(message_clear_start:hgAlgorithmMode)
#if defined(__clang__)
#define ZR_HELPER_(f) \
  _Pragma("clang diagnostic push") \
  _Pragma("clang diagnostic ignored \"-Winvalid-offsetof\"") \
  __builtin_offsetof(hgAlgorithmMode, f) \
  _Pragma("clang diagnostic pop")
#else
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<hgAlgorithmMode*>(16)->f)
#endif

#define ZR_(first, last) do {\
  ::memset(&(first), 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  ZR_(alarm1_, mode_);

#undef ZR_HELPER_
#undef ZR_

}

bool hgAlgorithmMode::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:hgAlgorithmMode)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional int32 mode = 1;
      case 1: {
        if (tag == 8) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &mode_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(17)) goto parse_alarm1;
        break;
      }

      // optional double alarm1 = 2;
      case 2: {
        if (tag == 17) {
         parse_alarm1:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &alarm1_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(25)) goto parse_alarm2;
        break;
      }

      // optional double alarm2 = 3;
      case 3: {
        if (tag == 25) {
         parse_alarm2:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &alarm2_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(33)) goto parse_alarm3;
        break;
      }

      // optional double alarm3 = 4;
      case 4: {
        if (tag == 33) {
         parse_alarm3:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &alarm3_)));
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
  // @@protoc_insertion_point(parse_success:hgAlgorithmMode)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:hgAlgorithmMode)
  return false;
#undef DO_
}

void hgAlgorithmMode::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:hgAlgorithmMode)
  // optional int32 mode = 1;
  if (this->mode() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->mode(), output);
  }

  // optional double alarm1 = 2;
  if (this->alarm1() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(2, this->alarm1(), output);
  }

  // optional double alarm2 = 3;
  if (this->alarm2() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(3, this->alarm2(), output);
  }

  // optional double alarm3 = 4;
  if (this->alarm3() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(4, this->alarm3(), output);
  }

  // @@protoc_insertion_point(serialize_end:hgAlgorithmMode)
}

::google::protobuf::uint8* hgAlgorithmMode::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:hgAlgorithmMode)
  // optional int32 mode = 1;
  if (this->mode() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->mode(), target);
  }

  // optional double alarm1 = 2;
  if (this->alarm1() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(2, this->alarm1(), target);
  }

  // optional double alarm2 = 3;
  if (this->alarm2() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(3, this->alarm2(), target);
  }

  // optional double alarm3 = 4;
  if (this->alarm3() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(4, this->alarm3(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:hgAlgorithmMode)
  return target;
}

size_t hgAlgorithmMode::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:hgAlgorithmMode)
  size_t total_size = 0;

  // optional int32 mode = 1;
  if (this->mode() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->mode());
  }

  // optional double alarm1 = 2;
  if (this->alarm1() != 0) {
    total_size += 1 + 8;
  }

  // optional double alarm2 = 3;
  if (this->alarm2() != 0) {
    total_size += 1 + 8;
  }

  // optional double alarm3 = 4;
  if (this->alarm3() != 0) {
    total_size += 1 + 8;
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void hgAlgorithmMode::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:hgAlgorithmMode)
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const hgAlgorithmMode* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const hgAlgorithmMode>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:hgAlgorithmMode)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:hgAlgorithmMode)
    UnsafeMergeFrom(*source);
  }
}

void hgAlgorithmMode::MergeFrom(const hgAlgorithmMode& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:hgAlgorithmMode)
  if (GOOGLE_PREDICT_TRUE(&from != this)) {
    UnsafeMergeFrom(from);
  } else {
    MergeFromFail(__LINE__);
  }
}

void hgAlgorithmMode::UnsafeMergeFrom(const hgAlgorithmMode& from) {
  GOOGLE_DCHECK(&from != this);
  if (from.mode() != 0) {
    set_mode(from.mode());
  }
  if (from.alarm1() != 0) {
    set_alarm1(from.alarm1());
  }
  if (from.alarm2() != 0) {
    set_alarm2(from.alarm2());
  }
  if (from.alarm3() != 0) {
    set_alarm3(from.alarm3());
  }
}

void hgAlgorithmMode::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:hgAlgorithmMode)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void hgAlgorithmMode::CopyFrom(const hgAlgorithmMode& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:hgAlgorithmMode)
  if (&from == this) return;
  Clear();
  UnsafeMergeFrom(from);
}

bool hgAlgorithmMode::IsInitialized() const {

  return true;
}

void hgAlgorithmMode::Swap(hgAlgorithmMode* other) {
  if (other == this) return;
  InternalSwap(other);
}
void hgAlgorithmMode::InternalSwap(hgAlgorithmMode* other) {
  std::swap(mode_, other->mode_);
  std::swap(alarm1_, other->alarm1_);
  std::swap(alarm2_, other->alarm2_);
  std::swap(alarm3_, other->alarm3_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata hgAlgorithmMode::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = hgAlgorithmMode_descriptor_;
  metadata.reflection = hgAlgorithmMode_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// hgAlgorithmMode

// optional int32 mode = 1;
void hgAlgorithmMode::clear_mode() {
  mode_ = 0;
}
::google::protobuf::int32 hgAlgorithmMode::mode() const {
  // @@protoc_insertion_point(field_get:hgAlgorithmMode.mode)
  return mode_;
}
void hgAlgorithmMode::set_mode(::google::protobuf::int32 value) {
  
  mode_ = value;
  // @@protoc_insertion_point(field_set:hgAlgorithmMode.mode)
}

// optional double alarm1 = 2;
void hgAlgorithmMode::clear_alarm1() {
  alarm1_ = 0;
}
double hgAlgorithmMode::alarm1() const {
  // @@protoc_insertion_point(field_get:hgAlgorithmMode.alarm1)
  return alarm1_;
}
void hgAlgorithmMode::set_alarm1(double value) {
  
  alarm1_ = value;
  // @@protoc_insertion_point(field_set:hgAlgorithmMode.alarm1)
}

// optional double alarm2 = 3;
void hgAlgorithmMode::clear_alarm2() {
  alarm2_ = 0;
}
double hgAlgorithmMode::alarm2() const {
  // @@protoc_insertion_point(field_get:hgAlgorithmMode.alarm2)
  return alarm2_;
}
void hgAlgorithmMode::set_alarm2(double value) {
  
  alarm2_ = value;
  // @@protoc_insertion_point(field_set:hgAlgorithmMode.alarm2)
}

// optional double alarm3 = 4;
void hgAlgorithmMode::clear_alarm3() {
  alarm3_ = 0;
}
double hgAlgorithmMode::alarm3() const {
  // @@protoc_insertion_point(field_get:hgAlgorithmMode.alarm3)
  return alarm3_;
}
void hgAlgorithmMode::set_alarm3(double value) {
  
  alarm3_ = value;
  // @@protoc_insertion_point(field_set:hgAlgorithmMode.alarm3)
}

inline const hgAlgorithmMode* hgAlgorithmMode::internal_default_instance() {
  return &hgAlgorithmMode_default_instance_.get();
}
#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
