#include "IMGroup.h"
#include "IM.BaseDefine.pb.h"

using namespace IM::BaseDefine;

CIMGroup::CIMGroup()
{
}

CIMGroup::~CIMGroup()
{
}

int CIMGroup::HandleSID_Group_Send(IMMessageCID cid, const Json::Value& jsInParam, unsigned char* OutParam, int& outLen)
{
	int nRet = IM_ERR_SUCCESS;

	switch (cid)
	{
	case IM_Group_Normal_List_Req:
		nRet = EncodeIMNormalGroupListReq(jsInParam, OutParam, outLen);
		break;
	case IM_Group_Info_Req:
		nRet = EncodeIMGroupInfoListReq(jsInParam, OutParam, outLen);
		break;
	case IM_Group_Create_Req:
		nRet = EncodeIMGroupCreateReq(jsInParam, OutParam, outLen);
		break;
	case IM_Group_Change_Member_Req:
		nRet = EncodeIMGroupChangeMemberReq(jsInParam, OutParam, outLen);
		break;
	case IM_Group_Shield_Group_Req:
		nRet = EncodeIMGroupShieldReq(jsInParam, OutParam, outLen);
		break;
	case IM_Group_Change_Member_Notify:
		nRet = EncodeIMGroupChangeMemberNotify(jsInParam, OutParam, outLen);
		break;
	default:
		nRet = IM_ERR_UNKOWNCMDID;
		break;
	}

	return nRet;
}

int CIMGroup::HandleSID_Group_Receive(CImPdu* pPdu, string& OutParam)
{
	int nRet = IM_ERR_SUCCESS;

	switch (pPdu->GetCommandId())
	{
	case DFFX_CID_GROUP_NORMAL_LIST_RESPONSE:
		nRet = DecodeIMNormalGroupListRsp(pPdu, OutParam);
		break;
	case DFFX_CID_GROUP_INFO_RESPONSE:
		nRet = DecodeIMGroupInfoListRsp(pPdu, OutParam);
		break;
	case DFFX_CID_GROUP_CREATE_RESPONSE:
		nRet = DecodeIMGroupCreateRsp(pPdu, OutParam);
		break;
	case DFFX_CID_GROUP_CHANGE_MEMBER_RESPONSE:
		nRet = DecodeIMGroupChangeMemberRsp(pPdu, OutParam);
		break;
	case DFFX_CID_GROUP_SHIELD_GROUP_RESPONSE:
		nRet = DecodeIMGroupShieldRsp(pPdu, OutParam);
		break;
	case DFFX_CID_GROUP_CHANGE_MEMBER_NOTIFY:
		nRet = DecodeIMGroupChangeMemberNotify(pPdu, OutParam);
		break;
	default:
		nRet = IM_ERR_UNKOWNCMDID;
		break;
	}
	return nRet;
}

