// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: hgCPA.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "hgCPA.pb.h"

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

const ::google::protobuf::Descriptor* hgCPA_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  hgCPA_reflection_ = NULL;
const ::google::protobuf::Descriptor* hgCPARepsone_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  hgCPARepsone_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_hgCPA_2eproto() GOOGLE_ATTRIBUTE_COLD;
void protobuf_AssignDesc_hgCPA_2eproto() {
  protobuf_AddDesc_hgCPA_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "hgCPA.proto");
  GOOGLE_CHECK(file != NULL);
  hgCPA_descriptor_ = file->message_type(0);
  static const int hgCPA_offsets_[9] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgCPA, mmsi_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgCPA, ownlat_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgCPA, ownlon_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgCPA, ownsog_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgCPA, owncog_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgCPA, targetlat_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgCPA, targetlon_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgCPA, targetsog_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgCPA, targetcog_),
  };
  hgCPA_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      hgCPA_descriptor_,
      hgCPA::internal_default_instance(),
      hgCPA_offsets_,
      -1,
      -1,
      -1,
      sizeof(hgCPA),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgCPA, _internal_metadata_));
  hgCPARepsone_descriptor_ = file->message_type(1);
  static const int hgCPARepsone_offsets_[3] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgCPARepsone, mmsi_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgCPARepsone, tcpa_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgCPARepsone, cpa_),
  };
  hgCPARepsone_reflection_ =
    ::google::protobuf::internal::GeneratedMessageReflection::NewGeneratedMessageReflection(
      hgCPARepsone_descriptor_,
      hgCPARepsone::internal_default_instance(),
      hgCPARepsone_offsets_,
      -1,
      -1,
      -1,
      sizeof(hgCPARepsone),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(hgCPARepsone, _internal_metadata_));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_hgCPA_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      hgCPA_descriptor_, hgCPA::internal_default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
      hgCPARepsone_descriptor_, hgCPARepsone::internal_default_instance());
}

}  // namespace

void protobuf_ShutdownFile_hgCPA_2eproto() {
  hgCPA_default_instance_.Shutdown();
  delete hgCPA_reflection_;
  hgCPARepsone_default_instance_.Shutdown();
  delete hgCPARepsone_reflection_;
}

void protobuf_InitDefaults_hgCPA_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::internal::GetEmptyString();
  hgCPA_default_instance_.DefaultConstruct();
  ::google::protobuf::internal::GetEmptyString();
  hgCPARepsone_default_instance_.DefaultConstruct();
  hgCPA_default_instance_.get_mutable()->InitAsDefaultInstance();
  hgCPARepsone_default_instance_.get_mutable()->InitAsDefaultInstance();
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_InitDefaults_hgCPA_2eproto_once_);
void protobuf_InitDefaults_hgCPA_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_InitDefaults_hgCPA_2eproto_once_,
                 &protobuf_InitDefaults_hgCPA_2eproto_impl);
}
void protobuf_AddDesc_hgCPA_2eproto_impl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  protobuf_InitDefaults_hgCPA_2eproto();
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\013hgCPA.proto\"\241\001\n\005hgCPA\022\014\n\004MMSI\030\001 \001(\t\022\016\n"
    "\006OwnLat\030\002 \001(\001\022\016\n\006OwnLon\030\003 \001(\001\022\016\n\006OwnSog\030"
    "\004 \001(\001\022\016\n\006OwnCog\030\005 \001(\001\022\021\n\tTargetLat\030\006 \001(\001"
    "\022\021\n\tTargetLon\030\007 \001(\001\022\021\n\tTargetSog\030\010 \001(\001\022\021"
    "\n\tTargetCog\030\t \001(\001\"7\n\014hgCPARepsone\022\014\n\004MMS"
    "I\030\001 \001(\t\022\014\n\004TCPA\030\002 \001(\001\022\013\n\003CPA\030\003 \001(\001b\006prot"
    "o3", 242);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "hgCPA.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_hgCPA_2eproto);
}

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AddDesc_hgCPA_2eproto_once_);
void protobuf_AddDesc_hgCPA_2eproto() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AddDesc_hgCPA_2eproto_once_,
                 &protobuf_AddDesc_hgCPA_2eproto_impl);
}
// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_hgCPA_2eproto {
  StaticDescriptorInitializer_hgCPA_2eproto() {
    protobuf_AddDesc_hgCPA_2eproto();
  }
} static_descriptor_initializer_hgCPA_2eproto_;

