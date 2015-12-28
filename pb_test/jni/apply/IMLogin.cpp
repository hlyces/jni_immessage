#include "IMLogin.h"
#include "IM.BaseDefine.pb.h"

using namespace IM::BaseDefine;

CIMLogin::CIMLogin()
{
}

CIMLogin::~CIMLogin()
{
}

int CIMLogin::HandleSID_Login_Send(IMMessageCID cid, const Json::Value& jsInParam, unsigned char* OutParam, int& outLen)
{
	switch (cid)
	{
	case IM_Login_Req:
		return EncodeLoginReq(jsInParam, OutParam, outLen);
	case IM_Login_Rsp:
		return EncodeLoginRsp(jsInParam, OutParam, outLen);
	case IM_Logout_Req:
		return EncodeLogoutReq(jsInParam, OutParam, outLen);
	case IM_Logout_Rsp:
		return EncodeLogoutRsp(jsInParam, OutParam, outLen);
	case IM_KickUser:
		return EncodeKickUser(jsInParam, OutParam, outLen);
	case IM_DeviceToken_Req:
		return EncodeDeviceTokenReq(jsInParam, OutParam, outLen);
	case IM_DeviceToken_Rsp:
		return EncodeDeviceTokenRsp(jsInParam, OutParam, outLen);
	case IM_KickPCClient_Req:
	case IM_KickPCClient_Rsp:
		return EncodeKickPCClientRsp(jsInParam, OutParam, outLen);
	default:
		return IM_ERR_UNKOWNCMDID;
		break;
	}
	
}

int CIMLogin::HandleSID_Login_Receive(CImPdu* pPdu, string& OutParam)
{
	switch (pPdu->GetCommandId())
	{
	case DFFX_CID_LOGIN_REQ_USERLOGIN:
		return DecodeLoginReq(pPdu, OutParam);
	case DFFX_CID_LOGIN_RES_USERLOGIN:
		return DecodeLoginRsp(pPdu, OutParam);
	case DFFX_CID_LOGIN_REQ_LOGINOUT:
		return DecodeLogoutReq(pPdu, OutParam);
	case DFFX_CID_LOGIN_RES_LOGINOUT:
		return DecodeLogoutRsp(pPdu, OutParam);
	case DFFX_CID_LOGIN_KICK_USER:
		return DecodeKickUser(pPdu, OutParam);
	case DFFX_CID_LOGIN_REQ_DEVICETOKEN:
		return DecodeDeviceTokenReq(pPdu, OutParam);
	case DFFX_CID_LOGIN_RES_DEVICETOKEN:
		return DecodeDeviceTokenRsp(pPdu, OutParam);
	case DFFX_CID_LOGIN_REQ_KICKPCCLIENT:
	case DFFX_CID_LOGIN_RES_KICKPCCLIENT:
		return DecodeKickPCClientRsp(pPdu, OutParam);

	default:
		return IM_ERR_UNKOWNCMDID;
		break;
	}
}

int CIMLogin::EncodeLoginReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Login::IMLoginReq msg;

	if (jsInParam["user_name"].isNull() || jsInParam["password"].isNull()
		|| jsInParam["client_type"].isNull() || jsInParam["client_version"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}
	
	msg.set_user_name(jsInParam["user_name"].asString());
	msg.set_password(jsInParam["password"].asString());
	msg.set_online_status(IM::BaseDefine::USER_STATUS_ONLINE);
	msg.set_client_type(IM::BaseDefine::ClientType(jsInParam["client_type"].asInt()));
	msg.set_client_version(jsInParam["client_version"].asString());

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeLogin(&msg, DFFX_CID_LOGIN_REQ_USERLOGIN, OutParam, len, seqNo);

	return len;
}

