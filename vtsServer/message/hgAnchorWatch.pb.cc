// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hgAnchorWatch.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "hgAnchorWatch.pb.h"

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

const ::google::protobuf::Descriptor* hgAnchorWatch_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  hgAnchorWatch_reflection_ = NULL;
const ::google::protobuf::Descriptor* hgAnchorWatchRepsone_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  hgAnchorWatchRepsone_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_hgAnchorWatch_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_hgAnchorWatch_2eproto() {
  protobuf_AddDesc_hgAnchorWatch_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "hgAnchorWatch.proto");
  GOOGLE_CHECK(file != NULL);
  hgAnchorWatch_descriptor_ = file->message_type(0);
  static const int hgAnchorWatch_offsets_[6] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAnchorWatch, mmsi_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAnchorWatch, anchorwatch_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAnchorWatch, clubbing_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAnchorWatch, dragging_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAnchorWatch, lat_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAnchorWatch, lon_),
  };
  hgAnchorWatch_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      hgAnchorWatch_descriptor_,
      hgAnchorWatch::internal_default_instance(),
      hgAnchorWatch_offsets_,
      -1,
      -1,
      -1,
      sizeof(hgAnchorWatch),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAnchorWatch, _internal_metadata_));
  hgAnchorWatchRepsone_descriptor_ = file->message_type(1);
  static const int hgAnchorWatchRepsone_offsets_[1] = {
  };
  hgAnchorWatchRepsone_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      hgAnchorWatchRepsone_descriptor_,
      hgAnchorWatchRepsone::internal_default_instance(),
      hgAnchorWatchRepsone_offsets_,
      -1,
      -1,
      -1,
      sizeof(hgAnchorWatchRepsone),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgAnchorWatchRepsone, _internal_metadata_));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_hgAnchorWatch_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      hgAnchorWatch_descriptor_, hgAnchorWatch::internal_default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      hgAnchorWatchRepsone_descriptor_, hgAnchorWatchRepsone::internal_default_instance());
}

}  // namespace

void protobuf_ShutdownFile_hgAnchorWatch_2eproto() {
  hgAnchorWatch_default_instance_.Shutdown();
  delete hgAnchorWatch_reflection_;
  hgAnchorWatchRepsone_default_instance_.Shutdown();
  delete hgAnchorWatchRepsone_reflection_;
}

void protobuf_InitDefaults_hgAnchorWatch_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::GetEmptyString();
  hgAnchorWatch_default_instance_.DefaultConstruct();
  hgAnchorWatchRepsone_default_instance_.DefaultConstruct();
  hgAnchorWatch_default_instance_.get_mutable()->InitAsDefaultInstance();
  hgAnchorWatchRepsone_default_instance_.get_mutable()->InitAsDefaultInstance();
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_InitDefaults_hgAnchorWatch_2eproto_once_);
void protobuf_InitDefaults_hgAnchorWatch_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_InitDefaults_hgAnchorWatch_2eproto_once_,
                 &protobuf_InitDefaults_hgAnchorWatch_2eproto_impl);
}
void protobuf_AddDesc_hgAnchorWatch_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  protobuf_InitDefaults_hgAnchorWatch_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\023hgAnchorWatch.proto\"p\n\rhgAnchorWatch\022\014"
    "\n\004MMSI\030\001 \001(\t\022\023\n\013AnchorWatch\030\002 \001(\010\022\020\n\010Clu"
    "bbing\030\003 \001(\001\022\020\n\010Dragging\030\004 \001(\001\022\013\n\003Lat\030\005 \001"
    "(\001\022\013\n\003Lon\030\006 \001(\001\"\026\n\024hgAnchorWatchRepsoneb"
    "\006proto3", 167);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "hgAnchorWatch.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_hgAnchorWatch_2eproto);
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_hgAnchorWatch_2eproto_once_);
void protobuf_AddDesc_hgAnchorWatch_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_hgAnchorWatch_2eproto_once_,
                 &protobuf_AddDesc_hgAnchorWatch_2eproto_impl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_hgAnchorWatch_2eproto {
  StaticDescriptorInitializer_hgAnchorWatch_2eproto() {
    protobuf_AddDesc_hgAnchorWatch_2eproto();
  }
} static_descriptor_initializer_hgAnchorWatch_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD GOOGLE_ATTRIBUTE_NORETURN;
static void MergeFromFail(int line) {
  ::google::protobuf::internal::MergeFromFail(__FILE__, line);
}

}  // namespace


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int hgAnchorWatch::kMMSIFieldNumber;
const int hgAnchorWatch::kAnchorWatchFieldNumber;
const int hgAnchorWatch::kClubbingFieldNumber;
const int hgAnchorWatch::kDraggingFieldNumber;
const int hgAnchorWatch::kLatFieldNumber;
const int hgAnchorWatch::kLonFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

