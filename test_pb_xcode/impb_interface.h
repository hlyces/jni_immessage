
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
	inParam ����Ϊjson��
	OutParam ���Ϊ�������ֽ�������Ҫ��֤�����㹻
	seqNo �ͻ��˴�������к�
	jint ����ֵΪ������
	*/
	JNIEXPORT jint JNICALL Java_com_dffx_im_impb_impb_IMReq(JNIEnv *, jobject, IMMessageSID sid, IMMessageCID cid, jstring inParam, jbyteArray OutParam);

	/*
	inParam ����Ϊ���յ����ֽ���
	OutParam ���Ϊ������json������Ҫ��֤�����㹻
	seqNo ���ظ��ͻ��˵����к�
	jint ����ֵΪ������
	*/
	JNIEXPORT jstring JNICALL Java_com_dffx_im_impb_impb_IMRsp(JNIEnv *, jobject,  jbyteArray inParam, jbyteArray seqNo);


#else
	//
	DLL_MODIFIER bool Init();
	DLL_MODIFIER void Destroy();

	/*
	inParam ����Ϊjson��
	szOutParam ���Ϊ�������ֽ��������ⲿ�����㹻�ڴ�
	nOutLen	szOutParam�ĳ��ȣ�������Ҫ��֤�����㹻�����ʱ������Ϊ�����ĳ���
	seqNo �ͻ��˴�������к�
	int ����ֵΪ������
	*/
	DLL_MODIFIER int IMReq(IMMessageSID sid, IMMessageCID cid, const string& inParam, unsigned char* szOutParam, int& nOutLen);

	/*
	inParam ����Ϊ���յ����ֽ���
	nInLen	�����ֽ����ĳ���; ���ʱ������Ϊ�����˶��ٳ���
	OutParam ���Ϊ������json��
	seqNo ���ظ��ͻ��˵����к�
	int ����ֵΪ������
	*/
	DLL_MODIFIER int IMRsp(const unsigned char* inParam, int& nInLen, string& OutParam, int& seqNo);

#endif

#ifdef __cplusplus
}
#endif
#endif
