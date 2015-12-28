#include "IMBuddy.h"
#include "IM.BaseDefine.pb.h"
#include "impb_security.h"

using namespace IM::BaseDefine;

CIMBuddy::CIMBuddy()
{
}

CIMBuddy::~CIMBuddy()
{
}

int CIMBuddy::HandleSID_Buddy_Send(IMMessageCID cid, const Json::Value& jsInParam, unsigned char* OutParam, int& outLen)
{
	switch (cid)
	{
	case IM_Buddy_RecentContactSessionReq:
		return EncodeRecentContactSessionReq(jsInParam, OutParam, outLen);
	case IM_Buddy_RecentContactSessionRsp:
		return EncodeRecentContactSessionRsp(jsInParam, OutParam, outLen);
	case IM_Buddy_UserStatNotify:
		return EncodeUserStatNotify(jsInParam, OutParam, outLen);
	case IM_Buddy_UsersInfoReq:
	case IM_Buddy_UsersStatReq:
		return EncodeUsersInfoReq(jsInParam, OutParam, outLen);
	case IM_Buddy_UsersStatRsp:
		return EncodeUsersStatRsp(jsInParam, OutParam, outLen);
	case IM_Buddy_RemoveSessionReq:
	case IM_Buddy_RemoveSessionRsp:
		return EncodeRemoveSessionRsp(jsInParam, OutParam, outLen);
	case IM_Buddy_PCLoginStatusNotify:
		return EncodePCLoginStatusNotify(jsInParam, OutParam, outLen);
	case IM_Buddy_RemoveSessionNotify:
		return EncodeRemoveSessionNotify(jsInParam, OutParam, outLen);
	case IM_Buddy_UsersInfoRsp:
	case IM_Buddy_AllUserReq:
	case IM_Buddy_AllUserRsp:
	case IM_Buddy_FindUserInfoRsp:
		return EncodeAllUserRsp(jsInParam, OutParam, outLen);
	case IM_Buddy_DepartmentReq:
	case IM_Buddy_DepartmentRsp:
		return EncodeDepartmentRsp(jsInParam, OutParam, outLen);
	case IM_Buddy_AddFriendReq:
		return EncodeAddFriendReq(jsInParam, OutParam, outLen);
	case IM_Buddy_AddFriendRsp:
	case IM_Buddy_ReverseAddFriendRsp:
	case IM_Buddy_DelFriendRsp:
	case IM_Buddy_DelFriendNotify:
	case IM_Buddy_ChgFiendRemarkRsp:
		return EncodeCommonOperFriendRes(jsInParam, OutParam, outLen);
	case IM_Buddy_ReverseAddFriendReq:
		return EncodeIMReverseAddFriendReq(jsInParam, OutParam, outLen);
	case IM_Buddy_DelFriendReq:
	case IM_Buddy_DelFiendGroupReq:
	case IM_Buddy_DelFiendGroupRsp:
	case IM_Buddy_CreateFiendGroupRsp:
	case IM_Buddy_MoveFiendGroupRsp:
	case IM_Buddy_ChgFiendGroupNameRsp:
		return EncodeCommonOperFriendGroupRes(jsInParam, OutParam, outLen);
	case IM_Buddy_ChgFiendRemarkReq:
	case IM_Buddy_ChgFiendGroupNameReq:
		return EncodeChgFriendRemarkReq(jsInParam, OutParam, outLen);
	case IM_Buddy_CreateFiendGroupReq:
		return EncodeCreateFriendGroupReq(jsInParam, OutParam, outLen);
	case IM_Buddy_MoveFiendGroupReq:
		return EncodeMoveFriendToGroupReq(jsInParam, OutParam, outLen);
	case IM_Buddy_FiendNotifyReq:
		return EncodeFriendNotifyReq(jsInParam, OutParam, outLen);
	case IM_Buddy_FiendNotifyRsp:
		return EncodeFriendNotifyRes(jsInParam, OutParam, outLen);
	case IM_Buddy_GetAddFriendReq:
		return EncodeGetAddFriendReq(jsInParam, OutParam, outLen);
	case IM_Buddy_GetAddFriendRsp:
		return EncodeGetAddFriendRes(jsInParam, OutParam, outLen);
	case IM_Buddy_FindUserInfoReq:
		return EncodeFindUserInfoReq(jsInParam, OutParam, outLen);
	default:
		return IM_ERR_UNKOWNCMDID;
		break;
	}

}