namespace {

static void MergeFromFail(int line) GOOGLE_ATTRIBUTE_COLD GOOGLE_ATTRIBUTE_NORETURN;
static void MergeFromFail(int line) {
  ::google::protobuf::internal::MergeFromFail(__FILE__, line);
}

}  // namespace


// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int hgCPA::kMMSIFieldNumber;
const int hgCPA::kOwnLatFieldNumber;
const int hgCPA::kOwnLonFieldNumber;
const int hgCPA::kOwnSogFieldNumber;
const int hgCPA::kOwnCogFieldNumber;
const int hgCPA::kTargetLatFieldNumber;
const int hgCPA::kTargetLonFieldNumber;
const int hgCPA::kTargetSogFieldNumber;
const int hgCPA::kTargetCogFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

hgCPA::hgCPA()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (this != internal_default_instance()) protobuf_InitDefaults_hgCPA_2eproto();
  SharedCtor();
  // @@protoc_insertion_point(constructor:hgCPA)
}

void hgCPA::InitAsDefaultInstance() {
}

hgCPA::hgCPA(const hgCPA& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  UnsafeMergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:hgCPA)
}

void hgCPA::SharedCtor() {
  mmsi_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&ownlat_, 0, reinterpret_cast<char*>(&targetcog_) -
    reinterpret_cast<char*>(&ownlat_) + sizeof(targetcog_));
  _cached_size_ = 0;
}

hgCPA::~hgCPA() {
  // @@protoc_insertion_point(destructor:hgCPA)
  SharedDtor();
}

void hgCPA::SharedDtor() {
  mmsi_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void hgCPA::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* hgCPA::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return hgCPA_descriptor_;
}

const hgCPA& hgCPA::default_instance() {
  protobuf_InitDefaults_hgCPA_2eproto();
  return *internal_default_instance();
}

::google::protobuf::internal::ExplicitlyConstructed<hgCPA> hgCPA_default_instance_;

hgCPA* hgCPA::New(::google::protobuf::Arena* arena) const {
  hgCPA* n = new hgCPA;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void hgCPA::Clear() {
// @@protoc_insertion_point(message_clear_start:hgCPA)
#if defined(__clang__)
#define ZR_HELPER_(f) \
  _Pragma("clang diagnostic push") \
  _Pragma("clang diagnostic ignored \"-Winvalid-offsetof\"") \
  __builtin_offsetof(hgCPA, f) \
  _Pragma("clang diagnostic pop")
#else
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<hgCPA*>(16)->f)
#endif

#define ZR_(first, last) do {\
  ::memset(&(first), 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  ZR_(ownlat_, targetsog_);
  mmsi_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  targetcog_ = 0;

#undef ZR_HELPER_
#undef ZR_

}

bool hgCPA::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:hgCPA)
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
            "hgCPA.MMSI"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(17)) goto parse_OwnLat;
        break;
      }

      // optional double OwnLat = 2;
      case 2: {
        if (tag == 17) {
         parse_OwnLat:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &ownlat_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(25)) goto parse_OwnLon;
        break;
      }

      // optional double OwnLon = 3;
      case 3: {
        if (tag == 25) {
         parse_OwnLon:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &ownlon_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(33)) goto parse_OwnSog;
        break;
      }

      // optional double OwnSog = 4;
      case 4: {
        if (tag == 33) {
         parse_OwnSog:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &ownsog_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(41)) goto parse_OwnCog;
        break;
      }

      // optional double OwnCog = 5;
      case 5: {
        if (tag == 41) {
         parse_OwnCog:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &owncog_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(49)) goto parse_TargetLat;
        break;
      }

      // optional double TargetLat = 6;
      case 6: {
        if (tag == 49) {
         parse_TargetLat:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &targetlat_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(57)) goto parse_TargetLon;
        break;
      }

      // optional double TargetLon = 7;
      case 7: {
        if (tag == 57) {
         parse_TargetLon:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &targetlon_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(65)) goto parse_TargetSog;
        break;
      }

      // optional double TargetSog = 8;
      case 8: {
        if (tag == 65) {
         parse_TargetSog:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &targetsog_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(73)) goto parse_TargetCog;
        break;
      }

      // optional double TargetCog = 9;
      case 9: {
        if (tag == 73) {
         parse_TargetCog:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &targetcog_)));
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
  // @@protoc_insertion_point(parse_success:hgCPA)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:hgCPA)
  return false;
