#include "IMMessage.h"
#include "IM.BaseDefine.pb.h"
#include <sstream>
#include "impb_security.h"

using namespace IM::BaseDefine;

CIMMessage::CIMMessage()
{
}

CIMMessage::~CIMMessage()
{
}

int CIMMessage::HandleSID_Message_Send(IMMessageCID cid, const Json::Value& jsInParam, unsigned char* OutParam, int& outLen)
{
	switch (cid)
	{
	case IM_Message_Data:
		return EncodeMsgData(jsInParam, OutParam, outLen);
	case IM_Message_DataAck:
	case IM_Message_Data_ReadAck:
	case IM_Message_Data_Notify:
		return EncodeMsgDataAck(jsInParam, OutParam, outLen);
	case IM_Message_ClientTimeReq:
		return EncodeClientTimeReq(jsInParam, OutParam, outLen);
	case IM_Message_ClientTimeRsp:
		return EncodeClientTimeRsp(jsInParam, OutParam, outLen);
	case IM_Message_UnreadMsgCntReq:
		return EncodeUnreadMsgCntReq(jsInParam, OutParam, outLen);
	case IM_Message_UnreadMsgCntRsp:
		return EncodeUnreadMsgCntRsp(jsInParam, OutParam, outLen);
	case IM_Message_GetMsgListReq:
		return EncodeGetMsgListReq(jsInParam, OutParam, outLen);
	case IM_Message_GetMsgListRsp:
		return EncodeGetMsgListRsp(jsInParam, OutParam, outLen);
	case IM_Message_CleanMsgListReq:
	case IM_Message_CleanMsgListRsp:
		return EncodeCleanMsgListRsp(jsInParam, OutParam, outLen);
	case IM_Message_OrderStatusRead:
	case IM_Message_OrderStatusReadBroadcast:
		return EncodeOrderStatusRead(jsInParam, OutParam, outLen);
	default:
		return IM_ERR_UNKOWNCMDID;
		break;
	}

}

int CIMMessage::HandleSID_Message_Receive(CImPdu* pPdu, string& OutParam)
{
	switch (pPdu->GetCommandId())
	{
	case DFFX_CID_MSG_DATA:
		return DecodeMsgData(pPdu, OutParam);
	case DFFX_CID_MSG_DATA_ACK:
	case DFFX_CID_MSG_READ_ACK:
	case DFFX_CID_MSG_READ_NOTIFY:
		return DecodeMsgDataAck(pPdu, OutParam);
	case DFFX_CID_MSG_TIME_REQUEST:
		return DecodeClientTimeReq(pPdu, OutParam);
	case DFFX_CID_MSG_TIME_RESPONSE:
		return DecodeClientTimeRsp(pPdu, OutParam);
	case DFFX_CID_MSG_UNREAD_CNT_REQUEST:
		return DecodeUnreadMsgCntReq(pPdu, OutParam);
	case DFFX_CID_MSG_UNREAD_CNT_RESPONSE:
		return DecodeUnreadMsgCntRsp(pPdu, OutParam);
	case DFFX_CID_MSG_LIST_REQUEST:
		return DecodeGetMsgListReq(pPdu, OutParam);
	case DFFX_CID_MSG_LIST_RESPONSE:
		return DecodeGetMsgListRsp(pPdu, OutParam);
	case DFFX_CID_MSG_CLEAN_MSGLIST_REQ:
	case DFFX_CID_MSG_CLEAN_MSGLIST_RES:
		return DecodeCleanMsgListRsp(pPdu, OutParam);
	case DFFX_CID_MSG_ORDERSTATUS_READ:
	case DFFX_CID_MSG_ORDERSTATUS_READ_BROADCAST:
		return DecodeOrderStatusRead(pPdu, OutParam);
	default:
		return IM_ERR_UNKOWNCMDID;
		break;
	}
}