int CIMLogin::DecodeLoginReq(CImPdu* pPdu, string& OutParam)
{
	IM::Login::IMLoginReq msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;

	jsOutParam["sid"] = IM_LOGIN;
	jsOutParam["cid"] = IM_Login_Req;

	jsOutParam["user_name"] = msg.user_name();
	jsOutParam["password"] = msg.password();
	jsOutParam["online_status"] = msg.online_status();
	jsOutParam["client_type"] = msg.client_type();
	jsOutParam["client_version"] = msg.client_version();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMLogin::EncodeLoginRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Login::IMLoginRes msg;

	if (jsInParam["server_time"].isNull() || jsInParam["result_code"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_server_time(jsInParam["server_time"].asInt());
	msg.set_result_code(IM::BaseDefine::ResultType(jsInParam["result_code"].asInt()));
	msg.set_result_string(jsInParam["result_string"].asString());
	msg.set_online_status(IM::BaseDefine::UserStatType(jsInParam["online_status"].asInt()));
	

	if (!jsInParam["user_info"].isNull())
	{
			Json::Value jUserInfo = jsInParam["user_info"];
			IM::BaseDefine::UserInfo *userInfo = msg.mutable_user_info();

			userInfo->set_user_id(jUserInfo["user_id"].asInt());
			userInfo->set_user_nickname(jUserInfo["user_nickname"].asString());
			userInfo->set_user_gender(jUserInfo["user_gender"].asInt());
			userInfo->set_user_birthday(jUserInfo["user_birthday"].asString());
			userInfo->set_user_headlink(jUserInfo["user_headlink"].asString());
			userInfo->set_user_level(jUserInfo["user_level"].asInt());
			userInfo->set_user_status(jUserInfo["user_status"].asInt());
			userInfo->set_user_uid(jUserInfo["user_uid"].asInt());
			userInfo->set_user_phone(jUserInfo["user_phone"].asString());
			userInfo->set_friend_groupid(jUserInfo["friend_groupid"].asInt());
			userInfo->set_friend_remark(jUserInfo["friend_remark"].asString());
			userInfo->set_friend_status(jUserInfo["friend_status"].asInt());
			userInfo->set_user_type(jUserInfo["user_type"].asInt());
			userInfo->set_user_ischeck(jUserInfo["user_ischeck"].asInt());
			userInfo->set_user_desc(jUserInfo["user_desc"].asString());	
	}

	msg.set_user_token(jsInParam["user_token"].asString());
	msg.set_version_max(jsInParam["version_max"].asString());
	msg.set_version_download(jsInParam["version_download"].asString());
	msg.set_version_filesize(jsInParam["version_filesize"].asString());

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeLogin(&msg, DFFX_CID_LOGIN_RES_USERLOGIN, OutParam, len, seqNo);

	return len;
}

int CIMLogin::DecodeLoginRsp(CImPdu* pPdu, string& OutParam)
{
	IM::Login::IMLoginRes msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;	
	//
	Json::Value jsUserInfo;
    Json::FastWriter jsWriter;

	jsOutParam["sid"] = IM_LOGIN;
	jsOutParam["cid"] = IM_Login_Rsp;

	jsOutParam["server_time"] = msg.server_time();
	jsOutParam["result_code"] = msg.result_code();
	jsOutParam["result_string"] = msg.result_string();
	jsOutParam["online_status"] = msg.online_status();

	jsOutParam["user_token"] = msg.user_token();
	jsOutParam["version_max"] = msg.version_max();
	jsOutParam["version_download"] = msg.version_download();
	jsOutParam["version_filesize"] = msg.version_filesize();

	//只有登录成功才返回用户信息和token
	if (0 == msg.result_code())
	{
		jsOutParam["user_token"] = msg.user_token();
		jsUserInfo["user_id"] = msg.user_info().user_id();
		jsUserInfo["user_nickname"] = msg.user_info().user_nickname();
		jsUserInfo["user_gender"] = msg.user_info().user_gender();
		jsUserInfo["user_birthday"] = msg.user_info().user_birthday();
		jsUserInfo["user_headlink"] = msg.user_info().user_headlink();
		jsUserInfo["user_level"] = msg.user_info().user_level();
		jsUserInfo["user_status"] = msg.user_info().user_status();
		jsUserInfo["user_uid"] = msg.user_info().user_uid();
		jsUserInfo["user_phone"] = msg.user_info().user_phone();
		jsUserInfo["user_type"] = msg.user_info().user_type();
		jsUserInfo["user_ischeck"] = msg.user_info().user_ischeck();
		jsUserInfo["user_desc"] = msg.user_info().user_desc();

		jsUserInfo["friend_groupid"] = msg.user_info().friend_groupid();
		jsUserInfo["friend_remark"] = msg.user_info().friend_remark();
		jsUserInfo["friend_status"] = msg.user_info().friend_status();

		jsOutParam["user_info"] = jsUserInfo;
	}

	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}



int CIMLogin::EncodeLogoutReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Login::IMLogoutReq msg;

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeLogin(&msg, DFFX_CID_LOGIN_REQ_LOGINOUT, OutParam, len, seqNo);

	return IM_ERR_SUCCESS;
}

int CIMLogin::DecodeLogoutReq(CImPdu* pPdu, string& OutParam)
{
	IM::Login::IMLogoutReq msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	Json::Value jsOutParam;

	jsOutParam["sid"] = IM_LOGIN;
	jsOutParam["cid"] = IM_Logout_Req;

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMLogin::EncodeLogoutRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Login::IMLogoutRsp msg;

	if (jsInParam["result_code"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_result_code(jsInParam["result_code"].asInt());

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeLogin(&msg, DFFX_CID_LOGIN_RES_LOGINOUT, OutParam, len, seqNo);

	return IM_ERR_SUCCESS;
}

int CIMLogin::DecodeLogoutRsp(CImPdu* pPdu, string& OutParam)
{
	IM::Login::IMLogoutRsp msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	Json::Value jsOutParam;

	jsOutParam["sid"] = IM_LOGIN;
	jsOutParam["cid"] = IM_Logout_Rsp;

	jsOutParam["result_code"] = msg.result_code();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMLogin::EncodeKickUser(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Login::IMKickUser msg;

	if (jsInParam["user_id"].isNull() || jsInParam["kick_reason"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_kick_reason(IM::BaseDefine::KickReasonType(jsInParam["kick_reason"].asInt()));

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeLogin(&msg, DFFX_CID_LOGIN_KICK_USER, OutParam, len, seqNo);

	return IM_ERR_SUCCESS;
}

int CIMLogin::DecodeKickUser(CImPdu* pPdu, string& OutParam)
{
	IM::Login::IMKickUser msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));


	Json::Value jsOutParam;
	
	jsOutParam["sid"] = IM_LOGIN;
	jsOutParam["cid"] = IM_KickUser;
	
	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["kick_reason"] = msg.kick_reason();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMLogin::EncodeDeviceTokenReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Login::IMDeviceTokenReq msg;
	
	if (jsInParam["user_id"].isNull() || jsInParam["device_token"].isNull()
		|| jsInParam["client_type"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_device_token(jsInParam["device_token"].asString());
	msg.set_client_type(IM::BaseDefine::ClientType(jsInParam["client_type"].asInt()));
	msg.set_attach_data(jsInParam["attach_data"].asString().c_str());

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeLogin(&msg, DFFX_CID_LOGIN_REQ_DEVICETOKEN, OutParam, len, seqNo);

	return IM_ERR_SUCCESS;
}

int CIMLogin::DecodeDeviceTokenReq(CImPdu* pPdu, string& OutParam)
{
	IM::Login::IMDeviceTokenReq msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	Json::Value jsOutParam;

	jsOutParam["sid"] = IM_LOGIN;
	jsOutParam["cid"] = IM_DeviceToken_Req;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["device_token"] = msg.device_token();
	jsOutParam["client_type"] = msg.client_type();
	jsOutParam["attach_data"] = msg.attach_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int  CIMLogin::EncodeDeviceTokenRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Login::IMDeviceTokenRsp msg;

	if (jsInParam["user_id"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_attach_data(jsInParam["attach_data"].asString());

	int seqNo = jsInParam["seqNo"].asInt();
	len = EncodeLogin(&msg, DFFX_CID_LOGIN_RES_DEVICETOKEN, OutParam, len, seqNo);

	return IM_ERR_SUCCESS;
}

int CIMLogin::DecodeDeviceTokenRsp(CImPdu* pPdu, string& OutParam)
{
	IM::Login::IMDeviceTokenRsp msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	Json::Value jsOutParam;

	jsOutParam["sid"] = IM_LOGIN;
	jsOutParam["cid"] = IM_DeviceToken_Rsp;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["attach_data"] = msg.attach_data();


	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMLogin::EncodeKickPCClientRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Login::IMKickPCClientRsp msg;

	if (jsInParam["user_id"].isNull() || jsInParam["result_code"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_result_code(jsInParam["result_code"].asInt());

	int seqNo = jsInParam["seqNo"].asInt();
	if (jsInParam["cid"].asInt() == IM_KickPCClient_Req)
		len = EncodeLogin(&msg, DFFX_CID_LOGIN_REQ_KICKPCCLIENT, OutParam, len, seqNo);
	else if (jsInParam["cid"].asInt() == IM_KickPCClient_Rsp)
		len = EncodeLogin(&msg, DFFX_CID_LOGIN_RES_KICKPCCLIENT, OutParam, len, seqNo);

	return IM_ERR_SUCCESS;
}

int CIMLogin::DecodeKickPCClientRsp(CImPdu* pPdu, string& OutParam)
{
	IM::Login::IMKickPCClientRsp msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	Json::Value jsOutParam;

	jsOutParam["sid"] = IM_LOGIN;
	
	if (pPdu->GetCommandId() == DFFX_CID_LOGIN_REQ_KICKPCCLIENT)
	{
		jsOutParam["cid"] = IM_KickPCClient_Req;
	}
	else if (pPdu->GetCommandId() == DFFX_CID_LOGIN_RES_KICKPCCLIENT)
	{
		jsOutParam["cid"] = IM_KickPCClient_Rsp;
	}

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["result_code"] = msg.result_code();


	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}


int CIMLogin::EncodeLogin(google::protobuf::MessageLite* msg, uint16_t command_id, unsigned char* OutParam, int& len, int seqNo)
{

	CImPdu pdu;
	pdu.SetPBMsg(msg);
	pdu.SetServiceId(DFFX_SID_LOGIN);
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