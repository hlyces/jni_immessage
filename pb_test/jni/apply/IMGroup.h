
#ifndef _IMBUDDY_H_
#define _IMBUDDY_H_


#include <protocol/IM.Group.pb.h>

#include "imdefine.h"
using namespace IM::IMPB;

#include <string>
#include "json/json.h"
#include "ImPduBase.h"
#include <sstream>

using namespace std;

class CIMGroup
{
public:
	CIMGroup();
	~CIMGroup();

	static int HandleSID_Group_Send(IMMessageCID cid, const Json::Value& jsInParam, unsigned char* OutParam, int& outLen);
	static int HandleSID_Group_Receive(CImPdu* pPdu, string& OutParam);

private:
	static int EncodeGroup(google::protobuf::MessageLite* msg, uint16_t command_id, unsigned char* OutParam, int& len, int seqNo);
	static int EncodeIMNormalGroupListReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int EncodeIMGroupInfoListReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int EncodeIMGroupCreateReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int EncodeIMGroupChangeMemberReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int EncodeIMGroupShieldReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int EncodeIMGroupChangeMemberNotify(const Json::Value& jsInParam, unsigned char* OutParam, int& len);


	static int DecodeIMNormalGroupListRsp(CImPdu* pPdu, string& OutParam);
	static int DecodeIMGroupInfoListRsp(CImPdu* pPdu, string& OutParam);
	static int DecodeIMGroupCreateRsp(CImPdu* pPdu, string& OutParam);
	static int DecodeIMGroupChangeMemberRsp(CImPdu* pPdu, string& OutParam);
	static int DecodeIMGroupShieldRsp(CImPdu* pPdu, string& OutParam);
	static int DecodeIMGroupChangeMemberNotify(CImPdu* pPdu, string& OutParam);

};

#endif