#undef DO_
}

void hgCPA::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:hgCPA)
  // optional string MMSI = 1;
  if (this->mmsi().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->mmsi().data(), this->mmsi().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "hgCPA.MMSI");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->mmsi(), output);
  }

  // optional double OwnLat = 2;
  if (this->ownlat() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(2, this->ownlat(), output);
  }

  // optional double OwnLon = 3;
  if (this->ownlon() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(3, this->ownlon(), output);
  }

  // optional double OwnSog = 4;
  if (this->ownsog() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(4, this->ownsog(), output);
  }

  // optional double OwnCog = 5;
  if (this->owncog() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(5, this->owncog(), output);
  }

  // optional double TargetLat = 6;
  if (this->targetlat() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(6, this->targetlat(), output);
  }

  // optional double TargetLon = 7;
  if (this->targetlon() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(7, this->targetlon(), output);
  }

  // optional double TargetSog = 8;
  if (this->targetsog() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(8, this->targetsog(), output);
  }

  // optional double TargetCog = 9;
  if (this->targetcog() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(9, this->targetcog(), output);
  }

  // @@protoc_insertion_point(serialize_end:hgCPA)
}

::google::protobuf::uint8* hgCPA::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:hgCPA)
  // optional string MMSI = 1;
  if (this->mmsi().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->mmsi().data(), this->mmsi().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "hgCPA.MMSI");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->mmsi(), target);
  }

  // optional double OwnLat = 2;
  if (this->ownlat() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(2, this->ownlat(), target);
  }

  // optional double OwnLon = 3;
  if (this->ownlon() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(3, this->ownlon(), target);
  }

  // optional double OwnSog = 4;
  if (this->ownsog() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(4, this->ownsog(), target);
  }

  // optional double OwnCog = 5;
  if (this->owncog() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(5, this->owncog(), target);
  }

  // optional double TargetLat = 6;
  if (this->targetlat() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(6, this->targetlat(), target);
  }

  // optional double TargetLon = 7;
  if (this->targetlon() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(7, this->targetlon(), target);
  }

  // optional double TargetSog = 8;
  if (this->targetsog() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(8, this->targetsog(), target);
  }

  // optional double TargetCog = 9;
  if (this->targetcog() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(9, this->targetcog(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:hgCPA)
  return target;
}

size_t hgCPA::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:hgCPA)
  size_t total_size = 0;

  // optional string MMSI = 1;
  if (this->mmsi().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->mmsi());
  }

  // optional double OwnLat = 2;
  if (this->ownlat() != 0) {
    total_size += 1 + 8;
  }

  // optional double OwnLon = 3;
  if (this->ownlon() != 0) {
    total_size += 1 + 8;
  }

  // optional double OwnSog = 4;
  if (this->ownsog() != 0) {
    total_size += 1 + 8;
  }

  // optional double OwnCog = 5;
  if (this->owncog() != 0) {
    total_size += 1 + 8;
  }

  // optional double TargetLat = 6;
  if (this->targetlat() != 0) {
    total_size += 1 + 8;
  }

  // optional double TargetLon = 7;
  if (this->targetlon() != 0) {
    total_size += 1 + 8;
  }

  // optional double TargetSog = 8;
  if (this->targetsog() != 0) {
    total_size += 1 + 8;
  }

  // optional double TargetCog = 9;
  if (this->targetcog() != 0) {
    total_size += 1 + 8;
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void hgCPA::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:hgCPA)
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const hgCPA* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const hgCPA>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:hgCPA)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:hgCPA)
    UnsafeMergeFrom(*source);
  }
}

