
#ifndef _include_impb_interface
#define _include_impb_interface

#ifdef WIN32
#if USE_DLL
#define DLL_MODIFIER _declspec(dllexport)
#else
#define DLL_MODIFIER
#endif
#else
#define DLL_MODIFIER
#endif

#include<iostream>
using namespace std;
#ifdef __cplusplus
extern "C" {
#endif

#include "imdefine.h"
using namespace IM::IMPB;

#ifdef __ANDROID__

#include <jni.h>

	JNIEXPORT jboolean JNICALL Java_com_dffx_im_impb_impb_Init(JNIEnv *, jobject);
	JNIEXPORT void JNICALL Java_com_dffx_im_impb_impb_Destroy(JNIEnv *, jobject);

	/*
	inParam 输入为json串
	OutParam 输出为编码后的字节流，需要保证长度足够
	seqNo 客户端传入的序列号
	jint 返回值为错误码
	*/
	JNIEXPORT jint JNICALL Java_com_dffx_im_impb_impb_IMReq(JNIEnv *, jobject, IMMessageSID sid, IMMessageCID cid, jstring inParam, jbyteArray OutParam);

	/*
	inParam 输入为接收到的字节流
	OutParam 输出为解码后的json串，需要保证长度足够
	seqNo 返回给客户端的序列号
	jint 返回值为错误码
	*/
	JNIEXPORT jstring JNICALL Java_com_dffx_im_impb_impb_IMRsp(JNIEnv *, jobject,  jbyteArray inParam, jbyteArray seqNo);


#else
	//
	DLL_MODIFIER bool Init();
	DLL_MODIFIER void Destroy();

	/*
	inParam 输入为json串
	szOutParam 输出为编码后的字节流，在外部分配足够内存
	nOutLen	szOutParam的长度，输入需要保证长度足够；输出时将设置为编码后的长度
	seqNo 客户端传入的序列号
	int 返回值为错误码
	*/
	DLL_MODIFIER int IMReq(IMMessageSID sid, IMMessageCID cid, const string& inParam, unsigned char* szOutParam, int& nOutLen);

	/*
	inParam 输入为接收到的字节流
	nInLen	输入字节流的长度; 输出时将设置为解码了多少长度
	OutParam 输出为解码后的json串
	seqNo 返回给客户端的序列号
	int 返回值为错误码
	*/
	DLL_MODIFIER int IMRsp(const unsigned char* inParam, int& nInLen, string& OutParam, int& seqNo);

#endif

#ifdef __cplusplus
}
#endif
#endif
