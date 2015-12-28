
#ifndef _IMFILE_H_
#define _IMFILE_H_


#include <protocol/IM.File.pb.h>

#include "imdefine.h"
using namespace IM::IMPB;

#include <string>
#include "json/json.h"
#include "ImPduBase.h"
#include <sstream>

using namespace std;

class CIMFile
{
public:
	CIMFile();
	~CIMFile();

	static int HandleSID_File_Send(IMMessageCID cid, const Json::Value& jsInParam, unsigned char* OutParam, int& outLen);
	static int HandleSID_File_Receive(CImPdu* pPdu, string& OutParam);

private:
	static int EncodeFile(google::protobuf::MessageLite* msg, uint16_t command_id, unsigned char* OutParam, int& len, int seqNo);

	//IM_File_Login_Req,
	static int EncodeFileLoginReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeFileLoginReq(CImPdu* pPdu, string& OutParam);

	//IM_File_Login_Rsp,
	static int EncodeFileLoginRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeFileLoginRsp(CImPdu* pPdu, string& OutParam);

	//IM_File_State,
	static int EncodeFileState(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeFileState(CImPdu* pPdu, string& OutParam);

	//IM_File_Pull_Data_Req,
	static int EncodeFilePullDataReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeFilePullDataReq(CImPdu* pPdu, string& OutParam);

	//IM_File_Pull_Data_Rsp,
	static int EncodeFilePullDataRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeFilePullDataRsp(CImPdu* pPdu, string& OutParam);

	//IM_File_Request,
	static int EncodeFileRequest(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeFileRequest(CImPdu* pPdu, string& OutParam);

	//IM_File_Response,
	static int EncodeFileResponse(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeFileResponse(CImPdu* pPdu, string& OutParam);
	
	//IM_File_Notify,
	static int EncodeFileNotify(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeFileNotify(CImPdu* pPdu, string& OutParam);

	//IM_File_Has_Offline_Req,
	//IM_File_Has_Offline_Rsp,
	static int EncodeFileHasOfflineRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeFileHasOfflineRsp(CImPdu* pPdu, string& OutParam);

	//IM_File_Add_Offline_Req,
	static int EncodeFileAddOfflineReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeFileAddOfflineReq(CImPdu* pPdu, string& OutParam);

	//IM_File_Del_Offline_Req,
	static int EncodeFileDelOfflineReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeFileDelOfflineReq(CImPdu* pPdu, string& OutParam);

};

#endif
