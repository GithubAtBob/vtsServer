// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: test.proto

#ifndef PROTOBUF_test_2eproto__INCLUDED
#define PROTOBUF_test_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3001000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3001000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void protobuf_AddDesc_test_2eproto();
void protobuf_InitDefaults_test_2eproto();
void protobuf_AssignDesc_test_2eproto();
void protobuf_ShutdownFile_test_2eproto();

class Test;

// ===================================================================

class Test : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:Test) */ {
 public:
  Test();
  virtual ~Test();

  Test(const Test& from);

  inline Test& operator=(const Test& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Test& default_instance();

  static const Test* internal_default_instance();

  void Swap(Test* other);

  // implements Message ----------------------------------------------

  inline Test* New() const { return New(NULL); }

  Test* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Test& from);
  void MergeFrom(const Test& from);
  void Clear();
  bool IsInitialized() const;

  size_t ByteSizeLong() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(Test* other);
  void UnsafeMergeFrom(const Test& from);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string word = 1;
  bool has_word() const;
  void clear_word();
  static const int kWordFieldNumber = 1;
  const ::std::string& word() const;
  void set_word(const ::std::string& value);
  void set_word(const char* value);
  void set_word(const char* value, size_t size);
  ::std::string* mutable_word();
  ::std::string* release_word();
  void set_allocated_word(::std::string* word);

  // @@protoc_insertion_point(class_scope:Test)
 private:
  inline void set_has_word();
  inline void clear_has_word();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr word_;
  friend void  protobuf_InitDefaults_test_2eproto_impl();
  friend void  protobuf_AddDesc_test_2eproto_impl();
  friend void protobuf_AssignDesc_test_2eproto();
  friend void protobuf_ShutdownFile_test_2eproto();

  void InitAsDefaultInstance();
};
extern ::google::protobuf::internal::ExplicitlyConstructed<Test> Test_default_instance_;

// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// Test

// required string word = 1;
inline bool Test::has_word() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Test::set_has_word() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Test::clear_has_word() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Test::clear_word() {
  word_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_word();
}
inline const ::std::string& Test::word() const {
  // @@protoc_insertion_point(field_get:Test.word)
  return word_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Test::set_word(const ::std::string& value) {
  set_has_word();
  word_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Test.word)
}
inline void Test::set_word(const char* value) {
  set_has_word();
  word_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Test.word)
}
inline void Test::set_word(const char* value, size_t size) {
  set_has_word();
  word_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Test.word)
}
inline ::std::string* Test::mutable_word() {
  set_has_word();
  // @@protoc_insertion_point(field_mutable:Test.word)
  return word_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* Test::release_word() {
  // @@protoc_insertion_point(field_release:Test.word)
  clear_has_word();
  return word_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void Test::set_allocated_word(::std::string* word) {
  if (word != NULL) {
    set_has_word();
  } else {
    clear_has_word();
  }
  word_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), word);
  // @@protoc_insertion_point(field_set_allocated:Test.word)
}

inline const Test* Test::internal_default_instance() {
  return &Test_default_instance_.get();
}
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_test_2eproto__INCLUDED
