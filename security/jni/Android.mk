
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := security
LOCAL_C_INCLUDES := ./src/
LOCAL_SRC_FILES := ./src/aes_core.cpp ./src/base64.cpp ./src/md5.cpp ./src/impb_security.cpp
LOCAL_LDLIBS += -L$(SYSROOT)/usr/lib -llog
LOCAL_CFLAGS := -D__ANDROID__
#include $(BUILD_STATIC_LIBRARY)

include $(BUILD_SHARED_LIBRARY)