hgAnchorWatch::hgAnchorWatch()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (this != internal_default_instance()) protobuf_InitDefaults_hgAnchorWatch_2eproto();
  SharedCtor();
  // @@protoc_insertion_point(constructor:hgAnchorWatch)
}

void hgAnchorWatch::InitAsDefaultInstance() {
}

hgAnchorWatch::hgAnchorWatch(const hgAnchorWatch& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  UnsafeMergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:hgAnchorWatch)
}

void hgAnchorWatch::SharedCtor() {
  mmsi_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&clubbing_, 0, reinterpret_cast<char*>(&anchorwatch_) -
    reinterpret_cast<char*>(&clubbing_) + sizeof(anchorwatch_));
  _cached_size_ = 0;
}

hgAnchorWatch::~hgAnchorWatch() {
  // @@protoc_insertion_point(destructor:hgAnchorWatch)
  SharedDtor();
}

void hgAnchorWatch::SharedDtor() {
  mmsi_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void hgAnchorWatch::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* hgAnchorWatch::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return hgAnchorWatch_descriptor_;
}

const hgAnchorWatch& hgAnchorWatch::default_instance() {
  protobuf_InitDefaults_hgAnchorWatch_2eproto();
  return *internal_default_instance();
}

::google::protobuf::internal::ExplicitlyConstructed<hgAnchorWatch> hgAnchorWatch_default_instance_;

hgAnchorWatch* hgAnchorWatch::New(::google::protobuf::Arena* arena) const {
  hgAnchorWatch* n = new hgAnchorWatch;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void hgAnchorWatch::Clear() {
// @@protoc_insertion_point(message_clear_start:hgAnchorWatch)
#if defined(__clang__)
#define ZR_HELPER_(f) \
  _Pragma("clang diagnostic push") \
  _Pragma("clang diagnostic ignored \"-Winvalid-offsetof\"") \
  __builtin_offsetof(hgAnchorWatch, f) \
  _Pragma("clang diagnostic pop")
#else
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<hgAnchorWatch*>(16)->f)
#endif

#define ZR_(first, last) do {\
  ::memset(&(first), 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  ZR_(clubbing_, anchorwatch_);
  mmsi_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());

#undef ZR_HELPER_
#undef ZR_

}

bool hgAnchorWatch::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:hgAnchorWatch)
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
            "hgAnchorWatch.MMSI"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(16)) goto parse_AnchorWatch;
        break;
      }

      // optional bool AnchorWatch = 2;
      case 2: {
        if (tag == 16) {
         parse_AnchorWatch:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   bool, ::google::protobuf::internal::WireFormatLite::TYPE_BOOL>(
                 input, &anchorwatch_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(25)) goto parse_Clubbing;
        break;
      }

      // optional double Clubbing = 3;
      case 3: {
        if (tag == 25) {
         parse_Clubbing:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &clubbing_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(33)) goto parse_Dragging;
        break;
      }

      // optional double Dragging = 4;
      case 4: {
        if (tag == 33) {
         parse_Dragging:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &dragging_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(41)) goto parse_Lat;
        break;
      }

      // optional double Lat = 5;
      case 5: {
        if (tag == 41) {
         parse_Lat:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &lat_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(49)) goto parse_Lon;
        break;
      }

      // optional double Lon = 6;
      case 6: {
        if (tag == 49) {
         parse_Lon:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &lon_)));
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
  // @@protoc_insertion_point(parse_success:hgAnchorWatch)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:hgAnchorWatch)
  return false;
#undef DO_
}