int CIMMessage::EncodeMsgData(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	if (jsInParam["from_user_id"].isNull() || jsInParam["to_session_id"].isNull()
		|| jsInParam["msg_id"].isNull() || jsInParam["create_time"].isNull()
		|| jsInParam["msg_type"].isNull() || jsInParam["msg_data"].isNull()
		)
	{
		return IM_ERR_JSONPARAM;
	}

	IM::Message::IMMsgData msg;

	msg.set_from_user_id(jsInParam["from_user_id"].asInt());
	msg.set_to_session_id(jsInParam["to_session_id"].asInt());
	msg.set_msg_id(jsInParam["msg_id"].asInt());
	msg.set_create_time(jsInParam["create_time"].asInt());
	
	IM::BaseDefine::MsgType msg_type = IM::BaseDefine::MsgType(jsInParam["msg_type"].asInt());
	msg.set_msg_type(msg_type);

	string strMsgData = jsInParam["msg_data"].asString();
	char * pMsgData = NULL;
	uint32_t nMsgLen = 0;


	int retCode = EncryptMsg(strMsgData.c_str(), strMsgData.length(), &pMsgData, nMsgLen);
	if (retCode == 0 && nMsgLen > 0 && pMsgData != 0 && msg_type != IM::BaseDefine::MSG_TYPE_GROUP_AUDIO && msg_type != IM::BaseDefine::MSG_TYPE_SINGLE_AUDIO)
	{
		msg.set_msg_data(pMsgData, nMsgLen);
		Free( pMsgData);
		pMsgData = NULL;
	}
	else if (msg_type == IM::BaseDefine::MSG_TYPE_GROUP_AUDIO || msg_type == IM::BaseDefine::MSG_TYPE_SINGLE_AUDIO)
	{
		msg.set_msg_data(strMsgData);
	}
	else
	{
		msg.set_msg_data(strMsgData);
		return IM_ERR_ENCRPYTMSG;
	}

	if (!jsInParam["is_black"].isNull())
	{
		msg.set_is_black(jsInParam["is_black"].asInt());
	}

	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeMessage(&msg, DFFX_CID_MSG_DATA, OutParam, len, seqNo);

	return len;
}