void hgCPA::MergeFrom(const hgCPA& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:hgCPA)
  if (GOOGLE_PREDICT_TRUE(&from != this)) {
    UnsafeMergeFrom(from);
  } else {
    MergeFromFail(__LINE__);
  }
}

void hgCPA::UnsafeMergeFrom(const hgCPA& from) {
  GOOGLE_DCHECK(&from != this);
  if (from.mmsi().size() > 0) {

    mmsi_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.mmsi_);
  }
  if (from.ownlat() != 0) {
    set_ownlat(from.ownlat());
  }
  if (from.ownlon() != 0) {
    set_ownlon(from.ownlon());
  }
  if (from.ownsog() != 0) {
    set_ownsog(from.ownsog());
  }
  if (from.owncog() != 0) {
    set_owncog(from.owncog());
  }
  if (from.targetlat() != 0) {
    set_targetlat(from.targetlat());
  }
  if (from.targetlon() != 0) {
    set_targetlon(from.targetlon());
  }
  if (from.targetsog() != 0) {
    set_targetsog(from.targetsog());
  }
  if (from.targetcog() != 0) {
    set_targetcog(from.targetcog());
  }
}

void hgCPA::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:hgCPA)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void hgCPA::CopyFrom(const hgCPA& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:hgCPA)
  if (&from == this) return;
  Clear();
  UnsafeMergeFrom(from);
}

bool hgCPA::IsInitialized() const {

  return true;
}

void hgCPA::Swap(hgCPA* other) {
  if (other == this) return;
  InternalSwap(other);
}
void hgCPA::InternalSwap(hgCPA* other) {
  mmsi_.Swap(&other->mmsi_);
  std::swap(ownlat_, other->ownlat_);
  std::swap(ownlon_, other->ownlon_);
  std::swap(ownsog_, other->ownsog_);
  std::swap(owncog_, other->owncog_);
  std::swap(targetlat_, other->targetlat_);
  std::swap(targetlon_, other->targetlon_);
  std::swap(targetsog_, other->targetsog_);
  std::swap(targetcog_, other->targetcog_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata hgCPA::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = hgCPA_descriptor_;
  metadata.reflection = hgCPA_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// hgCPA

// optional string MMSI = 1;
void hgCPA::clear_mmsi() {
  mmsi_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& hgCPA::mmsi() const {
  // @@protoc_insertion_point(field_get:hgCPA.MMSI)
  return mmsi_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void hgCPA::set_mmsi(const ::std::string& value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgCPA.MMSI)
}
void hgCPA::set_mmsi(const char* value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgCPA.MMSI)
}
void hgCPA::set_mmsi(const char* value, size_t size) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgCPA.MMSI)
}
::std::string* hgCPA::mutable_mmsi() {
  
  // @@protoc_insertion_point(field_mutable:hgCPA.MMSI)
  return mmsi_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* hgCPA::release_mmsi() {
  // @@protoc_insertion_point(field_release:hgCPA.MMSI)
  
  return mmsi_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void hgCPA::set_allocated_mmsi(::std::string* mmsi) {
  if (mmsi != NULL) {
    
  } else {
    
  }
  mmsi_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), mmsi);
  // @@protoc_insertion_point(field_set_allocated:hgCPA.MMSI)
}

// optional double OwnLat = 2;
void hgCPA::clear_ownlat() {
  ownlat_ = 0;
}
double hgCPA::ownlat() const {
  // @@protoc_insertion_point(field_get:hgCPA.OwnLat)
  return ownlat_;
}
void hgCPA::set_ownlat(double value) {
  
  ownlat_ = value;
  // @@protoc_insertion_point(field_set:hgCPA.OwnLat)
}

