LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#LOCAL_ARM_MODE := arm
LOCAL_CPPFLAGS += -frtti
LOCAL_MODULE_CLASS := STATIC_LIBRARIES
LOCAL_MODULE := libprotobuf-lite
LOCAL_MODULE_TAGS := optional
LOCAL_CPP_EXTENSION := .cc .cpp
LOCAL_SRC_FILES := protobuf-2.6.1/src/google/protobuf/stubs/atomicops_internals_x86_msvc.cc                \
protobuf-2.6.1/src/google/protobuf/io/coded_stream.cc                   \
protobuf-2.6.1/src/google/protobuf/stubs/common.cc                    \
protobuf-2.6.1/src/google/protobuf/extension_set.cc                  \
protobuf-2.6.1/src/google/protobuf/generated_message_util.cc            \
protobuf-2.6.1/src/google/protobuf/message_lite.cc                \
protobuf-2.6.1/src/google/protobuf/stubs/once.cc                  \
protobuf-2.6.1/src/google/protobuf/repeated_field.cc            \
protobuf-2.6.1/src/google/protobuf/stubs/stringprintf.cc   \
protobuf-2.6.1/src/google/protobuf/wire_format_lite.cc         \
protobuf-2.6.1/src/google/protobuf/io/zero_copy_stream.cc                 \
protobuf-2.6.1/src/google/protobuf/io/zero_copy_stream_impl_lite.cc              \


LOCAL_C_INCLUDES += . \
./protobuf-2.6.1/src \
./protobuf-2.6.1/	\
./protobuf-2.6.1/src/google \


LOCAL_LDLIBS := -llog -lgcc 
	  
ifndef NDK_ROOT
include external/stlport/libstlport.mk
endif

include $(BUILD_STATIC_LIBRARY)
#include $(BUILD_SHARED_LIBRARY)