int CIMMessage::DecodeMsgData(CImPdu* pPdu, string& OutParam)
{
	IM::Message::IMMsgData msg;;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;

	jsOutParam["sid"] = IM_MESSAGE;
	jsOutParam["cid"] = IM_Message_Data;

	jsOutParam["from_user_id"] = msg.from_user_id();
	jsOutParam["to_session_id"] = msg.to_session_id();
	jsOutParam["msg_id"] = msg.msg_id();
	jsOutParam["create_time"] = msg.create_time();
	jsOutParam["msg_type"] = msg.msg_type();

	if (msg.msg_type() != IM::BaseDefine::MSG_TYPE_GROUP_AUDIO && msg.msg_type() != IM::BaseDefine::MSG_TYPE_SINGLE_AUDIO)
	{
		string strMsg = "";
		//DecryptMsg
		char * pOutData = NULL;
		uint32_t nOutLen = 0;
		int retCode = DecryptMsg(msg.msg_data().c_str(), msg.msg_data().length(), &pOutData, nOutLen);
		if (retCode == 0 && nOutLen > 0 && pOutData != 0)
		{
			strMsg = std::string(pOutData, nOutLen);
			Free(pOutData);
			pOutData = NULL;
		}
		else
		{
			strMsg = std::string(msg.msg_data().c_str(), msg.msg_data().length());

		}

		jsOutParam["msg_data"] = strMsg;
	}
	else
	{
		string strMsg = IMBase64Eecode(msg.msg_data());	
		jsOutParam["msg_data"] = strMsg;
	}

	
	jsOutParam["is_black"] = msg.is_black();
	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMMessage::EncodeMsgDataAck(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	if (jsInParam["user_id"].isNull() || jsInParam["session_id"].isNull()
		|| jsInParam["msg_id"].isNull() || jsInParam["session_type"].isNull()
		)
	{
		return IM_ERR_JSONPARAM;
	}

	IM::Message::IMMsgDataAck msg;

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_session_id(jsInParam["session_id"].asInt());
	msg.set_msg_id(jsInParam["msg_id"].asInt());
	msg.set_session_type(IM::BaseDefine::SessionType(jsInParam["session_type"].asInt()));

	if (!jsInParam["is_black"].isNull())
	{
		msg.set_is_black(jsInParam["is_black"].asInt());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	if (jsInParam["cid"].asInt() == IM_Message_DataAck)
		len = EncodeMessage(&msg, DFFX_CID_MSG_DATA_ACK, OutParam, len, seqNo);
	else if (jsInParam["cid"].asInt() == IM_Message_Data_ReadAck)
		len = EncodeMessage(&msg, DFFX_CID_MSG_READ_ACK, OutParam, len, seqNo);
	else if (jsInParam["cid"].asInt() == IM_Message_Data_Notify)
		len = EncodeMessage(&msg, DFFX_CID_MSG_READ_NOTIFY, OutParam, len, seqNo);
	else
		return IM_ERR_UNKOWNCMDID;

	return len;
}

int CIMMessage::DecodeMsgDataAck(CImPdu* pPdu, string& OutParam)
{
	IM::Message::IMMsgDataAck msg;;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;

	jsOutParam["sid"] = IM_MESSAGE;
	if (pPdu->GetCommandId() == DFFX_CID_MSG_DATA_ACK)
	{
		jsOutParam["cid"] = IM_Message_DataAck;
	}
	else if (pPdu->GetCommandId() == DFFX_CID_MSG_READ_ACK)
	{
		jsOutParam["cid"] = IM_Message_Data_ReadAck;
	}
	else if (pPdu->GetCommandId() == DFFX_CID_MSG_READ_NOTIFY)
	{
		jsOutParam["cid"] = IM_Message_Data_Notify;
	}

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["session_id"] = msg.session_id();
	jsOutParam["msg_id"] = msg.msg_id();
	jsOutParam["session_type"] = msg.session_type();
	jsOutParam["is_black"] = msg.is_black();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMMessage::EncodeClientTimeReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Message::IMClientTimeReq msg;

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeMessage(&msg, DFFX_CID_MSG_TIME_REQUEST, OutParam, len, seqNo);

	return len;
}

int CIMMessage::DecodeClientTimeReq(CImPdu* pPdu, string& OutParam)
{
	IM::Message::IMClientTimeReq msg;;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	Json::Value jsOutParam;

	jsOutParam["sid"] = IM_MESSAGE;
	jsOutParam["cid"] = IM_Message_ClientTimeReq;

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMMessage::EncodeClientTimeRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	if (jsInParam["server_time"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	IM::Message::IMClientTimeRsp msg;

	msg.set_server_time(jsInParam["server_time"].asInt());

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeMessage(&msg, DFFX_CID_MSG_TIME_RESPONSE, OutParam, len, seqNo);

	return len;
}

int CIMMessage::DecodeClientTimeRsp(CImPdu* pPdu, string& OutParam)
{
	IM::Message::IMClientTimeRsp msg;;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	Json::Value jsOutParam;

	jsOutParam["sid"] = IM_MESSAGE;
	jsOutParam["cid"] = IM_Message_ClientTimeRsp;

	jsOutParam["server_time"] = msg.server_time();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMMessage::EncodeUnreadMsgCntReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	if (jsInParam["user_id"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	IM::Message::IMUnreadMsgCntReq msg;;

	msg.set_user_id(jsInParam["user_id"].asInt());

	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeMessage(&msg, DFFX_CID_MSG_UNREAD_CNT_REQUEST, OutParam, len, seqNo);

	return len;
}

int CIMMessage::DecodeUnreadMsgCntReq(CImPdu* pPdu, string& OutParam)
{
	IM::Message::IMUnreadMsgCntReq msg;;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	Json::Value jsOutParam;

	jsOutParam["sid"] = IM_MESSAGE;
	jsOutParam["cid"] = IM_Message_UnreadMsgCntReq;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMMessage::EncodeUnreadMsgCntRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	if (jsInParam["user_id"].isNull() || jsInParam["total_cnt"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	IM::Message::IMUnreadMsgCntRsp msg;;

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_total_cnt(jsInParam["total_cnt"].asInt());

	if (!jsInParam["unreadinfo_list"].isNull())
	{
		Json::Value jsArr = jsInParam["unreadinfo_list"];
		for (unsigned int i = 0; i < jsArr.size(); i++)
		{
			Json::Value jsInfo = jsArr[i];
			IM::BaseDefine::UnreadInfo*	pInfo = msg.add_unreadinfo_list();
			pInfo->set_session_id(jsInfo["session_id"].asInt());
			pInfo->set_session_type(IM::BaseDefine::SessionType(jsInfo["session_type"].asInt()));
			pInfo->set_unread_cnt(jsInfo["unread_cnt"].asInt());
			pInfo->set_latest_msg_id(jsInfo["latest_msg_id"].asInt());
			pInfo->set_latest_msg_data(jsInfo["latest_msg_data"].asString());
			pInfo->set_latest_msg_type(IM::BaseDefine::MsgType(jsInfo["latest_msg_type"].asInt()));
			pInfo->set_latest_msg_from_user_id(jsInfo["latest_msg_from_user_id"].asInt());
			pInfo->set_latest_msg_time(jsInfo["latest_msg_time"].asInt());
		}
	}


	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeMessage(&msg, DFFX_CID_MSG_UNREAD_CNT_RESPONSE, OutParam, len, seqNo);

	return len;
}

int CIMMessage::DecodeUnreadMsgCntRsp(CImPdu* pPdu, string& OutParam)
{
	IM::Message::IMUnreadMsgCntRsp msg;;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	Json::Value jsOutParam;
	Json::Value jsInfoArray;

	jsOutParam["sid"] = IM_MESSAGE;
	jsOutParam["cid"] = IM_Message_UnreadMsgCntRsp;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["total_cnt"] = msg.total_cnt();


	//	unreadinfo_list
	uint32_t nCnt = msg.unreadinfo_list_size();
	for (uint32_t i = 0; i < nCnt; ++i) {
		IM::BaseDefine::UnreadInfo unreadInfo = msg.unreadinfo_list(i);

		Json::Value jsUserInfo;
		jsUserInfo["session_id"] = unreadInfo.session_id();
		jsUserInfo["session_type"] = unreadInfo.session_type();
		jsUserInfo["unread_cnt"] = unreadInfo.unread_cnt();
		jsUserInfo["latest_msg_id"] = unreadInfo.latest_msg_id();

		//jsUserInfo["latest_msg_data"] = unreadInfo.latest_msg_data();
		//jsUserInfo["latest_msg_type"] = unreadInfo.latest_msg_type();
		IM::BaseDefine::MsgType msgType = unreadInfo.latest_msg_type();
		jsUserInfo["latest_msg_type"] = msgType;
		if (msgType == IM::BaseDefine::MSG_TYPE_GROUP_AUDIO || msgType == IM::BaseDefine::MSG_TYPE_SINGLE_AUDIO)
		{
			string strMsg = IMBase64Eecode(unreadInfo.latest_msg_data());
			jsOutParam["latest_msg_data"] = strMsg;
		}
		else
		{
			jsUserInfo["latest_msg_data"] = unreadInfo.latest_msg_data();
		}

		jsUserInfo["latest_msg_from_user_id"] = unreadInfo.latest_msg_from_user_id();
		jsUserInfo["latest_msg_time"] = unreadInfo.latest_msg_time();
		jsOutParam["attach_data"] = msg.attach_data();

		jsInfoArray[i] = jsUserInfo;

	}

	jsOutParam["unreadinfo_list"] = jsInfoArray;

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMMessage::EncodeGetMsgListReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	if (jsInParam["user_id"].isNull() || jsInParam["session_type"].isNull()
		|| jsInParam["session_id"].isNull() || jsInParam["msg_id_begin"].isNull()
		|| jsInParam["msg_cnt"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	IM::Message::IMGetMsgListReq msg;

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_session_type(IM::BaseDefine::SessionType(jsInParam["session_type"].asInt()));
	msg.set_session_id(jsInParam["session_id"].asInt());
	msg.set_msg_id_begin(jsInParam["msg_id_begin"].asInt());
	msg.set_msg_cnt(jsInParam["msg_cnt"].asInt());

	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeMessage(&msg, DFFX_CID_MSG_LIST_REQUEST, OutParam, len, seqNo);

	return len;
}

int CIMMessage::DecodeGetMsgListReq(CImPdu* pPdu, string& OutParam)
{
	IM::Message::IMGetMsgListReq msg;;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	Json::Value jsOutParam;

	jsOutParam["sid"] = IM_MESSAGE;
	jsOutParam["cid"] = IM_Message_GetMsgListReq;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["session_type"] = msg.session_type();
	jsOutParam["session_id"] = msg.session_id();
	jsOutParam["msg_id_begin"] = msg.msg_id_begin();
	jsOutParam["msg_cnt"] = msg.msg_cnt();

	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMMessage::EncodeGetMsgListRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	if (jsInParam["user_id"].isNull() || jsInParam["session_type"].isNull()
		|| jsInParam["session_id"].isNull() || jsInParam["msg_id_begin"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	IM::Message::IMGetMsgListRsp msg;;

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_session_type(IM::BaseDefine::SessionType(jsInParam["session_type"].asInt()));
	msg.set_session_id(jsInParam["session_id"].asInt());
	msg.set_msg_id_begin(jsInParam["msg_id_begin"].asInt());

	if (!jsInParam["msg_list"].isNull())
	{
		Json::Value jsArr = jsInParam["msg_list"];
		for (unsigned int i = 0; i < jsArr.size(); i++)
		{
			Json::Value jsInfo = jsArr[i];
			IM::BaseDefine::MsgInfo*	pInfo = msg.add_msg_list();
			pInfo->set_msg_id(jsInfo["msg_id"].asInt());
			pInfo->set_from_session_id(jsInfo["from_session_id"].asInt());
			pInfo->set_create_time(jsInfo["create_time"].asInt());
			pInfo->set_msg_type(IM::BaseDefine::MsgType(jsInfo["msg_type"].asInt()));
			pInfo->set_msg_data(jsInfo["msg_data"].asString());
		}
	}


	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeMessage(&msg, DFFX_CID_MSG_LIST_RESPONSE, OutParam, len, seqNo);

	return len;
}

int CIMMessage::DecodeGetMsgListRsp(CImPdu* pPdu, string& OutParam)
{
	IM::Message::IMGetMsgListRsp msg;;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	Json::Value jsOutParam;
	Json::Value jsMsgListArray;

	jsOutParam["sid"] = IM_MESSAGE;
	jsOutParam["cid"] = IM_Message_GetMsgListRsp;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["session_type"] = msg.session_type();
	jsOutParam["session_id"] = msg.session_id();
	jsOutParam["msg_id_begin"] = msg.msg_id_begin();

	uint32_t nCnt = msg.msg_list_size();
	for (uint32_t i = 0; i < nCnt; ++i) {
		IM::BaseDefine::MsgInfo msg_list = msg.msg_list(i);

		Json::Value jsMsgList;
		jsMsgList["msg_id"] = msg_list.msg_id();
		jsMsgList["from_session_id"] = msg_list.from_session_id();
		//jsMsgList["msg_type"] = msg_list.msg_type();
		//jsMsgList["msg_data"] = msg_list.msg_data();
		IM::BaseDefine::MsgType msgType = msg_list.msg_type();
		jsMsgList["msg_type"] = msgType;
		if (msgType == IM::BaseDefine::MSG_TYPE_GROUP_AUDIO || msgType == IM::BaseDefine::MSG_TYPE_SINGLE_AUDIO)
		{
			string strMsg = IMBase64Eecode(msg_list.msg_data());
			jsOutParam["msg_data"] = strMsg;
		}
		else
		{
			jsMsgList["msg_data"] = msg_list.msg_data();
		}


		jsMsgList["create_time"] = msg_list.create_time();

		jsMsgListArray[i] = jsMsgList;
	}

	jsOutParam["msg_list"] = jsMsgListArray;
	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}


int CIMMessage::EncodeCleanMsgListRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	if (jsInParam["user_id"].isNull() || jsInParam["session_type"].isNull()
		|| jsInParam["session_id"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	IM::Message::IMCleanMsgListRsp msg;

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_session_type(IM::BaseDefine::SessionType(jsInParam["session_type"].asInt()));
	msg.set_session_id(jsInParam["session_id"].asInt());

	if (!jsInParam["result_code"].isNull())
	{
		msg.set_result_code(jsInParam["result_code"].asInt());
	}

	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	if (jsInParam["cid"].asInt() == IM_Message_CleanMsgListReq)
		len = EncodeMessage(&msg, DFFX_CID_MSG_CLEAN_MSGLIST_REQ, OutParam, len, seqNo);
	else if (jsInParam["cid"].asInt() == IM_Message_CleanMsgListRsp)
		len = EncodeMessage(&msg, DFFX_CID_MSG_CLEAN_MSGLIST_RES, OutParam, len, seqNo);
	else
		return IM_ERR_UNKOWNCMDID;

	return len;
}

int CIMMessage::DecodeCleanMsgListRsp(CImPdu* pPdu, string& OutParam)
{
	IM::Message::IMCleanMsgListRsp msg;;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	Json::Value jsOutParam;

	jsOutParam["sid"] = IM_MESSAGE;

	if (pPdu->GetCommandId() == DFFX_CID_MSG_CLEAN_MSGLIST_REQ)
	{
		jsOutParam["cid"] = IM_Message_CleanMsgListReq;
	}
	else if (pPdu->GetCommandId() == DFFX_CID_MSG_CLEAN_MSGLIST_RES)
	{
		jsOutParam["cid"] = IM_Message_CleanMsgListRsp;
	}

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["session_type"] = msg.session_type();
	jsOutParam["session_id"] = msg.session_id();
	jsOutParam["result_code"] = msg.result_code();
	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMMessage::EncodeOrderStatusRead(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Message::IMOrderStatusRead msg;;

	if (jsInParam["user_id"].isNull() || jsInParam["order_id"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_order_id(jsInParam["order_id"].asInt());
	msg.set_orderlist_is_null(jsInParam["orderlist_is_null"].asInt());

	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	if (jsInParam["cid"].asInt() == IM_Message_OrderStatusRead)
		len = EncodeMessage(&msg, DFFX_CID_MSG_ORDERSTATUS_READ, OutParam, len, seqNo);
	else if (jsInParam["cid"].asInt() == IM_Message_OrderStatusReadBroadcast)
		len = EncodeMessage(&msg, DFFX_CID_MSG_ORDERSTATUS_READ_BROADCAST, OutParam, len, seqNo);
	else
		return IM_ERR_UNKOWNCMDID;

	return len;
}

int CIMMessage::DecodeOrderStatusRead(CImPdu* pPdu, string& OutParam)
{
	IM::Message::IMOrderStatusRead msg;;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	Json::Value jsOutParam;

	jsOutParam["sid"] = IM_MESSAGE;

	if (pPdu->GetCommandId() == DFFX_CID_MSG_ORDERSTATUS_READ)
	{
		jsOutParam["cid"] = IM_Message_OrderStatusRead;
	}
	else if (pPdu->GetCommandId() == DFFX_CID_MSG_ORDERSTATUS_READ_BROADCAST)
	{
		jsOutParam["cid"] = IM_Message_OrderStatusReadBroadcast;
	}

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["order_id"] = msg.order_id();
	jsOutParam["orderlist_is_null"] = msg.orderlist_is_null();
	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);


	return IM_ERR_SUCCESS;
}

int CIMMessage::EncodeMessage(google::protobuf::MessageLite* msg, uint16_t command_id, unsigned char* OutParam, int& len, int seqNo)
{

	CImPdu pdu;
	pdu.SetPBMsg(msg);
	pdu.SetServiceId(DFFX_SID_MSG);
	pdu.SetCommandId(command_id);
	//todo... 调用序列号生成器生成
	pdu.SetSeqNum(seqNo);

	//输出参数不够长则返回错误
	if (len < pdu.GetLength())
		return IM_ERR_OUTPARAM_LEN;

	memcpy(OutParam, pdu.GetBuffer(), pdu.GetLength());

	len = pdu.GetLength();

	return len;


}