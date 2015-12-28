
LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

#LOCAL_ARM_MODE := arm
LOCAL_CPPFLAGS := -fexceptions -frtti  \
	-D__ANDROID__  -D_GLIBCXX_PERMIT_BACKWARD_HASH
LOCAL_CPP_EXTENSION := .cc .cpp
LOCAL_CFLAGS = -Wno-psabi  
LOCAL_MODULE    := impb
LOCAL_SRC_FILES := \
 ./protocol/IM.BaseDefine.pb.cc \
 ./protocol/IM.Buddy.pb.cc \
 ./protocol/IM.File.pb.cc \
 ./protocol/IM.Group.pb.cc \
 ./protocol/IM.Login.pb.cc \
 ./protocol/IM.Message.pb.cc \
 ./protocol/IM.Other.pb.cc \
 ./protocol/IM.SwitchService.pb.cc \
 \
 ./jsoncpp/json_reader.cpp \
 ./jsoncpp/json_value.cpp \
 ./jsoncpp/json_writer.cpp \
 \
 ./apply/ImPduBase.cpp \
 ./apply/UtilPdu.cpp \
 \
 ./apply/IMLogin.cpp \
 ./apply/IMMessage.cpp \
 ./apply/IMFile.cpp \
 ./apply/IMBuddy.cpp \
 ./apply/IMSwitchService.cpp \
 ./apply/IMOther.cpp \
 ./apply/IMGroup.cpp \
 ./src/impb_interface.cpp \
 

LOCAL_C_INCLUDES := ./include\
./include/security/ \
./protocol/ \
./jsoncpp/ \
./jsoncpp/json/ \
./apply/ \
./src \

#LOCAL_LDLIBS    := -L./lib/armeabi -lprotobuf-lite -lsecurity -llog 
LOCAL_LDLIBS    := -L./lib/armeabi-v7a -lprotobuf-lite -lsecurity -llog
#LOCAL_LDLIBS    := -L./lib/x86 -lprotobuf-lite -lsecurity -llog -lgcc

ifndef NDK_ROOT
	include external/stlport/libstlport.mk
endif

include $(BUILD_SHARED_LIBRARY)
#include $(BUILD_STATIC_LIBRARY)