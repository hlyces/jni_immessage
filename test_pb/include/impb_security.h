/*================================================================
*   Copyright (C) 2015 All rights reserved.
*   
*   �ļ����ƣ�security.h
*   �� �� �ߣ�Zhang Yuanhao
*   ��    �䣺bluefoxah@gmail.com
*   �������ڣ�2015��01��29��
*   ��    ����
*
#pragma once
================================================================*/

#ifndef __IMPB_SECURITY_H__
#define __IMPB_SECURITY_H__


#ifdef _WIN32
typedef char			int8_t;
typedef short			int16_t;
typedef int				int32_t;
typedef	long long		int64_t;
typedef unsigned char	uint8_t;
typedef unsigned short	uint16_t;
typedef unsigned int	uint32_t;
typedef	unsigned long long	uint64_t;
typedef int				socklen_t;
#else
#include <stdint.h>
#endif
typedef unsigned char	uchar_t;

#ifdef WIN32
#define DLL_MODIFIER __declspec(dllexport)
#else
#define DLL_MODIFIER
#endif


#ifdef __cplusplus
extern "C" {
#endif

//#include <iostream>
//using namespace std;
    
#ifdef __ANDROID__
#include <jni.h>
	     jbyteArray Java_com_dffx_im_Security_EncryptMsg(JNIEnv* env, jobject obj, jstring jstr);
	     jbyteArray Java_com_dffx_im_Security_DecryptMsg(JNIEnv* env, jobject obj, jstring jstr);
	     jbyteArray Java_com_dffx_im_Security_EncryptPass(JNIEnv* env, jobject obj, jstring jstr);
		 
		jbyteArray JNICALL Java_com_dffx_im_Security_IMBase64Eecode(JNIEnv* env, jobject obj,  jstring jstr);
		jbyteArray JNICALL Java_com_dffx_im_Security_IMBase64Decode(JNIEnv* env, jobject obj,  jstring jstr);
	 
#endif
    /**
     *  ����Ϣ����
     *
     *  @param pInData  �����ܵ���Ϣ����ָ��
     *  @param nInLen   ��������Ϣ���ݳ���
     *  @param pOutData ���ܺ���ı�
     *  @param nOutLen  ���ܺ���ı�����
     *
     *  @return ���� 0-�ɹ�; ����-ʧ��
     */
    DLL_MODIFIER int EncryptMsg(const char* pInData, uint32_t nInLen, char** pOutData, uint32_t& nOutLen);
    
    /**
     *  ����Ϣ����
     *
     *  @param pInData  �����ܵ���Ϣ����ָ��
     *  @param nInLen   ��������Ϣ���ݳ���
     *  @param pOutData ���ܺ���ı�
     *  @param nOutLen  ���ܺ���ı�����
     *
     *  @return ���� 0-�ɹ�; ����-ʧ��
     */
    DLL_MODIFIER int DecryptMsg(const char* pInData, uint32_t nInLen, char** pOutData, uint32_t& nOutLen);
    
    /**
     *  ��������м���
     *
     *  @param pInData  �����ܵ���Ϣ����ָ��
     *  @param nInLen   ��������Ϣ���ݳ���
     *  @param pOutData ���ܺ���ı�
     *  @param nOutLen  ���ܺ���ı�����
     *  @param pKey     32λ��Կ
     *
     *  @return ���� 0-�ɹ�; ����-ʧ��
     */
    DLL_MODIFIER int EncryptPass(const char* pInData, uint32_t nInLen, char** pOutData, uint32_t& nOutLen);
	
	DLL_MODIFIER string IMBase64Eecode(const string& pInData);
	DLL_MODIFIER string IMBase64Decode(const string& pInData);
	
	
    /**
     *  �ͷ���Դ
     *
     *  @param pOutData ��Ҫ�ͷŵ���Դ
     */
    DLL_MODIFIER void Free(char* pOutData);

    
#ifdef __cplusplus
}
#endif

#endif
