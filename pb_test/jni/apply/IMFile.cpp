#include "IMFile.h"
#include "IM.BaseDefine.pb.h"
#include "impb_security.h"

using namespace IM::BaseDefine;

CIMFile::CIMFile()
{
}

CIMFile::~CIMFile()
{
}


int CIMFile::HandleSID_File_Send(IMMessageCID cid, const Json::Value& jsInParam, unsigned char* OutParam, int& outLen)
{
	int nRet = IM_ERR_SUCCESS;

	switch (cid)
	{
	case IM_File_Login_Req:
		nRet = EncodeFileLoginReq(jsInParam, OutParam, outLen);
		break;
	case IM_File_Login_Rsp:
		nRet = EncodeFileLoginRsp(jsInParam, OutParam, outLen);
		break;
	case IM_File_State:
		nRet = EncodeFileState(jsInParam, OutParam, outLen);
		break;
	case IM_File_Pull_Data_Req:
		nRet = EncodeFilePullDataReq(jsInParam, OutParam, outLen);
		break;
	case IM_File_Pull_Data_Rsp:
		nRet = EncodeFilePullDataRsp(jsInParam, OutParam, outLen);
		break;
	case IM_File_Request:
		nRet = EncodeFileRequest(jsInParam, OutParam, outLen);
		break;
	case IM_File_Response:
		nRet = EncodeFileResponse(jsInParam, OutParam, outLen);
		break;
	case IM_File_Notify:
		nRet = EncodeFileNotify(jsInParam, OutParam, outLen);
		break;
	case IM_File_Has_Offline_Req:
	case IM_File_Has_Offline_Rsp:
		nRet = EncodeFileHasOfflineRsp(jsInParam, OutParam, outLen);
		break;
	case IM_File_Add_Offline_Req:
		nRet = EncodeFileAddOfflineReq(jsInParam, OutParam, outLen);
		break;
	case IM_File_Del_Offline_Req:
		nRet = EncodeFileDelOfflineReq(jsInParam, OutParam, outLen);
		break;
	default:
		nRet = IM_ERR_UNKOWNCMDID;
		break;
	}

	return nRet;
}

int CIMFile::HandleSID_File_Receive(CImPdu* pPdu, string& OutParam)
{
	int nRet = IM_ERR_SUCCESS;

	switch (pPdu->GetCommandId())
	{
	case DFFX_CID_FILE_LOGIN_REQ:
		nRet = DecodeFileLoginReq(pPdu, OutParam);
		break;
	case DFFX_CID_FILE_LOGIN_RES:
		nRet = DecodeFileLoginRsp(pPdu, OutParam);
		break;
	case DFFX_CID_FILE_STATE:
		nRet = DecodeFileState(pPdu, OutParam);
		break;
	case DFFX_CID_FILE_PULL_DATA_REQ:
		nRet = DecodeFilePullDataReq(pPdu, OutParam);
		break;
	case DFFX_CID_FILE_PULL_DATA_RSP:
		nRet = DecodeFilePullDataRsp(pPdu, OutParam);
		break;
	case DFFX_CID_FILE_REQUEST:
		nRet = DecodeFileRequest(pPdu, OutParam);
		break;
	case DFFX_CID_FILE_RESPONSE:
		nRet = DecodeFileResponse(pPdu, OutParam);
		break;
	case DFFX_CID_FILE_NOTIFY:
		nRet = DecodeFileNotify(pPdu, OutParam);
		break;
	case DFFX_CID_FILE_HAS_OFFLINE_REQ:
	case DFFX_CID_FILE_HAS_OFFLINE_RES:
		nRet = DecodeFileHasOfflineRsp(pPdu, OutParam);
		break;
	case DFFX_CID_FILE_ADD_OFFLINE_REQ:
		nRet = DecodeFileAddOfflineReq(pPdu, OutParam);
		break;
	case DFFX_CID_FILE_DEL_OFFLINE_REQ:
		nRet = DecodeFileDelOfflineReq(pPdu, OutParam);
		break;
	default:
		nRet = IM_ERR_UNKOWNCMDID;
		break;
	}
	return nRet;
}