// optional double OwnLon = 3;
void hgCPA::clear_ownlon() {
  ownlon_ = 0;
}
double hgCPA::ownlon() const {
  // @@protoc_insertion_point(field_get:hgCPA.OwnLon)
  return ownlon_;
}
void hgCPA::set_ownlon(double value) {
  
  ownlon_ = value;
  // @@protoc_insertion_point(field_set:hgCPA.OwnLon)
}

// optional double OwnSog = 4;
void hgCPA::clear_ownsog() {
  ownsog_ = 0;
}
double hgCPA::ownsog() const {
  // @@protoc_insertion_point(field_get:hgCPA.OwnSog)
  return ownsog_;
}
void hgCPA::set_ownsog(double value) {
  
  ownsog_ = value;
  // @@protoc_insertion_point(field_set:hgCPA.OwnSog)
}

// optional double OwnCog = 5;
void hgCPA::clear_owncog() {
  owncog_ = 0;
}
double hgCPA::owncog() const {
  // @@protoc_insertion_point(field_get:hgCPA.OwnCog)
  return owncog_;
}
void hgCPA::set_owncog(double value) {
  
  owncog_ = value;
  // @@protoc_insertion_point(field_set:hgCPA.OwnCog)
}

// optional double TargetLat = 6;
void hgCPA::clear_targetlat() {
  targetlat_ = 0;
}
double hgCPA::targetlat() const {
  // @@protoc_insertion_point(field_get:hgCPA.TargetLat)
  return targetlat_;
}
void hgCPA::set_targetlat(double value) {
  
  targetlat_ = value;
  // @@protoc_insertion_point(field_set:hgCPA.TargetLat)
}

// optional double TargetLon = 7;
void hgCPA::clear_targetlon() {
  targetlon_ = 0;
}
double hgCPA::targetlon() const {
  // @@protoc_insertion_point(field_get:hgCPA.TargetLon)
  return targetlon_;
}
void hgCPA::set_targetlon(double value) {
  
  targetlon_ = value;
  // @@protoc_insertion_point(field_set:hgCPA.TargetLon)
}

// optional double TargetSog = 8;
void hgCPA::clear_targetsog() {
  targetsog_ = 0;
}
double hgCPA::targetsog() const {
  // @@protoc_insertion_point(field_get:hgCPA.TargetSog)
  return targetsog_;
}
void hgCPA::set_targetsog(double value) {
  
  targetsog_ = value;
  // @@protoc_insertion_point(field_set:hgCPA.TargetSog)
}

// optional double TargetCog = 9;
void hgCPA::clear_targetcog() {
  targetcog_ = 0;
}
double hgCPA::targetcog() const {
  // @@protoc_insertion_point(field_get:hgCPA.TargetCog)
  return targetcog_;
}
void hgCPA::set_targetcog(double value) {
  
  targetcog_ = value;
  // @@protoc_insertion_point(field_set:hgCPA.TargetCog)
}

inline const hgCPA* hgCPA::internal_default_instance() {
  return &hgCPA_default_instance_.get();
}
#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// ===================================================================

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int hgCPARepsone::kMMSIFieldNumber;
const int hgCPARepsone::kTCPAFieldNumber;
const int hgCPARepsone::kCPAFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

hgCPARepsone::hgCPARepsone()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (this != internal_default_instance()) protobuf_InitDefaults_hgCPA_2eproto();
  SharedCtor();
  // @@protoc_insertion_point(constructor:hgCPARepsone)
}

void hgCPARepsone::InitAsDefaultInstance() {
}

hgCPARepsone::hgCPARepsone(const hgCPARepsone& from)
  : ::google::protobuf::Message(),
    _internal_metadata_(NULL) {
  SharedCtor();
  UnsafeMergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:hgCPARepsone)
}

void hgCPARepsone::SharedCtor() {
  mmsi_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ::memset(&tcpa_, 0, reinterpret_cast<char*>(&cpa_) -
    reinterpret_cast<char*>(&tcpa_) + sizeof(cpa_));
  _cached_size_ = 0;
}

