// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: RetCode.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "RetCode.pb.h"

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

namespace qmyx {

namespace {

const ::google::protobuf::EnumDescriptor* RET_descriptor_ = NULL;

}  // namespace


void protobuf_AssignDesc_RetCode_2eproto() {
  protobuf_AddDesc_RetCode_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "RetCode.proto");
  GOOGLE_CHECK(file != NULL);
  RET_descriptor_ = file->enum_type(0);
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_RetCode_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
}

}  // namespace

void protobuf_ShutdownFile_RetCode_2eproto() {
}

void protobuf_AddDesc_RetCode_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\rRetCode.proto\022\004qmyx*\213\001\n\003RET\022\017\n\013RET_ACC"
    "OUNT\020\001\022\020\n\014RET_PASSWORD\020\002\022\022\n\016RET_ROLE_EMP"
    "TY\020\003\022\022\n\016RET_ROLE_EXIST\020\004\022\021\n\rRET_ROLE_NAM"
    "E\020\005\022\023\n\017RET_MOVE_ILLGAL\020\006\022\021\n\rRET_ROLE_ATT"
    "R\020\007", 163);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "RetCode.proto", &protobuf_RegisterTypes);
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_RetCode_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_RetCode_2eproto {
  StaticDescriptorInitializer_RetCode_2eproto() {
    protobuf_AddDesc_RetCode_2eproto();
  }
} static_descriptor_initializer_RetCode_2eproto_;
const ::google::protobuf::EnumDescriptor* RET_descriptor() {
  protobuf_AssignDescriptorsOnce();
  return RET_descriptor_;
}
bool RET_IsValid(int value) {
  switch(value) {
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


// @@protoc_insertion_point(namespace_scope)

}  // namespace qmyx

// @@protoc_insertion_point(global_scope)
