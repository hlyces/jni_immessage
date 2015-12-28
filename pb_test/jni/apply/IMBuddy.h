
#ifndef _BUDDY_H_
#define _BUDDY_H_

#include "IM.Buddy.pb.h"

#include "imdefine.h"
using namespace IM::IMPB;

#include <string>
#include "json/json.h"
#include "ImPduBase.h"
#include <sstream>

using namespace std;

class CIMBuddy
{
public:
	CIMBuddy();
	~CIMBuddy();

	static int HandleSID_Buddy_Send(IMMessageCID cid, const Json::Value& jsInParam, unsigned char* OutParam, int& outLen);
	static int HandleSID_Buddy_Receive(CImPdu* pPdu, string& OutParam);

private:
	//IM_Buddy_RecentContactSessionReq,
	static int EncodeRecentContactSessionReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeRecentContactSessionReq(CImPdu* pPdu, string& OutParam);

	//IM_Buddy_RecentContactSessionRsp,
	static int EncodeRecentContactSessionRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeRecentContactSessionRsp(CImPdu* pPdu, string& OutParam);

	//IM_Buddy_UserStatNotify,
	static int EncodeUserStatNotify(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeUserStatNotify(CImPdu* pPdu, string& OutParam);

	//IM_Buddy_UsersInfoReq,
	//IM_Buddy_UsersStatReq,
	static int EncodeUsersInfoReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeUsersInfoReq(CImPdu* pPdu, string& OutParam);
	
	//IM_Buddy_UsersInfoRsp,
	//IM_Buddy_AllUserReq,
	//IM_Buddy_AllUserRsp,
	//IM_Buddy_FindUserInfoRsp,
	static int EncodeAllUserRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeAllUserRsp(CImPdu* pPdu, string& OutParam);
		
	//IM_Buddy_UsersStatRsp,
	static int EncodeUsersStatRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeUsersStatRsp(CImPdu* pPdu, string& OutParam);
	
	//IM_Buddy_RemoveSessionReq,
	//IM_Buddy_RemoveSessionRsp,
	static int EncodeRemoveSessionRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeRemoveSessionRsp(CImPdu* pPdu, string& OutParam);

	//IM_Buddy_PCLoginStatusNotify,
	static int EncodePCLoginStatusNotify(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodePCLoginStatusNotify(CImPdu* pPdu, string& OutParam);
	
	//IM_Buddy_RemoveSessionNotify,
	static int EncodeRemoveSessionNotify(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeRemoveSessionNotify(CImPdu* pPdu, string& OutParam);
	
	//IM_Buddy_DepartmentReq,
	//IM_Buddy_DepartmentRsp,
	static int EncodeDepartmentRsp(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeDepartmentRsp(CImPdu* pPdu, string& OutParam);

	//IM_Buddy_AddFriendReq, 
	static int EncodeAddFriendReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeAddFriendReq(CImPdu* pPdu, string& OutParam);

	//IM_Buddy_AddFriendRsp,
	//IM_Buddy_ReverseAddFriendRsp,
	//IM_Buddy_DelFriendRsp,
	//IM_Buddy_DelFriendNotify,
	//IM_Buddy_ChgFiendRemarkRsp,	
	static int EncodeCommonOperFriendRes(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeCommonOperFriendRes(CImPdu* pPdu, string& OutParam);

	//IM_Buddy_ReverseAddFriendReq,
	static int EncodeIMReverseAddFriendReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeIMReverseAddFriendReq(CImPdu* pPdu, string& OutParam);

	//IM_Buddy_DelFriendReq,
	//IM_Buddy_CreateFiendGroupRsp
	//IM_Buddy_DelFiendGroupReq,
	//IM_Buddy_DelFiendGroupRsp,
	//IM_Buddy_MoveFiendGroupRsp,
	//IM_Buddy_ChgFiendGroupNameRsp,
	static int EncodeCommonOperFriendGroupRes(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeCommonOperFriendGroupRes(CImPdu* pPdu, string& OutParam);

	//IM_Buddy_ChgFiendRemarkReq,
	//IM_Buddy_ChgFiendGroupNameReq,
	static int EncodeChgFriendRemarkReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeChgFriendRemarkReq(CImPdu* pPdu, string& OutParam);

	//IM_Buddy_CreateFiendGroupReq,
	static int EncodeCreateFriendGroupReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeCreateFriendGroupReq(CImPdu* pPdu, string& OutParam);

	//IM_Buddy_MoveFiendGroupReq,
	static int EncodeMoveFriendToGroupReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len); 
	static int DecodeMoveFriendToGroupReq(CImPdu* pPdu, string& OutParam);

	//IM_Buddy_FiendNotifyReq,
	static int EncodeFriendNotifyReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeFriendNotifyReq(CImPdu* pPdu, string& OutParam);

	//IM_Buddy_FiendNotifyRsp,
	static int EncodeFriendNotifyRes(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeFriendNotifyRes(CImPdu* pPdu, string& OutParam);
	
	//IM_Buddy_GetAddFriendReq,
	static int EncodeGetAddFriendReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeGetAddFriendReq(CImPdu* pPdu, string& OutParam);

	//IM_Buddy_GetAddFriendRsp,
	static int EncodeGetAddFriendRes(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeGetAddFriendRes(CImPdu* pPdu, string& OutParam);
	
	//IM_Buddy_FindUserInfoReq,
	static int EncodeFindUserInfoReq(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeFindUserInfoReq(CImPdu* pPdu, string& OutParam);
	
	static int EncodeBuddy(google::protobuf::MessageLite* msg, uint16_t command_id, unsigned char* OutParam, int& len, int seqNO);

};

#endif