hgCPARepsone::~hgCPARepsone() {
  // @@protoc_insertion_point(destructor:hgCPARepsone)
  SharedDtor();
}

void hgCPARepsone::SharedDtor() {
  mmsi_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void hgCPARepsone::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* hgCPARepsone::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return hgCPARepsone_descriptor_;
}

const hgCPARepsone& hgCPARepsone::default_instance() {
  protobuf_InitDefaults_hgCPA_2eproto();
  return *internal_default_instance();
}

::google::protobuf::internal::ExplicitlyConstructed<hgCPARepsone> hgCPARepsone_default_instance_;

hgCPARepsone* hgCPARepsone::New(::google::protobuf::Arena* arena) const {
  hgCPARepsone* n = new hgCPARepsone;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void hgCPARepsone::Clear() {
// @@protoc_insertion_point(message_clear_start:hgCPARepsone)
#if defined(__clang__)
#define ZR_HELPER_(f) \
  _Pragma("clang diagnostic push") \
  _Pragma("clang diagnostic ignored \"-Winvalid-offsetof\"") \
  __builtin_offsetof(hgCPARepsone, f) \
  _Pragma("clang diagnostic pop")
#else
#define ZR_HELPER_(f) reinterpret_cast<char*>(\
  &reinterpret_cast<hgCPARepsone*>(16)->f)
#endif

#define ZR_(first, last) do {\
  ::memset(&(first), 0,\
           ZR_HELPER_(last) - ZR_HELPER_(first) + sizeof(last));\
} while (0)

  ZR_(tcpa_, cpa_);
  mmsi_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());

#undef ZR_HELPER_
#undef ZR_

}

bool hgCPARepsone::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:hgCPARepsone)
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
            "hgCPARepsone.MMSI"));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(17)) goto parse_TCPA;
        break;
      }

      // optional double TCPA = 2;
      case 2: {
        if (tag == 17) {
         parse_TCPA:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &tcpa_)));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(25)) goto parse_CPA;
        break;
      }

      // optional double CPA = 3;
      case 3: {
        if (tag == 25) {
         parse_CPA:

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &cpa_)));
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
  // @@protoc_insertion_point(parse_success:hgCPARepsone)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:hgCPARepsone)
  return false;
#undef DO_
}

void hgCPARepsone::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:hgCPARepsone)
  // optional string MMSI = 1;
  if (this->mmsi().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->mmsi().data(), this->mmsi().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "hgCPARepsone.MMSI");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->mmsi(), output);
  }

  // optional double TCPA = 2;
  if (this->tcpa() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(2, this->tcpa(), output);
  }

  // optional double CPA = 3;
  if (this->cpa() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(3, this->cpa(), output);
  }

  // @@protoc_insertion_point(serialize_end:hgCPARepsone)
}

::google::protobuf::uint8* hgCPARepsone::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:hgCPARepsone)
  // optional string MMSI = 1;
  if (this->mmsi().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->mmsi().data(), this->mmsi().length(),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "hgCPARepsone.MMSI");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->mmsi(), target);
  }

  // optional double TCPA = 2;
  if (this->tcpa() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(2, this->tcpa(), target);
  }

  // optional double CPA = 3;
  if (this->cpa() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(3, this->cpa(), target);
  }

  // @@protoc_insertion_point(serialize_to_array_end:hgCPARepsone)
  return target;
}

size_t hgCPARepsone::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:hgCPARepsone)
  size_t total_size = 0;

  // optional string MMSI = 1;
  if (this->mmsi().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->mmsi());
  }

  // optional double TCPA = 2;
  if (this->tcpa() != 0) {
    total_size += 1 + 8;
  }

  // optional double CPA = 3;
  if (this->cpa() != 0) {
    total_size += 1 + 8;
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void hgCPARepsone::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:hgCPARepsone)
  if (GOOGLE_PREDICT_FALSE(&from == this)) MergeFromFail(__LINE__);
  const hgCPARepsone* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const hgCPARepsone>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:hgCPARepsone)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:hgCPARepsone)
    UnsafeMergeFrom(*source);
  }
}

