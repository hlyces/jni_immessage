#include "IMSwitchService.h"
#include "IM.BaseDefine.pb.h"


using namespace IM::BaseDefine;

CIMSwitchService::CIMSwitchService()
{
}

CIMSwitchService::~CIMSwitchService()
{
}

int CIMSwitchService::HandleSID_SwitchService_Send(IMMessageCID cid, const Json::Value& jsInParam, unsigned char* OutParam, int& outLen)
{
	switch (cid)
	{
	case IM_P2PCmdMsg:
		return EncodeP2PCmdMsg(jsInParam, OutParam, outLen);
	default:
		return IM_ERR_UNKOWNCMDID;
		break;
	}
	
}

int CIMSwitchService::HandleSID_SwitchService_Receive(CImPdu* pPdu, string& OutParam)
{
	switch (pPdu->GetCommandId())
	{
	case DFFX_CID_SWITCH_P2P_CMD:
		return DecodeP2PCmdMsg(pPdu, OutParam);
	default:
		return IM_ERR_UNKOWNCMDID;
		break;
	}
}

int CIMSwitchService::EncodeP2PCmdMsg(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::SwitchService::IMP2PCmdMsg msg;

	if (jsInParam["from_user_id"].isNull() || jsInParam["to_user_id"].isNull()
		|| jsInParam["cmd_msg_data"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}
	
	msg.set_from_user_id(jsInParam["from_user_id"].asInt());
	msg.set_to_user_id(jsInParam["to_user_id"].asInt());
	msg.set_cmd_msg_data(jsInParam["cmd_msg_data"].asString());
	
	CImPdu cPdu;
	cPdu.SetPBMsg(&msg);
	cPdu.SetServiceId(IM::BaseDefine::DFFX_SID_SWITCH_SERVICE);
	cPdu.SetCommandId(IM::BaseDefine::DFFX_CID_SWITCH_P2P_CMD);
	
	int seqNo = jsInParam["seqNo"].asInt();
	cPdu.SetSeqNum(seqNo);

	if (len < cPdu.GetLength())
		return IM_ERR_OUTPARAM_LEN;

	memcpy(OutParam, cPdu.GetBuffer(), cPdu.GetLength());

	len = cPdu.GetLength();

	return len;
}

int CIMSwitchService::DecodeP2PCmdMsg(CImPdu* pPdu, string& OutParam)
{
	IM::SwitchService::IMP2PCmdMsg msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;

	jsOutParam["sid"] = IM_SwtichService;
	jsOutParam["cid"] = IM_P2PCmdMsg;

	jsOutParam["from_user_id"] = msg.from_user_id();
	jsOutParam["to_user_id"] = msg.to_user_id();
	jsOutParam["cmd_msg_data"] = msg.cmd_msg_data();

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}
