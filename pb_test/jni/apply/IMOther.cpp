#include "IMOther.h"
#include "IM.BaseDefine.pb.h"


using namespace IM::BaseDefine;

CIMOther::CIMOther()
{
}

CIMOther::~CIMOther()
{
}

int CIMOther::HandleSID_Other_Send(IMMessageCID cid, const Json::Value& jsInParam, unsigned char* OutParam, int& outLen)
{
	switch (cid)
	{
	case IM_Other_HeartBeat:
		return EncodeHeartBeat(jsInParam, OutParam, outLen);
	default:
		return IM_ERR_UNKOWNCMDID;
		break;
	}
	
}

int CIMOther::HandleSID_Other_Receive(CImPdu* pPdu, string& OutParam)
{
	switch (pPdu->GetCommandId())
	{
	case DFFX_CID_OTHER_HEARTBEAT:
		return DecodeIMHeartBeat(pPdu, OutParam);
	default:
		return IM_ERR_UNKOWNCMDID;
		break;
	}
}


int CIMOther::EncodeHeartBeat(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::Other::IMHeartBeat msg;

	CImPdu cPdu;
	cPdu.SetPBMsg(&msg);
	cPdu.SetServiceId(IM::BaseDefine::DFFX_SID_OTHER);
	cPdu.SetCommandId(IM::BaseDefine::DFFX_CID_OTHER_HEARTBEAT);
	
	int seqNo = jsInParam["seqNo"].asInt();
	cPdu.SetSeqNum(seqNo);

	if (len < cPdu.GetLength())
		return IM_ERR_OUTPARAM_LEN;

	memcpy(OutParam, cPdu.GetBuffer(), cPdu.GetLength());

	len = cPdu.GetLength();

	return len;
}

int CIMOther::DecodeIMHeartBeat(CImPdu* pPdu, string& OutParam)
{
	IM::Other::IMHeartBeat msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;

	jsOutParam["sid"] = IM_Other;
	jsOutParam["cid"] = IM_Other_HeartBeat;

	Json::FastWriter jsWriter;
	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}
