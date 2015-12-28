
#ifndef _MESSAGE_H_
#define _MESSAGE_H_


#include <protocol/IM.Message.pb.h>

#include "imdefine.h"
using namespace IM::IMPB;

#include <string>
#include "json/json.h"
#include "ImPduBase.h"
#include<iostream>
#include <sstream>

using namespace std;

class CIMMessage
{
public:
	CIMMessage();
	~CIMMessage();

	static int HandleSID_Message_Send(IMMessageCID cid, const Json::Value& jsInParam, unsigned char* OutParam, int& outLen);
	static int HandleSID_Message_Receive(CImPdu* pPdu, string& OutParam);

private:
	//IM_Message_Data,
	static int EncodeMsgData(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeMsgData(CImPdu* pPdu, string& OutParam);

	//IM_Message_DataAck,
	//IM_Message_Data_ReadAck,
	//IM_Message_Data_Notify,
	static int EncodeMsgDataAck(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeMsgDataAck(CImPdu* pPdu, string& OutParam);

	//IM_Message_ClientTimeReq,
	static int EncodeClientTimeReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeClientTimeReq(CImPdu* pPdu, string& OutParam);

	//IM_Message_ClientTimeRsp,
	static int EncodeClientTimeRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeClientTimeRsp(CImPdu* pPdu, string& OutParam);

	//IM_Message_UnreadMsgCntReq,
	static int EncodeUnreadMsgCntReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeUnreadMsgCntReq(CImPdu* pPdu, string& OutParam);

	//IM_Message_UnreadMsgCntRsp,
	static int EncodeUnreadMsgCntRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeUnreadMsgCntRsp(CImPdu* pPdu, string& OutParam);
	
	//IM_Message_GetMsgListReq,
	static int EncodeGetMsgListReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeGetMsgListReq(CImPdu* pPdu, string& OutParam);

	//IM_Message_GetMsgListRsp,
	static int EncodeGetMsgListRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeGetMsgListRsp(CImPdu* pPdu, string& OutParam);

	//IM_Message_CleanMsgListReq,
	//IM_Message_CleanMsgListRsp,
	static int EncodeCleanMsgListRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeCleanMsgListRsp(CImPdu* pPdu, string& OutParam);

	//IM_Message_OrderStatusRead,
	//IM_Message_OrderStatusReadBroadcast
	static int EncodeOrderStatusRead(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeOrderStatusRead(CImPdu* pPdu, string& OutParam);
	
	static int EncodeMessage(google::protobuf::MessageLite* msg, uint16_t command_id, unsigned char* OutParam, int& len, int seqNo);

};

#endif