void hgAnchorWatch::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:hgAnchorWatch)
  // optional string MMSI = 1;
  if (this->mmsi().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->mmsi().data(), this->mmsi().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "hgAnchorWatch.MMSI");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->mmsi(), output);
  }

  // optional bool AnchorWatch = 2;
  if (this->anchorwatch() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteBool(2, this->anchorwatch(), output);
  }

  // optional double Clubbing = 3;
  if (this->clubbing() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(3, this->clubbing(), output);
  }

  // optional double Dragging = 4;
  if (this->dragging() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(4, this->dragging(), output);
  }

  // optional double Lat = 5;
  if (this->lat() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(5, this->lat(), output);
  }

  // optional double Lon = 6;
  if (this->lon() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(6, this->lon(), output);
  }

  // @@protoc_insertion_point(serialize_end:hgAnchorWatch)
}

::google::protobuf::uint8* hgAnchorWatch::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:hgAnchorWatch)
  // optional string MMSI = 1;
  if (this->mmsi().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->mmsi().data(), this->mmsi().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "hgAnchorWatch.MMSI");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->mmsi(), target);
  }

  // optional bool AnchorWatch = 2;
  if (this->anchorwatch() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteBoolToArray(2, this->anchorwatch(), target);
  }

  // optional double Clubbing = 3;
  if (this->clubbing() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(3, this->clubbing(), target);
  }

  // optional double Dragging = 4;
  if (this->dragging() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(4, this->dragging(), target);
  }

  // optional double Lat = 5;
  if (this->lat() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(5, this->lat(), target);
  }

  // optional double Lon = 6;
  if (this->lon() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(6, this->lon(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:hgAnchorWatch)
  return target;
}

size_t hgAnchorWatch::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:hgAnchorWatch)
  size_t total_size = 0;

  // optional string MMSI = 1;
  if (this->mmsi().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->mmsi());
  }

  // optional bool AnchorWatch = 2;
  if (this->anchorwatch() != 0) {
    total_size += 1 + 1;
  }

  // optional double Clubbing = 3;
  if (this->clubbing() != 0) {
    total_size += 1 + 8;
  }

  // optional double Dragging = 4;
  if (this->dragging() != 0) {
    total_size += 1 + 8;
  }

  // optional double Lat = 5;
  if (this->lat() != 0) {
    total_size += 1 + 8;
  }

  // optional double Lon = 6;
  if (this->lon() != 0) {
    total_size += 1 + 8;
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void hgAnchorWatch::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:hgAnchorWatch)
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const hgAnchorWatch* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const hgAnchorWatch>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:hgAnchorWatch)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:hgAnchorWatch)
    UnsafeMergeFrom(*source);
  }
}

void hgAnchorWatch::MergeFrom(const hgAnchorWatch& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:hgAnchorWatch)
  if (GOOGLE_PREDICT_TRUE(&from != this)) {
    UnsafeMergeFrom(from);
  } else {
    MergeFromFail(__LINE__);
  }
}

void hgAnchorWatch::UnsafeMergeFrom(const hgAnchorWatch& from) {
  GOOGLE_DCHECK(&from != this);
  if (from.mmsi().size() > 0) {

    mmsi_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.mmsi_);
  }
  if (from.anchorwatch() != 0) {
    set_anchorwatch(from.anchorwatch());
  }
  if (from.clubbing() != 0) {
    set_clubbing(from.clubbing());
  }
  if (from.dragging() != 0) {
    set_dragging(from.dragging());
  }
  if (from.lat() != 0) {
    set_lat(from.lat());
  }
  if (from.lon() != 0) {
    set_lon(from.lon());
  }
}

void hgAnchorWatch::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:hgAnchorWatch)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void hgAnchorWatch::CopyFrom(const hgAnchorWatch& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:hgAnchorWatch)
  if (&from == this) return;
  Clear();
  UnsafeMergeFrom(from);
}

bool hgAnchorWatch::IsInitialized() const {

  return true;
}

