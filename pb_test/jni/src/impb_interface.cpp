#include <stdio.h>
#include <stdlib.h>

#include "IMLogin.h"
#include "IMFile.h"
#include "IMMessage.h"
#include "IMBuddy.h"
#include "IMOther.h"
#include "IMSwitchService.h"
#include "IMGroup.h"

#include "impb_interface.h"
#include "json/json.h"
#include "IM.BaseDefine.pb.h"
using namespace IM::BaseDefine;

#ifdef __ANDROID__


JNIEXPORT jboolean JNICALL Java_com_dffx_im_impb_impb_Init(JNIEnv *env, jobject obj)
{
	return true;
}

JNIEXPORT void JNICALL Java_com_dffx_im_impb_impb_Destroy(JNIEnv *env, jobject obj)
{

}

JNIEXPORT jint JNICALL Java_com_dffx_im_impb_impb_IMReq(JNIEnv* env, jobject, IMMessageSID sid,  IMMessageCID cid, jstring inParam, jbyteArray OutParam)
{
	int nRet = IM_ERR_SUCCESS;


	LOGI("Java_com_dffx_im_impb_impb_IMReq begin");

	const char* szinParam = (char*)env->GetStringUTFChars(inParam, 0);
	LOGI(szinParam);

	unsigned char* szOutParam = (unsigned char*)env->GetByteArrayElements(OutParam,0);
	int nArrLen = env->GetArrayLength(OutParam);

	//todo

	memset(szOutParam, 0, nArrLen);

	Json::Reader jsReader(Json::Features::strictMode());
	Json::Value jsInParam;
	if ( !jsReader.parse(szinParam, jsInParam))
	{
		nRet = IM_ERR_JSONPARSE;
		goto lEnd;
	}

	switch (sid)
	{
	case IM_LOGIN:
		LOGI("Java_com_dffx_im_impb_impb_IMReq IM_LOGIN");
		nRet = CIMLogin::HandleSID_Login_Send(static_cast<IMMessageCID>(cid), jsInParam, szOutParam, nArrLen);
		break;
	case IM_File:
		LOGI("Java_com_dffx_im_impb_impb_IMReq IM_File");
		nRet = CIMFile::HandleSID_File_Send(static_cast<IMMessageCID>(cid), jsInParam, szOutParam, nArrLen);
		break;
	case IM_MESSAGE:
		LOGI("Java_com_dffx_im_impb_impb_IMReq IM_MESSAGE");
		nRet = CIMMessage::HandleSID_Message_Send(static_cast<IMMessageCID>(cid), jsInParam, szOutParam, nArrLen);
		break;
	case IM_BUDDY_LIST:
		LOGI("Java_com_dffx_im_impb_impb_IMReq IM_BUDDY_LIST");
		nRet = CIMBuddy::HandleSID_Buddy_Send(static_cast<IMMessageCID>(cid), jsInParam, szOutParam, nArrLen);
		break;
	case IM_Other:
		LOGI("Java_com_dffx_im_impb_impb_IMReq IM_Other");
		nRet = CIMOther::HandleSID_Other_Send(static_cast<IMMessageCID>(cid), jsInParam, szOutParam, nArrLen);
		break;
	case IM_SwtichService:
		LOGI("Java_com_dffx_im_impb_impb_IMReq IM_SwtichService");
		nRet = CIMSwitchService::HandleSID_SwitchService_Send(static_cast<IMMessageCID>(cid), jsInParam, szOutParam, nArrLen);
		break;
	case IM_Group:
		LOGI("Java_com_dffx_im_impb_impb_IMReq IM_Group");
		nRet = CIMGroup::HandleSID_Group_Send(static_cast<IMMessageCID>(cid), jsInParam, szOutParam, nArrLen);
		break;
	default:
		nRet = IM_ERR_UNKOWNSERVID;
		break;
	}

lEnd:
	env->ReleaseStringUTFChars(inParam, szinParam );
	env->ReleaseByteArrayElements(OutParam, (jbyte*)szOutParam,0 );
	return nRet;
}