int CIMBuddy::HandleSID_Buddy_Receive(CImPdu* pPdu, string& OutParam)
{
	switch (pPdu->GetCommandId())
	{
	case DFFX_CID_BUDDY_LIST_RECENT_CONTACT_SESSION_REQUEST:
		return DecodeRecentContactSessionReq(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_RECENT_CONTACT_SESSION_RESPONSE:
		return DecodeRecentContactSessionRsp(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_STATUS_NOTIFY:
		return DecodeUserStatNotify(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_USER_INFO_REQUEST:
	case DFFX_CID_BUDDY_LIST_USERS_STATUS_REQUEST:
		return DecodeUsersInfoReq(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_USERS_STATUS_RESPONSE:
		return DecodeUsersStatRsp(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_REMOVE_SESSION_REQ:
	case DFFX_CID_BUDDY_LIST_REMOVE_SESSION_RES:
		return DecodeRemoveSessionRsp(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_PC_LOGIN_STATUS_NOTIFY:
		return DecodePCLoginStatusNotify(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_REMOVE_SESSION_NOTIFY:
		return DecodeRemoveSessionNotify(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_USER_INFO_RESPONSE:
	case DFFX_CID_BUDDY_LIST_ALL_USER_REQUEST:
	case DFFX_CID_BUDDY_LIST_ALL_USER_RESPONSE:
	case DFFX_CID_BUDDY_LIST_FINDUSERINFO_RES:
		return DecodeAllUserRsp(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_DEPARTMENT_REQUEST:
	case DFFX_CID_BUDDY_LIST_DEPARTMENT_RESPONSE:
		return DecodeDepartmentRsp(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_ADDFRIEND_REQ:
		return DecodeAddFriendReq(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_ADDFRIEND_RES:
	case DFFX_CID_BUDDY_LIST_REVERSEADDFRIEND_RES:
	case DFFX_CID_BUDDY_LIST_DELFRIEND_RES:
	case DFFX_CID_BUDDY_LIST_CHGFRIENDREMARK_RES:
	case DFFX_CID_BUDDY_LIST_DELFRIEND_NOTIFY:
		return DecodeCommonOperFriendRes(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_REVERSEADDFRIEND_REQ:
		return DecodeIMReverseAddFriendReq(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_DELFRIEND_REQ:
	case DFFX_CID_BUDDY_LIST_DELFRIENDGROUP_REQ:
	case DFFX_CID_BUDDY_LIST_DELFRIENDGROUP_RES:
	case DFFX_CID_BUDDY_LIST_CREATEFRIENDGROUP_RES:
	case DFFX_CID_BUDDY_LIST_MOVEFRIENDTOGROUP_RES:
	case DFFX_CID_BUDDY_LIST_CHGFRIENDGROUPNAME_RES:
		return DecodeCommonOperFriendGroupRes(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_CHGFRIENDREMARK_REQ:
	case DFFX_CID_BUDDY_LIST_CHGFRIENDGROUPNAME_REQ:
		return DecodeChgFriendRemarkReq(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_CREATEFRIENDGROUP_REQ:
		return DecodeCreateFriendGroupReq(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_MOVEFRIENDTOGROUP_REQ:
		return DecodeMoveFriendToGroupReq(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_FRIENDNOTIFY_REQ:
		return DecodeFriendNotifyReq(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_FRIENDNOTIFY_RES:
		return DecodeFriendNotifyRes(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_GETADDFRIEND_REQ:
		return DecodeGetAddFriendReq(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_GETADDFRIEND_RES:
		return DecodeGetAddFriendRes(pPdu, OutParam);
	case DFFX_CID_BUDDY_LIST_FINDUSERINFO_REQ:
		return DecodeFindUserInfoReq(pPdu, OutParam);
	default:
		return IM_ERR_UNKOWNCMDID;
		break;
	}
}


int CIMBuddy::EncodeBuddy(google::protobuf::MessageLite* msg, uint16_t command_id, unsigned char* OutParam, int& len, int seqNo)
{

	CImPdu pdu;
	pdu.SetPBMsg(msg);
	pdu.SetServiceId(DFFX_SID_BUDDY_LIST);
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


int  CIMBuddy::EncodeRecentContactSessionReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMRecentContactSessionReq msg;

	if (jsInParam["user_id"].isNull() || jsInParam["latest_update_time"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_latest_update_time(jsInParam["latest_update_time"].asInt());

	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_RECENT_CONTACT_SESSION_REQUEST, OutParam, len, seqNo);

	return len;
}


int CIMBuddy::DecodeRecentContactSessionReq(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMRecentContactSessionReq msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	Json::Value jsOutParam;

	jsOutParam["sid"] = IM_BUDDY_LIST;
	jsOutParam["cid"] = IM_Buddy_RecentContactSessionReq;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["latest_update_time"] = msg.latest_update_time();

	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodeRecentContactSessionRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMRecentContactSessionRsp msg;

	if (jsInParam["user_id"].isNull() || jsInParam["contact_session_list"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());


	Json::Value readerIPArray = jsInParam["contact_session_list"];
	for (unsigned int i = 0; i < readerIPArray.size(); i++)
	{
		IM::BaseDefine::ContactSessionInfo* pContactSessionInfo = msg.add_contact_session_list();
		pContactSessionInfo->set_session_id(readerIPArray[i]["session_id"].asInt());
		pContactSessionInfo->set_session_type(IM::BaseDefine::SessionType(readerIPArray[i]["session_type"].asInt()));
		pContactSessionInfo->set_session_status(IM::BaseDefine::SessionStatusType(readerIPArray[i]["session_status"].asInt()));
		pContactSessionInfo->set_updated_time(readerIPArray[i]["updated_time"].asInt());
		pContactSessionInfo->set_latest_msg_id(readerIPArray[i]["latest_msg_id"].asInt());
		pContactSessionInfo->set_latest_msg_data(readerIPArray[i]["latest_msg_data"].asString());
		pContactSessionInfo->set_latest_msg_type(IM::BaseDefine::MsgType(readerIPArray[i]["latest_msg_type"].asInt()));
		pContactSessionInfo->set_latest_msg_from_user_id(readerIPArray[i]["latest_msg_from_user_id"].asInt());
	}

	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_RECENT_CONTACT_SESSION_RESPONSE, OutParam, len, seqNo);

	return len;
}

int  CIMBuddy::DecodeRecentContactSessionRsp(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMRecentContactSessionRsp msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsContactSessionInfoArray;

	jsOutParam["sid"] = IM_BUDDY_LIST;
	jsOutParam["cid"] = IM_Buddy_RecentContactSessionRsp;

	jsOutParam["user_id"] = msg.user_id();

	uint32_t nCnt = msg.contact_session_list_size();
	for (uint32_t i = 0; i < nCnt; ++i) {
		IM::BaseDefine::ContactSessionInfo ContactSessionInfo = msg.contact_session_list(i);

		Json::Value jsContactSessionInfo;
		jsContactSessionInfo["session_id"] = ContactSessionInfo.session_id();
		jsContactSessionInfo["session_type"] = ContactSessionInfo.session_type();
		jsContactSessionInfo["session_status"] = ContactSessionInfo.session_status();
		jsContactSessionInfo["updated_time"] = ContactSessionInfo.updated_time();
		jsContactSessionInfo["latest_msg_id"] = ContactSessionInfo.latest_msg_id();
	
		IM::BaseDefine::MsgType msgType = ContactSessionInfo.latest_msg_type();
		jsContactSessionInfo["latest_msg_type"] = msgType;

		if (msgType == IM::BaseDefine::MSG_TYPE_GROUP_AUDIO || msgType == IM::BaseDefine::MSG_TYPE_SINGLE_AUDIO)
		{
			string strMsg = IMBase64Eecode(ContactSessionInfo.latest_msg_data());
			jsOutParam["latest_msg_data"] = strMsg;
		}
		else
		{
			jsContactSessionInfo["latest_msg_data"] = ContactSessionInfo.latest_msg_data();
		}

		jsContactSessionInfo["latest_msg_from_user_id"] = ContactSessionInfo.latest_msg_from_user_id();

		jsContactSessionInfoArray[i] = jsContactSessionInfo;

	}

	jsOutParam["contact_session_list"] = jsContactSessionInfoArray;

	jsOutParam["attach_data"] = msg.attach_data();


	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodeUserStatNotify(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMUserStatNotify msg;

	if (jsInParam["user_stat"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	Json::Value jUserInfo = jsInParam["user_stat"];
	IM::BaseDefine::UserStat *userStat = msg.mutable_user_stat();

	userStat->set_user_id(jUserInfo["user_id"].asInt());
	userStat->set_status(IM::BaseDefine::UserStatType(jUserInfo["status"].asInt()));
	userStat->set_client_type(IM::BaseDefine::ClientType(jUserInfo["client_type"].asInt()));

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_STATUS_NOTIFY, OutParam, len, seqNo);

	return len;
}

int CIMBuddy::DecodeUserStatNotify(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMUserStatNotify msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsUserStat;

	jsOutParam["sid"] = IM_BUDDY_LIST;
	jsOutParam["cid"] = IM_Buddy_UserStatNotify;

	IM::BaseDefine::UserStat userstat = msg.user_stat();
	jsUserStat["user_id"] = userstat.user_id();
	jsUserStat["status"] = userstat.status();
	jsUserStat["client_type"] = userstat.client_type();

	jsOutParam["user_stat"] = jsUserStat;

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodeUsersInfoReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMUsersInfoReq msg;

	if (jsInParam["user_id"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());

	if (!jsInParam["user_id_list"].isNull())
	{
		Json::Value readerUserIdArray = jsInParam["user_id_list"];
		for (unsigned int i = 0; i < readerUserIdArray.size(); i++)
		{
			msg.add_user_id_list(readerUserIdArray[i].asInt());
		}
	}

	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	if (jsInParam["cid"].asInt() == IM_Buddy_UsersInfoReq)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_USER_INFO_REQUEST, OutParam, len, seqNo);
	else if (jsInParam["cid"].asInt() == IM_Buddy_UsersStatReq)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_USERS_STATUS_REQUEST, OutParam, len, seqNo);

	return len;
}

int CIMBuddy::DecodeUsersInfoReq(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMUsersInfoReq msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsUserIdArray;

	jsOutParam["sid"] = IM_BUDDY_LIST;
	if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_USER_INFO_REQUEST)
	{
		jsOutParam["cid"] = IM_Buddy_UsersInfoReq;
	}
	else if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_USERS_STATUS_REQUEST)
	{
		jsOutParam["cid"] = IM_Buddy_UsersStatReq;
	}

	jsOutParam["user_id"] = msg.user_id();
	//jsOutParam["user_id_list"] = msg.user_id_list();
	uint32_t nCnt = msg.user_id_list_size();
	for (uint32_t i = 0; i < nCnt; ++i)
	{
		jsUserIdArray[i] = msg.user_id_list(i);
	}
	jsOutParam["user_id_list"] = jsUserIdArray;

	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodeAllUserRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMAllUserRsp msg;

	if (jsInParam["user_id"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());

	if (!jsInParam["latest_update_time"].isNull())
	{
		msg.set_latest_update_time(jsInParam["latest_update_time"].asInt());
	}

	if (!jsInParam["user_list"].isNull())
	{
		Json::Value readerUserInfoArray = jsInParam["user_list"];
		for (unsigned int i = 0; i < readerUserInfoArray.size(); i++)
		{
			IM::BaseDefine::UserInfo* pUserInfoAddr = msg.add_user_list();

			pUserInfoAddr->set_user_id(readerUserInfoArray[i]["user_id"].asInt());
			pUserInfoAddr->set_user_nickname(readerUserInfoArray[i]["user_nickname"].asString());
			pUserInfoAddr->set_user_gender(readerUserInfoArray[i]["user_gender"].asInt());
			pUserInfoAddr->set_user_birthday(readerUserInfoArray[i]["user_birthday"].asString());
			pUserInfoAddr->set_user_headlink(readerUserInfoArray[i]["user_headlink"].asString());
			pUserInfoAddr->set_user_level(readerUserInfoArray[i]["user_level"].asInt());
			pUserInfoAddr->set_user_status(readerUserInfoArray[i]["user_status"].asInt());
			pUserInfoAddr->set_user_uid(readerUserInfoArray[i]["user_uid"].asInt());
			pUserInfoAddr->set_user_phone(readerUserInfoArray[i]["user_phone"].asString());
			pUserInfoAddr->set_friend_groupid(readerUserInfoArray[i]["friend_groupid"].asInt());
			pUserInfoAddr->set_friend_remark(readerUserInfoArray[i]["friend_remark"].asString());
			pUserInfoAddr->set_friend_status(readerUserInfoArray[i]["friend_status"].asInt());
			pUserInfoAddr->set_user_type(readerUserInfoArray[i]["user_type"].asInt());
			pUserInfoAddr->set_user_ischeck(readerUserInfoArray[i]["user_ischeck"].asInt());
			pUserInfoAddr->set_user_desc(readerUserInfoArray[i]["user_desc"].asString());

		}
	}

	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	if (jsInParam["cid"] == IM_Buddy_AllUserReq)
	{
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_ALL_USER_REQUEST, OutParam, len, seqNo); //??????????
	}
	else if (jsInParam["cid"] == IM_Buddy_AllUserRsp)
	{
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_ALL_USER_RESPONSE, OutParam, len, seqNo); //??????????
	}
	else if (jsInParam["cid"] == IM_Buddy_FindUserInfoRsp)
	{
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_FINDUSERINFO_RES, OutParam, len, seqNo); //??????????
	}
	else if (jsInParam["cid"] == IM_Buddy_UsersInfoRsp)
	{
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_USER_INFO_RESPONSE, OutParam, len, seqNo); //??????????
	}

	return len;

}

int CIMBuddy::DecodeAllUserRsp(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMAllUserRsp msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsUserInfoArray;

	jsOutParam["sid"] = IM_BUDDY_LIST;

	if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_ALL_USER_RESPONSE)
	{
		jsOutParam["cid"] = IM_Buddy_AllUserRsp;
	}
	else if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_ALL_USER_REQUEST)
	{
		jsOutParam["cid"] = IM_Buddy_AllUserReq;
	}
	else if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_FINDUSERINFO_RES)
	{
		jsOutParam["cid"] = IM_Buddy_FindUserInfoRsp;
	}
	else if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_USER_INFO_RESPONSE)
	{
		jsOutParam["cid"] = IM_Buddy_UsersInfoRsp;
	}


	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["latest_update_time"] = msg.latest_update_time();
	jsOutParam["attach_data"] = msg.attach_data();

	//	unreadinfo_list
	uint32_t nCnt = msg.user_list_size();
	for (uint32_t i = 0; i < nCnt; ++i) {
		IM::BaseDefine::UserInfo userInfo = msg.user_list(i);

		Json::Value jsUserInfo;
		jsUserInfo["user_id"] = userInfo.user_id();
		jsUserInfo["user_nickname"] = userInfo.user_nickname();
		jsUserInfo["user_gender"] = userInfo.user_gender();
		jsUserInfo["user_birthday"] = userInfo.user_birthday();
		jsUserInfo["user_headlink"] = userInfo.user_headlink();
		jsUserInfo["user_level"] = userInfo.user_level();
		jsUserInfo["user_status"] = userInfo.user_status();
		jsUserInfo["user_uid"] = userInfo.user_uid();
		jsUserInfo["user_phone"] = userInfo.user_phone();
		jsUserInfo["friend_groupid"] = userInfo.friend_groupid();
		jsUserInfo["friend_remark"] = userInfo.friend_remark();
		jsUserInfo["friend_status"] = userInfo.friend_status();
		jsUserInfo["user_type"] = userInfo.user_type();
		jsUserInfo["user_ischeck"] = userInfo.user_ischeck();
		jsUserInfo["user_desc"] = userInfo.user_desc();

		jsUserInfoArray[i] = jsUserInfo;

	}
	jsOutParam["user_list"] = jsUserInfoArray;

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodeUsersStatRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMUsersStatRsp msg;

	if (jsInParam["user_id"].isNull() || jsInParam["user_stat_list"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());


	if (!jsInParam["user_stat_list"].isNull())
	{
		Json::Value readerUserStatArray = jsInParam["user_stat_list"];
		for (unsigned int i = 0; i < readerUserStatArray.size(); i++)
		{
			IM::BaseDefine::UserStat* pUserStatAddr = msg.add_user_stat_list();

			pUserStatAddr->set_user_id(readerUserStatArray[i]["user_id"].asInt());
			pUserStatAddr->set_status(IM::BaseDefine::UserStatType(readerUserStatArray[i]["status"].asInt()));
			pUserStatAddr->set_client_type(IM::BaseDefine::ClientType(readerUserStatArray[i]["client_type"].asInt()));

		}
	}

	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	if (jsInParam["cid"] == IM_Buddy_UsersStatRsp)
	{
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_USERS_STATUS_RESPONSE, OutParam, len, seqNo); //??????????
	}

	return len;
}

int CIMBuddy::DecodeUsersStatRsp(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMUsersStatRsp msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsUserStatArray;

	jsOutParam["sid"] = IM_BUDDY_LIST;

	if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_USERS_STATUS_RESPONSE)
	{
		jsOutParam["cid"] = IM_Buddy_UsersStatRsp;
	}

	jsOutParam["user_id"] = msg.user_id();

	//	user_stat_list
	uint32_t nCnt = msg.user_stat_list_size();
	for (uint32_t i = 0; i < nCnt; ++i) {
		IM::BaseDefine::UserStat userStat = msg.user_stat_list(i);

		Json::Value jsUserStat;
		jsUserStat["user_id"] = userStat.user_id();
		jsUserStat["status"] = userStat.status();
		jsUserStat["client_type"] = userStat.client_type();

		jsUserStatArray[i] = jsUserStat;

	}
	jsOutParam["user_stat_list"] = jsUserStatArray;

	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodeRemoveSessionRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMRemoveSessionRsp msg;

	if (jsInParam["user_id"].isNull()
		|| jsInParam["session_type"].isNull() || jsInParam["session_id"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	if (!jsInParam["result_code"].isNull())
		msg.set_result_code(jsInParam["result_code"].asInt());
	msg.set_session_type(IM::BaseDefine::SessionType(jsInParam["session_type"].asInt()));
	msg.set_session_id(jsInParam["session_id"].asInt());

	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	if (jsInParam["cid"].asInt() == IM_Buddy_RemoveSessionReq)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_REMOVE_SESSION_REQ, OutParam, len, seqNo);
	else if (jsInParam["cid"].asInt() == IM_Buddy_RemoveSessionRsp)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_REMOVE_SESSION_RES, OutParam, len, seqNo);

	return len;
}

int CIMBuddy::DecodeRemoveSessionRsp(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMRemoveSessionRsp msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;

	jsOutParam["sid"] = IM_BUDDY_LIST;

	if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_REMOVE_SESSION_RES)
		jsOutParam["cid"] = IM_Buddy_RemoveSessionRsp;
	if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_REMOVE_SESSION_REQ)
		jsOutParam["cid"] = IM_Buddy_RemoveSessionReq;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["result_code"] = msg.result_code();
	jsOutParam["session_type"] = msg.session_type();
	jsOutParam["session_id"] = msg.session_id();
	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodePCLoginStatusNotify(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMPCLoginStatusNotify msg;

	if (jsInParam["user_id"].isNull() || jsInParam["login_stat"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_login_stat(IM::BaseDefine::UserStatType(jsInParam["login_stat"].asInt()));

	int seqNo = jsInParam["seqNo"].asInt();
	if (jsInParam["cid"].asInt() == IM_Buddy_PCLoginStatusNotify)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_PC_LOGIN_STATUS_NOTIFY, OutParam, len, seqNo);

	return len;
}

int CIMBuddy::DecodePCLoginStatusNotify(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMPCLoginStatusNotify msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;

	jsOutParam["sid"] = IM_BUDDY_LIST;
	jsOutParam["cid"] = IM_Buddy_PCLoginStatusNotify;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["login_stat"] = msg.login_stat();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodeRemoveSessionNotify(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMRemoveSessionNotify msg;

	if (jsInParam["user_id"].isNull() || jsInParam["session_type"].isNull()
		|| jsInParam["session_id"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_session_type(IM::BaseDefine::SessionType(jsInParam["session_type"].asInt()));
	msg.set_session_id(jsInParam["session_id"].asInt());

	int seqNo = jsInParam["seqNo"].asInt();
	if (jsInParam["cid"].asInt() == IM_Buddy_RemoveSessionNotify)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_REMOVE_SESSION_NOTIFY, OutParam, len, seqNo);

	return len;
}

int CIMBuddy::DecodeRemoveSessionNotify(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMRemoveSessionNotify msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;

	jsOutParam["sid"] = IM_BUDDY_LIST;
	jsOutParam["cid"] = IM_Buddy_RemoveSessionNotify;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["session_type"] = msg.session_type();
	jsOutParam["session_id"] = msg.session_id();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodeDepartmentRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMDepartmentRsp msg;

	if (jsInParam["user_id"].isNull() || jsInParam["latest_update_time"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_latest_update_time(jsInParam["latest_update_time"].asInt());

	if (!jsInParam["dept_list"].isNull())
	{
		Json::Value deptListArray = jsInParam["dept_list"];
		for (unsigned int i = 0; i < deptListArray.size(); i++)
		{
			IM::BaseDefine::DepartInfo* pDeptList = msg.add_dept_list();

			pDeptList->set_group_id(deptListArray[i]["group_id"].asInt());
			pDeptList->set_group_flag(deptListArray[i]["group_flag"].asInt());
			pDeptList->set_group_name(deptListArray[i]["group_name"].asString());
			pDeptList->set_group_sort(deptListArray[i]["group_sort"].asInt());
		}
	}
	

	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	if (jsInParam["cid"].asInt() == IM_Buddy_DepartmentReq)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_DEPARTMENT_REQUEST, OutParam, len, seqNo);
	else if (jsInParam["cid"].asInt() == IM_Buddy_DepartmentRsp)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_DEPARTMENT_RESPONSE, OutParam, len, seqNo);

	return len;
}

int CIMBuddy::DecodeDepartmentRsp(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMDepartmentRsp msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsDeptListArray;

	jsOutParam["sid"] = IM_BUDDY_LIST;

	if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_DEPARTMENT_REQUEST)
		jsOutParam["cid"] = IM_Buddy_DepartmentReq;
	else if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_DEPARTMENT_RESPONSE)
		jsOutParam["cid"] = IM_Buddy_DepartmentRsp;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["latest_update_time"] = msg.latest_update_time();


	uint32_t nCnt = msg.dept_list_size();
	for (uint32_t i = 0; i < nCnt; ++i) {
		IM::BaseDefine::DepartInfo departInfo = msg.dept_list(i);

		Json::Value jsDepartInfo;
		jsDepartInfo["group_id"] = departInfo.group_id();
		jsDepartInfo["group_flag"] = departInfo.group_flag();
		jsDepartInfo["group_name"] = departInfo.group_name();
		jsDepartInfo["group_sort"] = departInfo.group_sort();

		jsDeptListArray[i] = jsDepartInfo;

	}
	jsOutParam["dept_list"] = jsDeptListArray;

	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodeAddFriendReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMAddFriendReq msg;

	if (jsInParam["from_user_id"].isNull() || jsInParam["to_user_id"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_from_user_id(jsInParam["from_user_id"].asInt());
	msg.set_to_user_id(jsInParam["to_user_id"].asInt());
	msg.set_friend_groupid(jsInParam["friend_groupid"].asInt());
	msg.set_friend_remark(jsInParam["friend_remark"].asString());
	msg.set_extra_info(jsInParam["extra_info"].asString());
	msg.set_user_nickname(jsInParam["user_nickname"].asString());
	msg.set_user_headlink(jsInParam["user_headlink"].asString());
	msg.set_user_gender(jsInParam["user_gender"].asInt());
	msg.set_user_uid(jsInParam["user_uid"].asInt());

	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	if (jsInParam["cid"].asInt() == IM_Buddy_AddFriendReq)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_ADDFRIEND_REQ, OutParam, len, seqNo);

	return len;
}

int CIMBuddy::DecodeAddFriendReq(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMAddFriendReq msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsDeptListArray;

	jsOutParam["sid"] = IM_BUDDY_LIST;
	jsOutParam["cid"] = IM_Buddy_AddFriendReq;

	jsOutParam["from_user_id"] = msg.from_user_id();
	jsOutParam["to_user_id"] = msg.to_user_id();
	jsOutParam["friend_groupid"] = msg.friend_groupid();
	jsOutParam["friend_remark"] = msg.friend_remark();
	jsOutParam["extra_info"] = msg.extra_info();
	jsOutParam["user_nickname"] = msg.user_nickname();
	jsOutParam["user_headlink"] = msg.user_headlink();
	jsOutParam["user_gender"] = msg.user_gender();
	jsOutParam["user_uid"] = msg.user_uid();
	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodeCommonOperFriendRes(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMCommonOperFriendRes msg;

	if (jsInParam["user_id"].isNull() || jsInParam["result_code"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_result_code(jsInParam["result_code"].asInt());
	msg.set_friend_id(jsInParam["friend_id"].asInt());
	msg.set_friendres_status_type(IM::BaseDefine::FriendResStatusType(jsInParam["friendres_status_type"].asInt()));

	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	if (jsInParam["cid"].asInt() == IM_Buddy_AddFriendRsp)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_ADDFRIEND_RES, OutParam, len, seqNo);
	else if (jsInParam["cid"].asInt() == IM_Buddy_ReverseAddFriendRsp)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_REVERSEADDFRIEND_RES, OutParam, len, seqNo);
	else if (jsInParam["cid"].asInt() == IM_Buddy_DelFriendRsp)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_DELFRIEND_RES, OutParam, len, seqNo);
	else if (jsInParam["cid"].asInt() == IM_Buddy_ChgFiendRemarkRsp)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_CHGFRIENDREMARK_RES, OutParam, len, seqNo);
	else if (jsInParam["cid"].asInt() == IM_Buddy_DelFriendNotify)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_DELFRIEND_NOTIFY, OutParam, len, seqNo);

	return len;
}

int CIMBuddy::DecodeCommonOperFriendRes(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMCommonOperFriendRes msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsDeptListArray;

	jsOutParam["sid"] = IM_BUDDY_LIST;
	if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_ADDFRIEND_RES)
		jsOutParam["cid"] = IM_Buddy_AddFriendRsp;
	else if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_REVERSEADDFRIEND_RES)
		jsOutParam["cid"] = IM_Buddy_ReverseAddFriendRsp;
	else if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_DELFRIEND_RES)
		jsOutParam["cid"] = IM_Buddy_DelFriendRsp;
	else if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_CHGFRIENDREMARK_RES)
		jsOutParam["cid"] = IM_Buddy_ChgFiendRemarkRsp;
	else if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_DELFRIEND_NOTIFY)
		jsOutParam["cid"] = IM_Buddy_DelFriendNotify;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["result_code"] = msg.result_code();
	jsOutParam["friend_id"] = msg.friend_id();
	jsOutParam["friendres_status_type"] = msg.friendres_status_type();
	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodeIMReverseAddFriendReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMReverseAddFriendReq msg;

	if (jsInParam["from_user_id"].isNull() || jsInParam["to_user_id"].isNull()
		|| jsInParam["friendres_status_type"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_from_user_id(jsInParam["from_user_id"].asInt());
	msg.set_to_user_id(jsInParam["to_user_id"].asInt());
	msg.set_friendres_status_type(IM::BaseDefine::FriendResStatusType(jsInParam["friendres_status_type"].asInt()));
	msg.set_friend_groupid(jsInParam["friend_groupid"].asInt());
	msg.set_friend_remark(jsInParam["friend_remark"].asString());
	msg.set_refuse_reason(jsInParam["refuse_reason"].asString());

	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_REVERSEADDFRIEND_REQ, OutParam, len, seqNo);

	return len;
}


int CIMBuddy::DecodeIMReverseAddFriendReq(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMReverseAddFriendReq msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsDeptListArray;

	jsOutParam["sid"] = IM_BUDDY_LIST;
	if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_REVERSEADDFRIEND_REQ)
		jsOutParam["cid"] = IM_Buddy_ReverseAddFriendReq;

	jsOutParam["from_user_id"] = msg.from_user_id();
	jsOutParam["to_user_id"] = msg.to_user_id();
	jsOutParam["friendres_status_type"] = msg.friendres_status_type();
	jsOutParam["friend_groupid"] = msg.friend_groupid();
	jsOutParam["friend_remark"] = msg.friend_remark();
	jsOutParam["refuse_reason"] = msg.refuse_reason();
	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodeCommonOperFriendGroupRes(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMCommonOperFriendGroupRes msg;

	if (jsInParam["user_id"].isNull() || jsInParam["result_code"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_result_code(jsInParam["result_code"].asInt());


	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	if (jsInParam["cid"].asInt() == IM_Buddy_DelFriendReq)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_DELFRIEND_REQ, OutParam, len, seqNo);
	else if (jsInParam["cid"].asInt() == IM_Buddy_DelFiendGroupRsp)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_DELFRIENDGROUP_RES, OutParam, len, seqNo);
	else if (jsInParam["cid"].asInt() == IM_Buddy_DelFiendGroupReq)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_DELFRIENDGROUP_REQ, OutParam, len, seqNo);
	else if (jsInParam["cid"].asInt() == IM_Buddy_CreateFiendGroupRsp)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_CREATEFRIENDGROUP_RES, OutParam, len, seqNo);
	else if (jsInParam["cid"].asInt() == IM_Buddy_MoveFiendGroupRsp)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_MOVEFRIENDTOGROUP_RES, OutParam, len, seqNo);
	else if (jsInParam["cid"].asInt() == IM_Buddy_ChgFiendGroupNameRsp)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_CHGFRIENDGROUPNAME_RES, OutParam, len, seqNo);

	return len;
}

int CIMBuddy::DecodeCommonOperFriendGroupRes(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMCommonOperFriendRes msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsDeptListArray;

	jsOutParam["sid"] = IM_BUDDY_LIST;
	if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_CREATEFRIENDGROUP_RES)
		jsOutParam["cid"] = IM_Buddy_CreateFiendGroupRsp;
	else if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_DELFRIENDGROUP_REQ)
		jsOutParam["cid"] = IM_Buddy_DelFiendGroupReq;
	else if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_DELFRIENDGROUP_RES)
		jsOutParam["cid"] = IM_Buddy_DelFiendGroupRsp;
	else if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_MOVEFRIENDTOGROUP_RES)
		jsOutParam["cid"] = IM_Buddy_MoveFiendGroupRsp;
	else if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_CHGFRIENDGROUPNAME_RES)
		jsOutParam["cid"] = IM_Buddy_ChgFiendGroupNameRsp;
	else if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_DELFRIEND_REQ)
		jsOutParam["cid"] = IM_Buddy_DelFriendReq;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["result_code"] = msg.result_code();
	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodeChgFriendRemarkReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMChgFriendRemarkReq msg;

	if (jsInParam["user_id"].isNull() || jsInParam["friend_id"].isNull()
		|| jsInParam["friend_nick"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_friend_id(jsInParam["friend_id"].asInt());
	msg.set_friend_nick(jsInParam["friend_nick"].asString());

	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	if (jsInParam["cid"].asInt() == IM_Buddy_ChgFiendRemarkReq)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_CHGFRIENDREMARK_REQ, OutParam, len, seqNo);
	else if (jsInParam["cid"].asInt() == IM_Buddy_ChgFiendGroupNameReq)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_CHGFRIENDGROUPNAME_REQ, OutParam, len, seqNo);

	return len;
}