void hgAnchorWatch::Swap(hgAnchorWatch* other) {
  if (other == this) return;
  InternalSwap(other);
}
void hgAnchorWatch::InternalSwap(hgAnchorWatch* other) {
  mmsi_.Swap(&other->mmsi_);
  std::swap(anchorwatch_, other->anchorwatch_);
  std::swap(clubbing_, other->clubbing_);
  std::swap(dragging_, other->dragging_);
  std::swap(lat_, other->lat_);
  std::swap(lon_, other->lon_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata hgAnchorWatch::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = hgAnchorWatch_descriptor_;
  metadata.reflection = hgAnchorWatch_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// hgAnchorWatch

// optional string MMSI = 1;
void hgAnchorWatch::clear_mmsi() {
  mmsi_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& hgAnchorWatch::mmsi() const {
  // @@protoc_insertion_point(field_get:hgAnchorWatch.MMSI)
  return mmsi_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void hgAnchorWatch::set_mmsi(const ::std::string& value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgAnchorWatch.MMSI)
}
void hgAnchorWatch::set_mmsi(const char* value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgAnchorWatch.MMSI)
}
void hgAnchorWatch::set_mmsi(const char* value, size_t size) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgAnchorWatch.MMSI)
}
::std::string* hgAnchorWatch::mutable_mmsi() {
  
  // @@protoc_insertion_point(field_mutable:hgAnchorWatch.MMSI)
  return mmsi_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* hgAnchorWatch::release_mmsi() {
  // @@protoc_insertion_point(field_release:hgAnchorWatch.MMSI)
  
  return mmsi_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void hgAnchorWatch::set_allocated_mmsi(::std::string* mmsi) {
  if (mmsi != NULL) {
    
  } else {
    
  }
  mmsi_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), mmsi);
  // @@protoc_insertion_point(field_set_allocated:hgAnchorWatch.MMSI)
}

// optional bool AnchorWatch = 2;
void hgAnchorWatch::clear_anchorwatch() {
  anchorwatch_ = false;
}
bool hgAnchorWatch::anchorwatch() const {
  // @@protoc_insertion_point(field_get:hgAnchorWatch.AnchorWatch)
  return anchorwatch_;
}
void hgAnchorWatch::set_anchorwatch(bool value) {
  
  anchorwatch_ = value;
  // @@protoc_insertion_point(field_set:hgAnchorWatch.AnchorWatch)
}

// optional double Clubbing = 3;
void hgAnchorWatch::clear_clubbing() {
  clubbing_ = 0;
}
double hgAnchorWatch::clubbing() const {
  // @@protoc_insertion_point(field_get:hgAnchorWatch.Clubbing)
  return clubbing_;
}
void hgAnchorWatch::set_clubbing(double value) {
  
  clubbing_ = value;
  // @@protoc_insertion_point(field_set:hgAnchorWatch.Clubbing)
}

// optional double Dragging = 4;
void hgAnchorWatch::clear_dragging() {
  dragging_ = 0;
}
double hgAnchorWatch::dragging() const {
  // @@protoc_insertion_point(field_get:hgAnchorWatch.Dragging)
  return dragging_;
}
void hgAnchorWatch::set_dragging(double value) {
  
  dragging_ = value;
  // @@protoc_insertion_point(field_set:hgAnchorWatch.Dragging)
}

// optional double Lat = 5;
void hgAnchorWatch::clear_lat() {
  lat_ = 0;
}
double hgAnchorWatch::lat() const {
  // @@protoc_insertion_point(field_get:hgAnchorWatch.Lat)
  return lat_;
}
void hgAnchorWatch::set_lat(double value) {
  
  lat_ = value;
  // @@protoc_insertion_point(field_set:hgAnchorWatch.Lat)
}

// optional double Lon = 6;
void hgAnchorWatch::clear_lon() {
  lon_ = 0;
}
double hgAnchorWatch::lon() const {
  // @@protoc_insertion_point(field_get:hgAnchorWatch.Lon)
  return lon_;
}
void hgAnchorWatch::set_lon(double value) {
  
  lon_ = value;
  // @@protoc_insertion_point(field_set:hgAnchorWatch.Lon)
}

inline const hgAnchorWatch* hgAnchorWatch::internal_default_instance() {
  return &hgAnchorWatch_default_instance_.get();
}
#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