void hgCPARepsone::MergeFrom(const hgCPARepsone& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:hgCPARepsone)
  if (GOOGLE_PREDICT_TRUE(&from != this)) {
    UnsafeMergeFrom(from);
  } else {
    MergeFromFail(__LINE__);
  }
}

void hgCPARepsone::UnsafeMergeFrom(const hgCPARepsone& from) {
  GOOGLE_DCHECK(&from != this);
  if (from.mmsi().size() > 0) {

    mmsi_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.mmsi_);
  }
  if (from.tcpa() != 0) {
    set_tcpa(from.tcpa());
  }
  if (from.cpa() != 0) {
    set_cpa(from.cpa());
  }
}

void hgCPARepsone::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:hgCPARepsone)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void hgCPARepsone::CopyFrom(const hgCPARepsone& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:hgCPARepsone)
  if (&from == this) return;
  Clear();
  UnsafeMergeFrom(from);
}

bool hgCPARepsone::IsInitialized() const {

  return true;
}

void hgCPARepsone::Swap(hgCPARepsone* other) {
  if (other == this) return;
  InternalSwap(other);
}
void hgCPARepsone::InternalSwap(hgCPARepsone* other) {
  mmsi_.Swap(&other->mmsi_);
  std::swap(tcpa_, other->tcpa_);
  std::swap(cpa_, other->cpa_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  std::swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata hgCPARepsone::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = hgCPARepsone_descriptor_;
  metadata.reflection = hgCPARepsone_reflection_;
  return metadata;
}

#if PROTOBUF_INLINE_NOT_IN_HEADERS
// hgCPARepsone

// optional string MMSI = 1;
void hgCPARepsone::clear_mmsi() {
  mmsi_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
const ::std::string& hgCPARepsone::mmsi() const {
  // @@protoc_insertion_point(field_get:hgCPARepsone.MMSI)
  return mmsi_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void hgCPARepsone::set_mmsi(const ::std::string& value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:hgCPARepsone.MMSI)
}
void hgCPARepsone::set_mmsi(const char* value) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:hgCPARepsone.MMSI)
}
void hgCPARepsone::set_mmsi(const char* value, size_t size) {
  
  mmsi_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:hgCPARepsone.MMSI)
}
::std::string* hgCPARepsone::mutable_mmsi() {
  
  // @@protoc_insertion_point(field_mutable:hgCPARepsone.MMSI)
  return mmsi_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
::std::string* hgCPARepsone::release_mmsi() {
  // @@protoc_insertion_point(field_release:hgCPARepsone.MMSI)
  
  return mmsi_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
void hgCPARepsone::set_allocated_mmsi(::std::string* mmsi) {
  if (mmsi != NULL) {
    
  } else {
    
  }
  mmsi_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), mmsi);
  // @@protoc_insertion_point(field_set_allocated:hgCPARepsone.MMSI)
}

// optional double TCPA = 2;
void hgCPARepsone::clear_tcpa() {
  tcpa_ = 0;
}
double hgCPARepsone::tcpa() const {
  // @@protoc_insertion_point(field_get:hgCPARepsone.TCPA)
  return tcpa_;
}
void hgCPARepsone::set_tcpa(double value) {
  
  tcpa_ = value;
  // @@protoc_insertion_point(field_set:hgCPARepsone.TCPA)
}

// optional double CPA = 3;
void hgCPARepsone::clear_cpa() {
  cpa_ = 0;
}
double hgCPARepsone::cpa() const {
  // @@protoc_insertion_point(field_get:hgCPARepsone.CPA)
  return cpa_;
}
void hgCPARepsone::set_cpa(double value) {
  
  cpa_ = value;
  // @@protoc_insertion_point(field_set:hgCPARepsone.CPA)
}

inline const hgCPARepsone* hgCPARepsone::internal_default_instance() {
  return &hgCPARepsone_default_instance_.get();
}
#endif  // PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)