JNIEXPORT jstring JNICALL Java_com_dffx_im_impb_impb_IMRsp(JNIEnv *env, jobject,  jbyteArray inParam, jbyteArray seqNo)
{	
	jstring strRet = NULL;
	int nRet = IM_ERR_SUCCESS;

	LOGI("Java_com_dffx_im_impb_impb_IMRsp begin");

	unsigned char* szinParam = (unsigned char*)env->GetByteArrayElements(inParam,0);
	int nArrLen = env->GetArrayLength(inParam);

	unsigned char* szSeqNo = (unsigned char*)env->GetByteArrayElements(seqNo,0);
	int nSeqLen = env->GetArrayLength(seqNo);

	string strSeqNo;
	LOGI("inParam = %s", szinParam);
	//todo
	CImPdu* pPdu = NULL;
	try
	{
		if (pPdu = CImPdu::ReadPdu(szinParam, nArrLen))
		{
			uint32_t pdu_len = pPdu->GetLength();
			uint32_t t_seqNo = pPdu->GetSeqNum();

			string strOutParam;

			switch (pPdu->GetServiceId())
			{
			case DFFX_SID_LOGIN:
				LOGI("Java_com_dffx_im_impb_impb_IMRsp IM_LOGIN");
				//strSeqNo = CIMLogin::getSeqNoString(t_seqNo);
				nRet = CIMLogin::HandleSID_Login_Receive(pPdu, strOutParam);
				break;
			case DFFX_SID_FILE:
				LOGI("Java_com_dffx_im_impb_impb_IMRsp IM_LOGIN");
				//strSeqNo = CIMFile::getSeqNoString(t_seqNo);
				nRet = CIMFile::HandleSID_File_Receive(pPdu, strOutParam);
				break;
			case DFFX_SID_MSG:
				LOGI("Java_com_dffx_im_impb_impb_IMRsp IM_MESSAGE");
				//strSeqNo = CIMMessage::getSeqNoString(t_seqNo);
				nRet = CIMMessage::HandleSID_Message_Receive(pPdu, strOutParam);
				break;
			case DFFX_SID_BUDDY_LIST:
				LOGI("Java_com_dffx_im_impb_impb_IMRsp DFFX_SID_BUDDY_LIST");
				//strSeqNo = CIMBuddy::getSeqNoString(t_seqNo);
				nRet = CIMBuddy::HandleSID_Buddy_Receive(pPdu, strOutParam);
				break;
			case DFFX_SID_OTHER:
				LOGI("Java_com_dffx_im_impb_impb_IMRsp DFFX_SID_Other");
				//strSeqNo = CIMOther::getSeqNoString(t_seqNo);
				nRet = CIMOther::HandleSID_Other_Receive(pPdu, strOutParam);
				break;
			case DFFX_SID_SWITCH_SERVICE:
				LOGI("Java_com_dffx_im_impb_impb_IMRsp DFFX_SID_SwitchService");
				//strSeqNo = CIMSwitchService::getSeqNoString(t_seqNo);
				nRet = CIMSwitchService::HandleSID_SwitchService_Receive(pPdu, strOutParam);
				break;
			case DFFX_SID_GROUP:
				LOGI("Java_com_dffx_im_impb_impb_IMRsp DFFX_SID_GROUP");
	//			strSeqNo = CIMGroup::getSeqNoString(t_seqNo);
				nRet = CIMGroup::HandleSID_Group_Receive(pPdu, strOutParam);
				break;
			default:
				LOGI("Java_com_dffx_im_impb_impb_IMRsp default");
				nRet = IM_ERR_UNKOWNSERVID;
				break;
			}

			if (nRet==IM_ERR_SUCCESS)
			{
		//		memcpy(szSeqNo, strSeqNo.c_str(), strSeqNo.length());
				char strS[10];
				sprintf(strS, "%d", t_seqNo);
				memcpy(szSeqNo, strS, strlen(strS));

				int len = strOutParam.length();
				jbyte* str = (jbyte* )strOutParam.c_str();
				jclass   clsstring   =   (env)->FindClass( "java/lang/String");
				jstring   strencode   =   (env)->NewStringUTF("UTF-8");
				jmethodID   mid   =   (env)->GetMethodID(clsstring, "<init>","([BLjava/lang/String;)V");
				jbyteArray   barr   =   (env)-> NewByteArray(len);
				(env)-> SetByteArrayRegion(barr ,0, len, str);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     

				strRet = (jstring)(env)-> NewObject(clsstring, mid, barr, strencode);
			}

			delete pPdu;
			pPdu = NULL;
		}
		else
		{
			LOGI("Java_com_dffx_im_impb_impb_IMRsp IM_ERR_NOTENOUGH");
			nRet = IM_ERR_NOTENOUGH;
		}
	}
	catch (CPduException& ex) {

		if (pPdu) {
			delete pPdu;
			pPdu = NULL;
		}
		nRet = IM_ERR_EXCEPTION;
	}

lEnd:
	env->ReleaseByteArrayElements(inParam, (jbyte*)szinParam, 0);
	//env->ReleaseStringUTFChars(OutParam, szOutParam);
	return strRet;
}