int CIMBuddy::DecodeChgFriendRemarkReq(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMChgFriendRemarkReq msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsDeptListArray;

	jsOutParam["sid"] = IM_BUDDY_LIST;
	if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_CHGFRIENDREMARK_REQ)
		jsOutParam["cid"] = IM_Buddy_ChgFiendRemarkReq;
	else if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_CHGFRIENDGROUPNAME_REQ)
		jsOutParam["cid"] = IM_Buddy_ChgFiendGroupNameReq;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["friend_id"] = msg.friend_id();
	jsOutParam["friend_nick"] = msg.friend_nick();
	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodeCreateFriendGroupReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMCreateFriendGroupReq msg;

	if (jsInParam["user_id"].isNull() || jsInParam["group_name"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_group_name(jsInParam["group_name"].asString());

	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	if (jsInParam["cid"].asInt() == IM_Buddy_CreateFiendGroupReq)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_CREATEFRIENDGROUP_REQ, OutParam, len, seqNo);

	return len;
}

int CIMBuddy::DecodeCreateFriendGroupReq(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMCreateFriendGroupReq msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsDeptListArray;

	jsOutParam["sid"] = IM_BUDDY_LIST;
	if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_CREATEFRIENDGROUP_REQ)
		jsOutParam["cid"] = IM_Buddy_CreateFiendGroupReq;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["group_name"] = msg.group_name();
	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodeMoveFriendToGroupReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMMoveFriendToGroupReq msg;

	if (jsInParam["user_id"].isNull() || jsInParam["group_id"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_group_id(jsInParam["group_id"].asInt());

	if (!jsInParam["friend_id_list"].isNull())
	{
		Json::Value readerFriendListPArray = jsInParam["friend_id_list"];
		for (unsigned int i = 0; i < readerFriendListPArray.size(); i++)
		{
			msg.add_friend_id_list(readerFriendListPArray[i].asInt());
		}
	}

	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_MOVEFRIENDTOGROUP_REQ, OutParam, len, seqNo);

	return len;
}