int CIMGroup::EncodeGroup(google::protobuf::MessageLite* msg, uint16_t command_id, unsigned char* OutParam, int& len, int seqNo)
{
	CImPdu pdu;
	pdu.SetPBMsg(msg);
	pdu.SetServiceId(DFFX_SID_GROUP);
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

int CIMGroup::EncodeIMNormalGroupListReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Group::IMNormalGroupListRsp msg;

	if (jsInParam["user_id"].isNull() || jsInParam["attach_data"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_attach_data(jsInParam["attach_data"].asString());

	int seqNo = jsInParam["seqNo"].asInt();
	return EncodeGroup(&msg, DFFX_CID_GROUP_NORMAL_LIST_REQUEST, OutParam, len, seqNo);
}

int CIMGroup::EncodeIMGroupInfoListReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Group::IMGroupInfoListReq msg;

	if (jsInParam["user_id"].isNull() || jsInParam["attach_data"].isNull() || jsInParam["group_version_list"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_attach_data(jsInParam["attach_data"].asString());

	//group_version_list
	Json::Value readerVersionInfoArray = jsInParam["group_version_list"];
	for (unsigned int i = 0; i < readerVersionInfoArray.size(); i++)
	{
		IM::BaseDefine::GroupVersionInfo* pGroupVersionInfo = msg.add_group_version_list();
		pGroupVersionInfo->set_group_id(readerVersionInfoArray[i]["group_id"].asInt());
		pGroupVersionInfo->set_version(readerVersionInfoArray[i]["version"].asInt());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	return EncodeGroup(&msg, DFFX_CID_GROUP_INFO_REQUEST, OutParam, len, seqNo);
}

int CIMGroup::EncodeIMGroupCreateReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Group::IMGroupCreateReq msg;

	if (jsInParam["user_id"].isNull() || jsInParam["group_type"].isNull() || jsInParam["group_name"].isNull()
		|| jsInParam["group_avatar"].isNull() || jsInParam["member_id_list"].isNull() || jsInParam["attach_data"].isNull()
		)
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_group_type(IM::BaseDefine::GroupType(jsInParam["group_type"].asInt()));
	msg.set_group_name(jsInParam["group_name"].asString());
	msg.set_group_avatar(jsInParam["group_avatar"].asString());
	msg.set_attach_data(jsInParam["attach_data"].asString());

	//member_id_list
	Json::Value readerIdListArray = jsInParam["member_id_list"];
	for (unsigned int i = 0; i < readerIdListArray.size(); i++)
	{
		msg.add_member_id_list(readerIdListArray[i].asInt());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	return EncodeGroup(&msg, DFFX_CID_GROUP_CREATE_REQUEST, OutParam, len, seqNo);
}

int CIMGroup::EncodeIMGroupChangeMemberReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Group::IMGroupChangeMemberReq msg;

	if (jsInParam["user_id"].isNull() || jsInParam["change_type"].isNull() || jsInParam["group_id"].isNull()
		|| jsInParam["member_id_list"].isNull() || jsInParam["attach_data"].isNull()
		)
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_change_type(IM::BaseDefine::GroupModifyType(jsInParam["change_type"].asInt()));
	msg.set_group_id(jsInParam["group_id"].asInt());
	msg.set_attach_data(jsInParam["attach_data"].asString());

	//member_id_list
	Json::Value readerIdListArray = jsInParam["member_id_list"];
	for (unsigned int i = 0; i < readerIdListArray.size(); i++)
	{
		msg.add_member_id_list(readerIdListArray[i].asInt());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	return EncodeGroup(&msg, DFFX_CID_GROUP_CHANGE_MEMBER_REQUEST, OutParam, len, seqNo);
}

int CIMGroup::EncodeIMGroupShieldReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Group::IMGroupShieldReq msg;

	if (jsInParam["user_id"].isNull() || jsInParam["group_id"].isNull() || jsInParam["shield_status"].isNull()
		|| jsInParam["attach_data"].isNull()
		)
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_group_id(jsInParam["group_id"].asInt());
	msg.set_shield_status(jsInParam["shield_status"].asInt());
	msg.set_attach_data(jsInParam["attach_data"].asString());

	int seqNo = jsInParam["seqNo"].asInt();
	return EncodeGroup(&msg, DFFX_CID_GROUP_SHIELD_GROUP_REQUEST, OutParam, len, seqNo);
}

int CIMGroup::EncodeIMGroupChangeMemberNotify(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Group::IMGroupChangeMemberRsp msg;

	if (jsInParam["user_id"].isNull() || jsInParam["change_type"].isNull() || jsInParam["group_id"].isNull()
		|| jsInParam["cur_user_id_list"].isNull() || jsInParam["chg_user_id_list"].isNull()
		)
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_change_type(IM::BaseDefine::GroupModifyType(jsInParam["change_type"].asInt()));
	msg.set_group_id(jsInParam["group_id"].asInt());

	//cur_user_id_list
	Json::Value readerCurIdListArray = jsInParam["cur_user_id_list"];
	for (unsigned int i = 0; i < readerCurIdListArray.size(); i++)
	{
		msg.add_cur_user_id_list(readerCurIdListArray[i].asInt());
	}

	//chg_user_id_list
	Json::Value readerChgIdListArray = jsInParam["chg_user_id_list"];
	for (unsigned int i = 0; i < readerChgIdListArray.size(); i++)
	{
		msg.add_chg_user_id_list(readerChgIdListArray[i].asInt());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	return EncodeGroup(&msg, DFFX_CID_GROUP_CHANGE_MEMBER_NOTIFY, OutParam, len, seqNo);
}

int CIMGroup::DecodeIMNormalGroupListRsp(CImPdu* pPdu, string& OutParam)
{
	IM::Group::IMNormalGroupListRsp msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsGroupVersionInfoArray;
	Json::FastWriter jsWriter;

	jsOutParam["sid"] = IM_Group;
	jsOutParam["cid"] = IM_Group_Normal_List_Rsp;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["attach_data"] = msg.attach_data();

	// group_version_list
	uint32_t nCnt = msg.group_version_list_size();
	for (uint32_t i = 0; i<nCnt; ++i)
	{
		IM::BaseDefine::GroupVersionInfo groupVersionInfo = msg.group_version_list(i);

		Json::Value jsGroupVersionInfo;
		jsGroupVersionInfo["group_id"] = groupVersionInfo.group_id();
		jsGroupVersionInfo["version"] = groupVersionInfo.version();
		jsGroupVersionInfoArray[i] = jsGroupVersionInfo;
	}

	jsOutParam["group_version_list"] = jsGroupVersionInfoArray;

	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMGroup::DecodeIMGroupInfoListRsp(CImPdu* pPdu, string& OutParam)
{
	IM::Group::IMGroupInfoListRsp msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsGroupInforArray;
	Json::Value jsMemberListArray;
	Json::FastWriter jsWriter;

	jsOutParam["sid"] = IM_Group;
	jsOutParam["cid"] = IM_Group_Info_Rsp;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["attach_data"] = msg.attach_data();

	// group_info_list
	uint32_t nCnt = msg.group_info_list_size();
	for (uint32_t i = 0; i<nCnt; ++i)
	{
		IM::BaseDefine::GroupInfo groupInfo = msg.group_info_list(i);

		Json::Value jsGroupInfo;
		jsGroupInfo["group_id"] = groupInfo.group_id();
		jsGroupInfo["version"] = groupInfo.version();
		jsGroupInfo["group_name"] = groupInfo.group_name();
		jsGroupInfo["group_avatar"] = groupInfo.group_avatar();

		jsGroupInfo["group_creator_id"] = groupInfo.group_creator_id();
		jsGroupInfo["group_type"] = groupInfo.group_type();
		jsGroupInfo["shield_status"] = groupInfo.shield_status();

		//group_member_list
		uint32_t nMemberCnt = groupInfo.group_member_list_size();
		for (uint32_t j = 0; j < nMemberCnt; j++)
		{
			jsMemberListArray[j] = groupInfo.group_member_list(j);
		}
		jsGroupInfo["group_member_list"] = jsMemberListArray;

		jsGroupInforArray[i] = jsGroupInfo;
	}

	jsOutParam["group_version_list"] = jsGroupInforArray;

	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMGroup::DecodeIMGroupCreateRsp(CImPdu* pPdu, string& OutParam)
{
	IM::Group::IMGroupCreateRsp msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsIdListArray;
	Json::FastWriter jsWriter;

	jsOutParam["sid"] = IM_Group;
	jsOutParam["cid"] = IM_Group_Create_Rsp;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["result_code"] = msg.result_code();
	jsOutParam["group_id"] = msg.group_id();
	jsOutParam["group_name"] = msg.group_name();

	jsOutParam["attach_data"] = msg.attach_data();

	//user_id_list
	uint32_t nMemberCnt = msg.user_id_list_size();
	for (uint32_t j = 0; j < nMemberCnt; j++)
	{
		jsIdListArray[j] = msg.user_id_list(j);
	}
	jsOutParam["user_id_list"] = jsIdListArray;


	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;

}

int CIMGroup::DecodeIMGroupChangeMemberRsp(CImPdu* pPdu, string& OutParam)
{
	IM::Group::IMGroupChangeMemberRsp msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsCurIdListArray;
	Json::Value jsChgIdListArray;
	Json::FastWriter jsWriter;

	jsOutParam["sid"] = IM_Group;
	jsOutParam["cid"] = IM_Group_Change_Member_Rsp;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["change_type"] = msg.change_type();
	jsOutParam["result_code"] = msg.result_code();
	jsOutParam["group_id"] = msg.group_id();

	jsOutParam["attach_data"] = msg.attach_data();

	//cur_user_id_list
	uint32_t nCurMemberCnt = msg.cur_user_id_list_size();
	for (uint32_t j = 0; j < nCurMemberCnt; j++)
	{
		jsCurIdListArray[j] = msg.cur_user_id_list(j);
	}
	jsOutParam["cur_user_id_list"] = jsCurIdListArray;

	//chg_user_id_list
	uint32_t nChgMemberCnt = msg.chg_user_id_list_size();
	for (uint32_t i = 0; i < nChgMemberCnt; i++)
	{
		jsChgIdListArray[i] = msg.chg_user_id_list(i);
	}
	jsOutParam["chg_user_id_list"] = jsChgIdListArray;

	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMGroup::DecodeIMGroupShieldRsp(CImPdu* pPdu, string& OutParam)
{
	IM::Group::IMGroupShieldReq msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::FastWriter jsWriter;

	jsOutParam["sid"] = IM_Group;
	jsOutParam["cid"] = IM_Group_Shield_Group_Rsp;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["group_id"] = msg.group_id();
	jsOutParam["shield_status"] = msg.shield_status();
	jsOutParam["attach_data"] = msg.attach_data();

	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMGroup::DecodeIMGroupChangeMemberNotify(CImPdu* pPdu, string& OutParam)
{
	IM::Group::IMGroupChangeMemberRsp msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsCurIdListArray;
	Json::Value jsChgIdListArray;
	Json::FastWriter jsWriter;

	jsOutParam["sid"] = IM_Group;
	jsOutParam["cid"] = IM_Group_Change_Member_Notify;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["change_type"] = msg.change_type();
	jsOutParam["result_code"] = msg.result_code();
	jsOutParam["group_id"] = msg.group_id();

	jsOutParam["attach_data"] = msg.attach_data();

	//cur_user_id_list
	uint32_t nCurMemberCnt = msg.cur_user_id_list_size();
	for (uint32_t j = 0; j < nCurMemberCnt; j++)
	{
		jsCurIdListArray[j] = msg.cur_user_id_list(j);
	}
	jsOutParam["cur_user_id_list"] = jsCurIdListArray;

	//chg_user_id_list
	uint32_t nChgMemberCnt = msg.chg_user_id_list_size();
	for (uint32_t i = 0; i < nChgMemberCnt; i++)
	{
		jsChgIdListArray[i] = msg.chg_user_id_list(i);
	}
	jsOutParam["chg_user_id_list"] = jsChgIdListArray;

	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}