#else

DLL_MODIFIER bool Init()
{
	return false;
}

DLL_MODIFIER void Destroy()
{

}

DLL_MODIFIER int IMReq(IMMessageSID sid, IMMessageCID cid, const string& inParam, unsigned char* szOutParam, int& nOutLen)
{
	int nRet = IM_ERR_SUCCESS;

	//todo ... 入参校验

	Json::Reader jsReader(Json::Features::strictMode());
	Json::Value jsInParam;
	if (!jsReader.parse(inParam, jsInParam))
	{
		nRet = IM_ERR_JSONPARSE;
		goto lEnd;
	}

	try
	{
		switch (sid)
		{
		case IM_LOGIN:
			nRet = CIMLogin::HandleSID_Login_Send(cid, jsInParam, szOutParam, nOutLen);
			break;
		case IM_File:
			nRet = CIMFile::HandleSID_File_Send(cid, jsInParam, szOutParam, nOutLen);
			break;
		case IM_MESSAGE:
			nRet = CIMMessage::HandleSID_Message_Send(cid, jsInParam, szOutParam, nOutLen);
			break;
		case IM_BUDDY_LIST:
			nRet = CIMBuddy::HandleSID_Buddy_Send(cid, jsInParam, szOutParam, nOutLen);
			break;
		case IM_Other:
			nRet = CIMOther::HandleSID_Other_Send(cid, jsInParam, szOutParam, nOutLen);
			break;
		case IM_SwtichService:
			nRet = CIMSwitchService::HandleSID_SwitchService_Send(cid, jsInParam, szOutParam, nOutLen);
			break;
		case IM_Group:
			nRet = CIMGroup::HandleSID_Group_Send(cid, jsInParam, szOutParam, nOutLen);
			break;
		default:
			nRet = IM_ERR_UNKOWNSERVID;
			break;
		}
	}
	catch (...)
	{
		nRet = IM_ERR_EXCEPTION;
	}

lEnd:
	return nRet;
}

DLL_MODIFIER int IMRsp(const unsigned char* inParam, int& nInLen, string& OutParam, int& seqNo)
{
	int nRet = IM_ERR_SUCCESS;

	//todo ... 入参校验

	CImPdu* pPdu = NULL;
	try
	{
		if (pPdu = CImPdu::ReadPdu((uchar_t*)inParam, nInLen))
		{
			uint32_t pdu_len = pPdu->GetLength();
			seqNo = pPdu->GetSeqNum();

			switch (pPdu->GetServiceId())
			{
			case DFFX_SID_LOGIN:
				nRet = CIMLogin::HandleSID_Login_Receive(pPdu, OutParam);
				break;
			case DFFX_SID_FILE:
				nRet = CIMFile::HandleSID_File_Receive(pPdu, OutParam);
                break;
			case DFFX_SID_MSG:
				nRet = CIMMessage::HandleSID_Message_Receive(pPdu, OutParam);
				break;
			case DFFX_SID_BUDDY_LIST:
				nRet = CIMBuddy::HandleSID_Buddy_Receive(pPdu, OutParam);
				break;
			case DFFX_SID_OTHER:
				nRet = CIMOther::HandleSID_Other_Receive(pPdu, OutParam);
				break;
			case DFFX_SID_SWITCH_SERVICE:
				nRet = CIMSwitchService::HandleSID_SwitchService_Receive(pPdu, OutParam);
				break;
			case DFFX_SID_GROUP:
				nRet = CIMGroup::HandleSID_Group_Receive(pPdu, OutParam);
				break;
			default:
				nRet = IM_ERR_UNKOWNSERVID;
				break;
			}
			if (nRet == IM_ERR_SUCCESS)
			{
				nInLen = pdu_len;
			}

			delete pPdu;
			pPdu = NULL;
		}
		else
		{
			nRet = IM_ERR_NOTENOUGH;
		}
	}
	catch (...) {

		if (pPdu) {
			delete pPdu;
			pPdu = NULL;
		}
		nRet = IM_ERR_EXCEPTION;
	}

lEnd:
	return nRet;
}

#endif