int CIMBuddy::DecodeMoveFriendToGroupReq(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMMoveFriendToGroupReq msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsFriendIdArray;

	jsOutParam["sid"] = IM_BUDDY_LIST;
	if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_MOVEFRIENDTOGROUP_REQ)
		jsOutParam["cid"] = IM_Buddy_MoveFiendGroupReq;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["group_id"] = msg.group_id();
	//jsOutParam["friend_id_list"] = msg.friend_id_list();
	uint32_t nCnt = msg.friend_id_list_size();
	for (uint32_t i = 0; i < nCnt; ++i)
	{
		jsFriendIdArray[i] = msg.friend_id_list(i);
	}
	jsOutParam["friend_id_list"] = jsFriendIdArray;

	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodeFriendNotifyReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMFriendNotifyReq msg;

	if (jsInParam["from_user_id"].isNull() || jsInParam["to_user_id"].isNull()
		|| jsInParam["friendres_status_type"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_from_user_id(jsInParam["from_user_id"].asInt());
	msg.set_to_user_id(jsInParam["to_user_id"].asInt());
	msg.set_friendres_status_type(IM::BaseDefine::FriendResStatusType(jsInParam["friendres_status_type"].asInt()));

	msg.set_user_nickname(jsInParam["user_nickname"].asString());
	msg.set_user_headlink(jsInParam["user_headlink"].asString());
	msg.set_user_gender(jsInParam["user_gender"].asInt());
	msg.set_user_uid(jsInParam["user_uid"].asInt());
	msg.set_refuse_reason(jsInParam["refuse_reason"].asString());

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_FRIENDNOTIFY_REQ, OutParam, len, seqNo);

	return len;
}

