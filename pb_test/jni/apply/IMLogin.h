
#ifndef _LOGIN_H_
#define _LOGIN_H_


#include <protocol/IM.Login.pb.h>

#include "imdefine.h"
using namespace IM::IMPB;

#include <string>
#include "json/json.h"
#include "ImPduBase.h"
#include <sstream>

using namespace std;

class CIMLogin
{
public:
	CIMLogin();
	~CIMLogin();

	static int HandleSID_Login_Send(IMMessageCID cid, const Json::Value& jsInParam, unsigned char* OutParam, int& outLen);
	static int HandleSID_Login_Receive(CImPdu* pPdu, string& OutParam);

private:
	//IM_Login_Req,
	static int EncodeLoginReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeLoginReq(CImPdu* pPdu, string& OutParam);

	//IM_Login_Rsp,
	static int EncodeLoginRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeLoginRsp(CImPdu* pPdu, string& OutParam);

	//IM_Logout_Req,
	static int EncodeLogoutReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeLogoutReq(CImPdu* pPdu, string& OutParam);

	//IM_Logout_Rsp,
	static int EncodeLogoutRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeLogoutRsp(CImPdu* pPdu, string& OutParam);

	//IM_KickUser,
	static int EncodeKickUser(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeKickUser(CImPdu* pPdu, string& OutParam);

	//IM_DeviceToken_Req,
	static int EncodeDeviceTokenReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeDeviceTokenReq(CImPdu* pPdu, string& OutParam);

	//IM_DeviceToken_Rsp,
	static int EncodeDeviceTokenRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeDeviceTokenRsp(CImPdu* pPdu, string& OutParam);

	//IM_KickPCClient_Req,
	//IM_KickPCClient_Rsp,
	static int EncodeKickPCClientRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeKickPCClientRsp(CImPdu* pPdu, string& OutParam);
	

	static int EncodeLogin(google::protobuf::MessageLite* msg, uint16_t command_id, unsigned char* OutParam, int& len, int seqNo);

};

#endif