hgAnchorWatchRepsone::hgAnchorWatchRepsone()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (this != internal_default_instance()) protobuf_InitDefaults_hgAnchorWatch_2eproto();
  SharedCtor();
  // @@protoc_insertion_point(constructor:hgAnchorWatchRepsone)
}

void hgAnchorWatchRepsone::InitAsDefaultInstance() {
}

hgAnchorWatchRepsone::hgAnchorWatchRepsone(const hgAnchorWatchRepsone& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  UnsafeMergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:hgAnchorWatchRepsone)
}

void hgAnchorWatchRepsone::SharedCtor() {
  _cached_size_ = 0;
}

hgAnchorWatchRepsone::~hgAnchorWatchRepsone() {
  // @@protoc_insertion_point(destructor:hgAnchorWatchRepsone)
  SharedDtor();
}

void hgAnchorWatchRepsone::SharedDtor() {
}

void hgAnchorWatchRepsone::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* hgAnchorWatchRepsone::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return hgAnchorWatchRepsone_descriptor_;
}

const hgAnchorWatchRepsone& hgAnchorWatchRepsone::default_instance() {
  protobuf_InitDefaults_hgAnchorWatch_2eproto();
  return *internal_default_instance();
}

::google::protobuf::internal::ExplicitlyConstructed<hgAnchorWatchRepsone> hgAnchorWatchRepsone_default_instance_;

hgAnchorWatchRepsone* hgAnchorWatchRepsone::New(::google::protobuf::Arena* arena) const {
  hgAnchorWatchRepsone* n = new hgAnchorWatchRepsone;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void hgAnchorWatchRepsone::Clear() {
// @@protoc_insertion_point(message_clear_start:hgAnchorWatchRepsone)
}

bool hgAnchorWatchRepsone::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:hgAnchorWatchRepsone)
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
  // @@protoc_insertion_point(parse_success:hgAnchorWatchRepsone)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:hgAnchorWatchRepsone)
  return false;
#undef DO_
}

void hgAnchorWatchRepsone::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:hgAnchorWatchRepsone)
  // @@protoc_insertion_point(serialize_end:hgAnchorWatchRepsone)
}

::google::protobuf::uint8* hgAnchorWatchRepsone::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:hgAnchorWatchRepsone)
  // @@protoc_insertion_point(serialize_to_array_end:hgAnchorWatchRepsone)
  return target;
}

size_t hgAnchorWatchRepsone::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:hgAnchorWatchRepsone)
  size_t total_size = 0;

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void hgAnchorWatchRepsone::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:hgAnchorWatchRepsone)
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const hgAnchorWatchRepsone* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const hgAnchorWatchRepsone>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:hgAnchorWatchRepsone)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:hgAnchorWatchRepsone)
    UnsafeMergeFrom(*source);
  }
}

void hgAnchorWatchRepsone::MergeFrom(const hgAnchorWatchRepsone& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:hgAnchorWatchRepsone)
  if (GOOGLE_PREDICT_TRUE(&from != this)) {
    UnsafeMergeFrom(from);
  } else {
    MergeFromFail(__LINE__);
  }
}

void hgAnchorWatchRepsone::UnsafeMergeFrom(const hgAnchorWatchRepsone& from) {
  GOOGLE_DCHECK(&from != this);
}

void hgAnchorWatchRepsone::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:hgAnchorWatchRepsone)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void hgAnchorWatchRepsone::CopyFrom(const hgAnchorWatchRepsone& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:hgAnchorWatchRepsone)
  if (&from == this) return;
  Clear();
  UnsafeMergeFrom(from);
}

bool hgAnchorWatchRepsone::IsInitialized() const {

  return true;
}

void hgAnchorWatchRepsone::Swap(hgAnchorWatchRepsone* other) {
  if (other == this) return;
  InternalSwap(other);
}
void hgAnchorWatchRepsone::InternalSwap(hgAnchorWatchRepsone* other) {
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata hgAnchorWatchRepsone::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = hgAnchorWatchRepsone_descriptor_;
  metadata.reflection = hgAnchorWatchRepsone_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// hgAnchorWatchRepsone

inline const hgAnchorWatchRepsone* hgAnchorWatchRepsone::internal_default_instance() {
  return &hgAnchorWatchRepsone_default_instance_.get();
}
#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