int CIMBuddy::DecodeFriendNotifyReq(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMFriendNotifyReq msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsFriendIdArray;

	jsOutParam["sid"] = IM_BUDDY_LIST;
	jsOutParam["cid"] = IM_Buddy_FiendNotifyReq;

	jsOutParam["from_user_id"] = msg.from_user_id();
	jsOutParam["to_user_id"] = msg.to_user_id();
	jsOutParam["friendres_status_type"] = msg.friendres_status_type();
	jsOutParam["user_nickname"] = msg.user_nickname();
	jsOutParam["user_headlink"] = msg.user_headlink();
	jsOutParam["user_gender"] = msg.user_gender();
	jsOutParam["user_uid"] = msg.user_uid();
	jsOutParam["refuse_reason"] = msg.refuse_reason();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodeFriendNotifyRes(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMFriendNotifyRes msg;

	if (jsInParam["from_user_id"].isNull() || jsInParam["to_user_id"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_from_user_id(jsInParam["from_user_id"].asInt());
	msg.set_to_user_id(jsInParam["to_user_id"].asInt());

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_FRIENDNOTIFY_RES, OutParam, len, seqNo);

	return len;
}

int CIMBuddy::DecodeFriendNotifyRes(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMFriendNotifyRes msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsDeptListArray;

	jsOutParam["sid"] = IM_BUDDY_LIST;
	if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_FRIENDNOTIFY_RES)
		jsOutParam["cid"] = IM_Buddy_FiendNotifyRsp;

	jsOutParam["from_user_id"] = msg.from_user_id();
	jsOutParam["to_user_id"] = msg.to_user_id();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodeGetAddFriendReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMGetAddFriendReq msg;

	if (jsInParam["user_id"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());

	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	if (jsInParam["cid"].asInt() == IM_Buddy_GetAddFriendReq)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_GETADDFRIEND_REQ, OutParam, len, seqNo);

	return len;
}

int CIMBuddy::DecodeGetAddFriendReq(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMGetAddFriendReq msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsDeptListArray;

	jsOutParam["sid"] = IM_BUDDY_LIST;
	if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_GETADDFRIEND_REQ)
		jsOutParam["cid"] = IM_Buddy_GetAddFriendReq;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodeGetAddFriendRes(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMGetAddFriendRes msg;

	if (jsInParam["user_id"].isNull() || jsInParam["addfriend_info_list"].isNull()
		|| jsInParam["agree_info_list"].isNull() || jsInParam["refuse_info_list"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_attach_data(jsInParam["attach_data"].asString());

	Json::Value addFriendInfoArray = jsInParam["addfriend_info_list"];
	for (unsigned int i = 0; i < addFriendInfoArray.size(); i++)
	{
		IM::Buddy::IMCommonOperFrienInfo* pCommonOperFrienInfo = msg.add_addfriend_info_list();

		pCommonOperFrienInfo->set_oper_user_id(addFriendInfoArray[i]["oper_user_id"].asInt());
		pCommonOperFrienInfo->set_oper_time(addFriendInfoArray[i]["oper_time"].asInt());
		pCommonOperFrienInfo->set_extra_info(addFriendInfoArray[i]["extra_info"].asString());
		pCommonOperFrienInfo->set_user_nickname(addFriendInfoArray[i]["user_nickname"].asString());
		pCommonOperFrienInfo->set_user_headlink(addFriendInfoArray[i]["user_headlink"].asString());
		pCommonOperFrienInfo->set_user_gender(addFriendInfoArray[i]["user_gender"].asInt());
		pCommonOperFrienInfo->set_user_uid(addFriendInfoArray[i]["user_uid"].asInt());
	}

	Json::Value agreeInfoArray = jsInParam["agree_info_list"];
	for (unsigned int i = 0; i < agreeInfoArray.size(); i++)
	{
		IM::Buddy::IMCommonOperFrienInfo* pCommonOperFrienInfo = msg.add_agree_info_list();

		pCommonOperFrienInfo->set_oper_user_id(agreeInfoArray[i]["oper_user_id"].asInt());
		pCommonOperFrienInfo->set_oper_time(agreeInfoArray[i]["oper_time"].asInt());
		pCommonOperFrienInfo->set_extra_info(agreeInfoArray[i]["extra_info"].asString());
		pCommonOperFrienInfo->set_user_nickname(agreeInfoArray[i]["user_nickname"].asString());
		pCommonOperFrienInfo->set_user_headlink(agreeInfoArray[i]["user_headlink"].asString());
		pCommonOperFrienInfo->set_user_gender(agreeInfoArray[i]["user_gender"].asInt());
		pCommonOperFrienInfo->set_user_uid(agreeInfoArray[i]["user_uid"].asInt());
	}
	
	Json::Value refuseInfoArray = jsInParam["refuse_info_list"];
	for (unsigned int i = 0; i < refuseInfoArray.size(); i++)
	{
		IM::Buddy::IMCommonOperFrienInfo* pCommonOperFrienInfo = msg.add_refuse_info_list();

		pCommonOperFrienInfo->set_oper_user_id(refuseInfoArray[i]["oper_user_id"].asInt());
		pCommonOperFrienInfo->set_oper_time(refuseInfoArray[i]["oper_time"].asInt());
		pCommonOperFrienInfo->set_extra_info(refuseInfoArray[i]["extra_info"].asString());
		pCommonOperFrienInfo->set_user_nickname(refuseInfoArray[i]["user_nickname"].asString());
		pCommonOperFrienInfo->set_user_headlink(refuseInfoArray[i]["user_headlink"].asString());
		pCommonOperFrienInfo->set_user_gender(refuseInfoArray[i]["user_gender"].asInt());
		pCommonOperFrienInfo->set_user_uid(refuseInfoArray[i]["user_uid"].asInt());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	if (jsInParam["cid"].asInt() == IM_Buddy_GetAddFriendRsp)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_GETADDFRIEND_RES, OutParam, len, seqNo);
	
	return len;
}

int CIMBuddy::DecodeGetAddFriendRes(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMGetAddFriendRes msg;

	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsAddFriendInfoArray;
	Json::Value jsAgreeFriendInfoArray;
	Json::Value jsRefuseFriendInfoArray;

	jsOutParam["sid"] = IM_BUDDY_LIST;
	if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_GETADDFRIEND_RES)
		jsOutParam["cid"] = IM_Buddy_GetAddFriendRsp;

	jsOutParam["user_id"] = msg.user_id();

	uint32_t nCnt = msg.addfriend_info_list_size();
	for (uint32_t i = 0; i < nCnt; ++i)
	{
		IM::Buddy::IMCommonOperFrienInfo CommonOperFrienInfo = msg.addfriend_info_list(i);

		Json::Value jsCommonOperFrienInfo;
		jsCommonOperFrienInfo["oper_user_id"] = CommonOperFrienInfo.oper_user_id();
		jsCommonOperFrienInfo["oper_time"] = CommonOperFrienInfo.oper_time();
		jsCommonOperFrienInfo["extra_info"] = CommonOperFrienInfo.extra_info();
		jsCommonOperFrienInfo["user_nickname"] = CommonOperFrienInfo.user_nickname();
		jsCommonOperFrienInfo["user_headlink"] = CommonOperFrienInfo.user_headlink();
		jsCommonOperFrienInfo["user_gender"] = CommonOperFrienInfo.user_gender();
		jsCommonOperFrienInfo["user_uid"] = CommonOperFrienInfo.user_uid();

		jsAddFriendInfoArray[i] = jsCommonOperFrienInfo;
	}
	jsOutParam["addfriend_info_list"] = jsAddFriendInfoArray;

	nCnt = msg.agree_info_list_size();
	for (uint32_t i = 0; i < nCnt; ++i)
	{
		IM::Buddy::IMCommonOperFrienInfo CommonOperFrienInfo = msg.agree_info_list(i);

		Json::Value jsCommonOperFrienInfo;
		jsCommonOperFrienInfo["oper_user_id"] = CommonOperFrienInfo.oper_user_id();
		jsCommonOperFrienInfo["oper_time"] = CommonOperFrienInfo.oper_time();
		jsCommonOperFrienInfo["extra_info"] = CommonOperFrienInfo.extra_info();
		jsCommonOperFrienInfo["user_nickname"] = CommonOperFrienInfo.user_nickname();
		jsCommonOperFrienInfo["user_headlink"] = CommonOperFrienInfo.user_headlink();
		jsCommonOperFrienInfo["user_gender"] = CommonOperFrienInfo.user_gender();
		jsCommonOperFrienInfo["user_uid"] = CommonOperFrienInfo.user_uid();

		jsAgreeFriendInfoArray[i] = jsCommonOperFrienInfo;
	}
	jsOutParam["agree_info_list"] = jsAgreeFriendInfoArray;

	nCnt = msg.refuse_info_list_size();
	for (uint32_t i = 0; i < nCnt; ++i)
	{
		IM::Buddy::IMCommonOperFrienInfo CommonOperFrienInfo = msg.refuse_info_list(i);

		Json::Value jsCommonOperFrienInfo;
		jsCommonOperFrienInfo["oper_user_id"] = CommonOperFrienInfo.oper_user_id();
		jsCommonOperFrienInfo["oper_time"] = CommonOperFrienInfo.oper_time();
		jsCommonOperFrienInfo["extra_info"] = CommonOperFrienInfo.extra_info();
		jsCommonOperFrienInfo["user_nickname"] = CommonOperFrienInfo.user_nickname();
		jsCommonOperFrienInfo["user_headlink"] = CommonOperFrienInfo.user_headlink();
		jsCommonOperFrienInfo["user_gender"] = CommonOperFrienInfo.user_gender();
		jsCommonOperFrienInfo["user_uid"] = CommonOperFrienInfo.user_uid();

		jsRefuseFriendInfoArray[i] = jsCommonOperFrienInfo;
	}
	jsOutParam["refuse_info_list"] = jsRefuseFriendInfoArray;

	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMBuddy::EncodeFindUserInfoReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Buddy::IMFindUserInfoReq msg;

	if (jsInParam["user_id"].isNull() || jsInParam["find_string"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_find_string(jsInParam["find_string"].asString());

	if (!jsInParam["attach_data"].isNull())
	{
		msg.set_attach_data(jsInParam["attach_data"].asString());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	if (jsInParam["cid"].asInt() == IM_Buddy_FindUserInfoReq)
		len = EncodeBuddy(&msg, DFFX_CID_BUDDY_LIST_FINDUSERINFO_REQ, OutParam, len, seqNo);

	return len;
}

int CIMBuddy::DecodeFindUserInfoReq(CImPdu* pPdu, string& OutParam)
{
	IM::Buddy::IMFindUserInfoReq msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsDeptListArray;

	jsOutParam["sid"] = IM_BUDDY_LIST;
	if (pPdu->GetCommandId() == DFFX_CID_BUDDY_LIST_FINDUSERINFO_REQ)
		jsOutParam["cid"] = IM_Buddy_FindUserInfoReq;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["find_string"] = msg.find_string();
	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}