int CIMFile::EncodeFile(google::protobuf::MessageLite* msg, uint16_t command_id, unsigned char* OutParam, int& len, int seqNo)
{
	CImPdu pdu;
	pdu.SetPBMsg(msg);
	pdu.SetServiceId(DFFX_SID_FILE);
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

int CIMFile::EncodeFileLoginReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::File::IMFileLoginReq msg;

	if (jsInParam["user_id"].isNull() || jsInParam["task_id"].isNull() || jsInParam["file_role"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_task_id(jsInParam["task_id"].asString());
	msg.set_file_role(IM::BaseDefine::ClientFileRole(jsInParam["file_role"].asInt()));

	int seqNo = jsInParam["seqNo"].asInt();
	return EncodeFile(&msg, DFFX_CID_FILE_LOGIN_REQ, OutParam, len, seqNo);

}

int CIMFile::DecodeFileLoginReq(CImPdu* pPdu, string& OutParam)
{
	IM::File::IMFileLoginReq msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::FastWriter jsWriter;

	jsOutParam["sid"] = IM_File;
	jsOutParam["cid"] = IM_File_Login_Req;

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["task_id"] = msg.task_id();
	jsOutParam["file_role"] = msg.file_role();

	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMFile::EncodeFileLoginRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::File::IMFileLoginRsp msg;

	if (jsInParam["result_code"].isNull() || jsInParam["task_id"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_result_code(jsInParam["result_code"].asInt());
	msg.set_task_id(jsInParam["task_id"].asString());

	int seqNo = jsInParam["seqNo"].asInt();
	return EncodeFile(&msg, DFFX_CID_FILE_LOGIN_RES, OutParam, len, seqNo);
}

int CIMFile::DecodeFileLoginRsp(CImPdu* pPdu, string& OutParam)
{
	IM::File::IMFileLoginRsp msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::FastWriter jsWriter;

	jsOutParam["sid"] = IM_File;
	jsOutParam["cid"] = IM_File_Login_Rsp;

	jsOutParam["result_code"] = msg.result_code();
	jsOutParam["task_id"] = msg.task_id();

	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMFile::EncodeFileState(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::File::IMFileState msg;

	if (jsInParam["user_id"].isNull() || jsInParam["task_id"].isNull() || jsInParam["state"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_task_id(jsInParam["task_id"].asString());
	msg.set_state(IM::BaseDefine::ClientFileState(jsInParam["state"].asInt()));

	int seqNo = jsInParam["seqNo"].asInt();
	return EncodeFile(&msg, DFFX_CID_FILE_STATE, OutParam, len, seqNo);
}

int CIMFile::DecodeFileState(CImPdu* pPdu, string& OutParam)
{
	IM::File::IMFileState msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::FastWriter jsWriter;

	jsOutParam["sid"] = IM_File;
	jsOutParam["cid"] = IM_File_State;

	jsOutParam["state"] = msg.state();
	jsOutParam["task_id"] = msg.task_id();
	jsOutParam["user_id"] = msg.user_id();

	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMFile::EncodeFilePullDataReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::File::IMFilePullDataReq msg;

	if (jsInParam["user_id"].isNull() || jsInParam["task_id"].isNull() || jsInParam["trans_mode"].isNull()
		|| jsInParam["offset"].isNull() || jsInParam["data_size"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_task_id(jsInParam["task_id"].asString());
	msg.set_trans_mode(IM::BaseDefine::FileType(jsInParam["trans_mode"].asInt()));
	msg.set_offset(jsInParam["offset"].asInt());
	msg.set_data_size(jsInParam["data_size"].asInt());

	int seqNo = jsInParam["seqNo"].asInt();
	return EncodeFile(&msg, DFFX_CID_FILE_PULL_DATA_REQ, OutParam, len, seqNo);
}


int CIMFile::DecodeFilePullDataReq(CImPdu* pPdu, string& OutParam)
{
	IM::File::IMFilePullDataReq msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::FastWriter jsWriter;

	jsOutParam["sid"] = IM_File;
	jsOutParam["cid"] = IM_File_Pull_Data_Req;

	jsOutParam["task_id"] = msg.task_id();
	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["trans_mode"] = msg.trans_mode();
	jsOutParam["offset"] = msg.offset();
	jsOutParam["data_size"] = msg.data_size();

	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMFile::EncodeFilePullDataRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::File::IMFilePullDataRsp msg;

	if (jsInParam["result_code"].isNull() || jsInParam["task_id"].isNull() || jsInParam["user_id"].isNull()
		|| jsInParam["offset"].isNull() || jsInParam["file_data"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_result_code(jsInParam["result_code"].asInt());
	msg.set_task_id(jsInParam["task_id"].asString());
	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_offset(jsInParam["offset"].asInt());
	msg.set_file_data(jsInParam["file_data"].asString());

	int seqNo = jsInParam["seqNo"].asInt();
	return EncodeFile(&msg, DFFX_CID_FILE_PULL_DATA_RSP, OutParam, len, seqNo);
}

int CIMFile::DecodeFilePullDataRsp(CImPdu* pPdu, string& OutParam)
{
	IM::File::IMFilePullDataRsp msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::FastWriter jsWriter;

	jsOutParam["sid"] = IM_File;
	jsOutParam["cid"] = IM_File_Pull_Data_Rsp;

	jsOutParam["result_code"] = msg.result_code();
	jsOutParam["task_id"] = msg.task_id();
	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["offset"] = msg.offset();
	//jsOutParam["file_data"] = msg.file_data();
	string fileData = IMBase64Eecode(msg.file_data());
	jsOutParam["file_data"] = fileData;

	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMFile::EncodeFileRequest(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::File::IMFileReq msg;

	if (jsInParam["from_user_id"].isNull() || jsInParam["to_user_id"].isNull() || jsInParam["file_name"].isNull()
		|| jsInParam["file_size"].isNull() || jsInParam["trans_mode"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_from_user_id(jsInParam["from_user_id"].asInt());
	msg.set_to_user_id(jsInParam["to_user_id"].asInt());
	msg.set_trans_mode(IM::BaseDefine::FileType(jsInParam["trans_mode"].asInt()));
	msg.set_file_name(jsInParam["file_name"].asString());
	msg.set_file_size(jsInParam["file_size"].asInt());

	int seqNo = jsInParam["seqNo"].asInt();
	return EncodeFile(&msg, DFFX_CID_FILE_REQUEST, OutParam, len, seqNo);
}

int CIMFile::DecodeFileRequest(CImPdu* pPdu, string& OutParam)
{
	IM::File::IMFileReq msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::FastWriter jsWriter;

	jsOutParam["sid"] = IM_File;
	jsOutParam["cid"] = IM_File_Request;

	jsOutParam["from_user_id"] = msg.from_user_id();
	jsOutParam["to_user_id"] = msg.to_user_id();
	jsOutParam["file_name"] = msg.file_name();
	jsOutParam["file_size"] = msg.file_size();
	jsOutParam["trans_mode"] = msg.trans_mode();

	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMFile::EncodeFileResponse(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::File::IMFileRsp msg;

	if (jsInParam["result_code"].isNull() || jsInParam["from_user_id"].isNull()
		|| jsInParam["to_user_id"].isNull() || jsInParam["file_name"].isNull()
		|| jsInParam["task_id"].isNull() || jsInParam["trans_mode"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_result_code(jsInParam["result_code"].asInt());
	msg.set_from_user_id(jsInParam["from_user_id"].asInt());
	msg.set_to_user_id(jsInParam["to_user_id"].asInt());
	msg.set_file_name(jsInParam["file_name"].asString());
	msg.set_task_id(jsInParam["task_id"].asString());
	msg.set_trans_mode(IM::BaseDefine::FileType(jsInParam["trans_mode"].asInt()));

	if (!jsInParam["ip_addr_list"].isNull())
	{
		Json::Value jsArr = jsInParam["ip_addr_list"];
		for (unsigned int i = 0; i < jsArr.size(); i++)
		{
			Json::Value jsInfo = jsArr[i];
			IM::BaseDefine::IpAddr*	pInfo = msg.add_ip_addr_list();
			pInfo->set_ip(jsInfo["ip"].asString());
			pInfo->set_port(jsInfo["port"].asInt());
		}
	}

	int seqNo = jsInParam["seqNo"].asInt();
	return EncodeFile(&msg, DFFX_CID_FILE_RESPONSE, OutParam, len, seqNo);
}

int CIMFile::DecodeFileResponse(CImPdu* pPdu, string& OutParam)
{
	IM::File::IMFileRsp msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsIpAddrArray;
	Json::FastWriter jsWriter;

	jsOutParam["sid"] = IM_File;
	jsOutParam["cid"] = IM_File_Response;

	jsOutParam["result_code"] = msg.result_code();
	jsOutParam["from_user_id"] = msg.from_user_id();
	jsOutParam["to_user_id"] = msg.to_user_id();
	jsOutParam["file_name"] = msg.file_name();
	jsOutParam["task_id"] = msg.task_id();
	jsOutParam["trans_mode"] = msg.trans_mode();

	// ip_addr_list
	uint32_t nCnt = msg.ip_addr_list_size();
	for (uint32_t i = 0; i < nCnt; ++i)
	{
		IM::BaseDefine::IpAddr ipAddr = msg.ip_addr_list(i);

		Json::Value jsIpAddr;
		jsIpAddr["ip"] = ipAddr.ip();
		jsIpAddr["port"] = ipAddr.port();
		jsIpAddrArray[i] = jsIpAddr;
	}

	jsOutParam["ip_addr_list"] = jsIpAddrArray;

	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMFile::EncodeFileNotify(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::File::IMFileNotify msg;

	if (jsInParam["from_user_id"].isNull() || jsInParam["to_user_id"].isNull() || jsInParam["file_name"].isNull()
		|| jsInParam["file_size"].isNull() || jsInParam["trans_mode"].isNull() || jsInParam["offline_ready"].isNull()
		|| jsInParam["task_id"].isNull() || jsInParam["ip_addr_list"].isNull()
		)
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_from_user_id(jsInParam["from_user_id"].asInt());
	msg.set_to_user_id(jsInParam["to_user_id"].asInt());
	msg.set_trans_mode(IM::BaseDefine::FileType(jsInParam["trans_mode"].asInt()));
	msg.set_file_name(jsInParam["file_name"].asString());
	msg.set_file_size(jsInParam["file_size"].asInt());
	msg.set_task_id(jsInParam["task_id"].asString());
	msg.set_offline_ready(jsInParam["offline_ready"].asInt());

	//ip_addr_list
	Json::Value readerIPArray = jsInParam["ip_addr_list"];
	for (unsigned int i = 0; i < readerIPArray.size(); i++)
	{
		IM::BaseDefine::IpAddr* pIpAddr = msg.add_ip_addr_list();
		pIpAddr->set_ip(readerIPArray[i]["ip"].asString());
		pIpAddr->set_port(readerIPArray[i]["port"].asInt());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	return EncodeFile(&msg, DFFX_CID_FILE_NOTIFY, OutParam, len, seqNo);
}

int CIMFile::DecodeFileNotify(CImPdu* pPdu, string& OutParam)
{
	IM::File::IMFileNotify msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsIpAddrArray;
	Json::FastWriter jsWriter;

	jsOutParam["sid"] = IM_File;
	jsOutParam["cid"] = IM_File_Notify;

	jsOutParam["from_user_id"] = msg.from_user_id();
	jsOutParam["to_user_id"] = msg.to_user_id();
	jsOutParam["file_name"] = msg.file_name();
	jsOutParam["file_size"] = msg.file_size();
	jsOutParam["task_id"] = msg.task_id();
	jsOutParam["trans_mode"] = msg.trans_mode();
	jsOutParam["offline_ready"] = msg.offline_ready();

	// ip_addr_list
	uint32_t nCnt = msg.ip_addr_list_size();
	for (uint32_t i = 0; i < nCnt; ++i)
	{
		IM::BaseDefine::IpAddr ipAddr = msg.ip_addr_list(i);

		Json::Value jsIpAddr;
		jsIpAddr["ip"] = ipAddr.ip();
		jsIpAddr["port"] = ipAddr.port();
		jsIpAddrArray[i] = jsIpAddr;
	}

	jsOutParam["ip_addr_list"] = jsIpAddrArray;

	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}


int CIMFile::EncodeFileHasOfflineRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::File::IMFileHasOfflineRsp msg;

	if (jsInParam["user_id"].isNull() || jsInParam["attach_data"].isNull() || jsInParam["offline_file_list"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_user_id(jsInParam["user_id"].asInt());
	msg.set_attach_data(jsInParam["attach_data"].asString());

	//offline_file_list
	Json::Value readerIPArray = jsInParam["offline_file_list"];
	for (unsigned int i = 0; i < readerIPArray.size(); i++)
	{
		IM::BaseDefine::OfflineFileInfo* pOfflineFileInfo = msg.add_offline_file_list();
		pOfflineFileInfo->set_from_user_id(readerIPArray[i]["from_user_id"].asInt());
		pOfflineFileInfo->set_task_id(readerIPArray[i]["task_id"].asString());
		pOfflineFileInfo->set_file_name(readerIPArray[i]["file_name"].asString());
		pOfflineFileInfo->set_file_size(readerIPArray[i]["file_size"].asInt());
		pOfflineFileInfo->set_send_time(readerIPArray[i]["send_time"].asInt());

		// ip_addr_list
		Json::Value ipArray = readerIPArray[i]["ip_addr_list"];
		for (uint32_t j = 0; j < ipArray.size(); j++)
		{
			IM::BaseDefine::IpAddr* pIPAddr = pOfflineFileInfo->add_ip_addr_list();

			pIPAddr->set_ip(ipArray[j]["ip"].asString());
			pIPAddr->set_port(ipArray[j]["port"].asInt());
		}
	}

	int seqNo = jsInParam["seqNo"].asInt();
	if (jsInParam["cid"].asInt() == IM_File_Has_Offline_Req)
		return EncodeFile(&msg, DFFX_CID_FILE_HAS_OFFLINE_REQ, OutParam, len, seqNo);
	else if (jsInParam["cid"].asInt() == IM_File_Has_Offline_Rsp)
		return EncodeFile(&msg, DFFX_CID_FILE_HAS_OFFLINE_RES, OutParam, len, seqNo);
	else
		return IM_ERR_UNKOWNCMDID;
}

int CIMFile::DecodeFileHasOfflineRsp(CImPdu* pPdu, string& OutParam)
{
	IM::File::IMFileHasOfflineRsp msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsOfflineFileInfoArray;
	Json::Value jsIpAddrArray;
	Json::FastWriter jsWriter;

	jsOutParam["sid"] = IM_File;

	if (pPdu->GetCommandId() == DFFX_CID_FILE_HAS_OFFLINE_REQ)
	{
		jsOutParam["cid"] = IM_File_Has_Offline_Req;
	}
	else if (pPdu->GetCommandId() == DFFX_CID_FILE_HAS_OFFLINE_RES)
	{
		jsOutParam["cid"] = IM_File_Has_Offline_Rsp;
	}

	jsOutParam["user_id"] = msg.user_id();
	jsOutParam["attach_data"] = msg.attach_data();

	// offline_file_list
	uint32_t nCnt = msg.offline_file_list_size();
	for (uint32_t i = 0; i < nCnt; ++i)
	{
		IM::BaseDefine::OfflineFileInfo offlineFileInfo = msg.offline_file_list(i);

		Json::Value jsOfflineFileInfo;
		jsOfflineFileInfo["from_user_id"] = offlineFileInfo.from_user_id();
		jsOfflineFileInfo["task_id"] = offlineFileInfo.task_id();
		jsOfflineFileInfo["file_name"] = offlineFileInfo.file_name();
		jsOfflineFileInfo["file_size"] = offlineFileInfo.file_size();
		jsOfflineFileInfo["send_time"] = offlineFileInfo.send_time();

		// ip_addr_list
		uint32_t nIpAddrCnt = offlineFileInfo.ip_addr_list_size();
		for (uint32_t j = 0; j < nIpAddrCnt; ++j)
		{
			IM::BaseDefine::IpAddr ipAddr = offlineFileInfo.ip_addr_list(j);

			Json::Value jsIpAddr;
			jsIpAddr["ip"] = ipAddr.ip();
			jsIpAddr["port"] = ipAddr.port();
			jsIpAddrArray[j] = jsIpAddr;
		}

		jsOfflineFileInfo["ip_addr_list"] = jsIpAddrArray;
		jsOfflineFileInfoArray[i] = jsOfflineFileInfo;
	}

	jsOutParam["offline_file_list"] = jsOfflineFileInfoArray;

	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}
int CIMFile::EncodeFileAddOfflineReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::File::IMFileAddOfflineReq msg;

	if (jsInParam["from_user_id"].isNull() || jsInParam["to_user_id"].isNull() || jsInParam["file_name"].isNull()
		|| jsInParam["file_size"].isNull() || jsInParam["task_id"].isNull() || jsInParam["ip_addr_list"].isNull()
		)
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_from_user_id(jsInParam["from_user_id"].asInt());
	msg.set_to_user_id(jsInParam["to_user_id"].asInt());
	msg.set_file_name(jsInParam["file_name"].asString());
	msg.set_file_size(jsInParam["file_size"].asInt());
	msg.set_task_id(jsInParam["task_id"].asString());

	//ip_addr_list
	Json::Value readerIPArray = jsInParam["ip_addr_list"];
	for (unsigned int i = 0; i < readerIPArray.size(); i++)
	{
		IM::BaseDefine::IpAddr* pIpAddr = msg.add_ip_addr_list();
		pIpAddr->set_ip(readerIPArray[i]["ip"].asString());
		pIpAddr->set_port(readerIPArray[i]["port"].asInt());
	}

	int seqNo = jsInParam["seqNo"].asInt();
	return EncodeFile(&msg, DFFX_CID_FILE_ADD_OFFLINE_REQ, OutParam, len, seqNo);
}

int CIMFile::DecodeFileAddOfflineReq(CImPdu* pPdu, string& OutParam)
{
	IM::File::IMFileAddOfflineReq msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::Value jsIpAddrArray;
	Json::FastWriter jsWriter;

	jsOutParam["sid"] = IM_File;
	jsOutParam["cid"] = IM_File_Add_Offline_Req;

	jsOutParam["from_user_id"] = msg.from_user_id();
	jsOutParam["to_user_id"] = msg.to_user_id();
	jsOutParam["task_id"] = msg.task_id();
	jsOutParam["file_name"] = msg.file_name();
	jsOutParam["file_size"] = msg.file_size();

	// ip_addr_list
	uint32_t nCnt = msg.ip_addr_list_size();
	for (uint32_t i = 0; i < nCnt; ++i)
	{
		IM::BaseDefine::IpAddr ipAddr = msg.ip_addr_list(i);

		Json::Value jsIpAddr;
		jsIpAddr["ip"] = ipAddr.ip();
		jsIpAddr["port"] = ipAddr.port();
		jsIpAddrArray[i] = jsIpAddr;
	}

	jsOutParam["ip_addr_list"] = jsIpAddrArray;

	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}

int CIMFile::EncodeFileDelOfflineReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len)
{
	IM::File::IMFileDelOfflineReq msg;

	if (jsInParam["from_user_id"].isNull() || jsInParam["to_user_id"].isNull() || jsInParam["task_id"].isNull())
	{
		return IM_ERR_JSONPARAM;
	}

	msg.set_from_user_id(jsInParam["from_user_id"].asInt());
	msg.set_to_user_id(jsInParam["to_user_id"].asInt());
	msg.set_task_id(jsInParam["task_id"].asString());

	int seqNo = jsInParam["seqNo"].asInt();
	return EncodeFile(&msg, DFFX_CID_FILE_DEL_OFFLINE_REQ, OutParam, len, seqNo);

}

int CIMFile::DecodeFileDelOfflineReq(CImPdu* pPdu, string& OutParam)
{
	IM::File::IMFileDelOfflineReq msg;
	CHECK_PB_PARSE_MSG(msg.ParseFromArray(pPdu->GetBodyData(), pPdu->GetBodyLength()));

	//json 
	Json::Value jsOutParam;
	Json::FastWriter jsWriter;

	jsOutParam["sid"] = IM_File;
	jsOutParam["cid"] = IM_File_Del_Offline_Req;

	jsOutParam["from_user_id"] = msg.from_user_id();
	jsOutParam["to_user_id"] = msg.to_user_id();
	jsOutParam["task_id"] = msg.task_id();

	OutParam = jsWriter.write(jsOutParam);

	return IM_ERR_SUCCESS;
}
