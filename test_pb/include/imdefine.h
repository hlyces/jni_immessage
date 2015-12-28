#ifndef __IMDEFINE__H__
#define __IMDEFINE__H__

namespace IM{
	namespace IMPB{

//消息CID
enum IMMessageCID
{
	//login
	IM_Login_Req,	
	IM_Login_Rsp,
	IM_Logout_Req,
	IM_Logout_Rsp,
	IM_KickUser,
	IM_DeviceToken_Req,
	IM_DeviceToken_Rsp,
	IM_KickPCClient_Req,
	IM_KickPCClient_Rsp,


	//message
	IM_Message_Data,
	IM_Message_DataAck,
	IM_Message_Data_ReadAck,
	IM_Message_Data_Notify,
	IM_Message_ClientTimeReq,
	IM_Message_ClientTimeRsp,
	IM_Message_UnreadMsgCntReq,
	IM_Message_UnreadMsgCntRsp,
	IM_Message_GetMsgListReq,
	IM_Message_GetMsgListRsp,
	IM_Message_CleanMsgListReq,
	IM_Message_CleanMsgListRsp,
	IM_Message_OrderStatusRead,
	IM_Message_OrderStatusReadBroadcast,


	//file
	IM_File_Login_Req,
	IM_File_Login_Rsp,
	IM_File_State,
	IM_File_Pull_Data_Req,
	IM_File_Pull_Data_Rsp,
	IM_File_Request,
	IM_File_Response,
	IM_File_Notify,
	IM_File_Has_Offline_Req,
	IM_File_Has_Offline_Rsp,
	IM_File_Add_Offline_Req,
	IM_File_Del_Offline_Req,

	//group
	IM_Group_Normal_List_Req,
	IM_Group_Normal_List_Rsp,
	IM_Group_Info_Req,
	IM_Group_Info_Rsp,
	IM_Group_Create_Req,
	IM_Group_Create_Rsp,
	IM_Group_Change_Member_Req,
	IM_Group_Change_Member_Rsp,
	IM_Group_Shield_Group_Req,
	IM_Group_Shield_Group_Rsp,
	IM_Group_Change_Member_Notify,

	//buddy
	IM_Buddy_RecentContactSessionReq,
	IM_Buddy_RecentContactSessionRsp,
	IM_Buddy_UserStatNotify,
	IM_Buddy_UsersInfoReq,
	IM_Buddy_UsersInfoRsp,
	IM_Buddy_RemoveSessionReq,
	IM_Buddy_RemoveSessionRsp,
	IM_Buddy_AllUserReq,
	IM_Buddy_AllUserRsp,
	IM_Buddy_UsersStatReq,
	IM_Buddy_UsersStatRsp,
	IM_Buddy_PCLoginStatusNotify,
	IM_Buddy_RemoveSessionNotify,
	IM_Buddy_DepartmentReq,
	IM_Buddy_DepartmentRsp,

	IM_Buddy_AddFriendReq, 
	IM_Buddy_AddFriendRsp,
	IM_Buddy_ReverseAddFriendReq,
	IM_Buddy_ReverseAddFriendRsp,
	IM_Buddy_DelFriendReq,
	IM_Buddy_DelFriendRsp,
	IM_Buddy_ChgFiendRemarkReq,
	IM_Buddy_ChgFiendRemarkRsp,

	IM_Buddy_CreateFiendGroupReq,
	IM_Buddy_CreateFiendGroupRsp,
	IM_Buddy_DelFiendGroupReq,
	IM_Buddy_DelFiendGroupRsp,
	IM_Buddy_MoveFiendGroupReq,
	IM_Buddy_MoveFiendGroupRsp,
	IM_Buddy_ChgFiendGroupNameReq,
	IM_Buddy_ChgFiendGroupNameRsp,

	IM_Buddy_FiendNotifyReq,
	IM_Buddy_FiendNotifyRsp,
	IM_Buddy_GetAddFriendReq,
	IM_Buddy_GetAddFriendRsp,
	IM_Buddy_FindUserInfoReq,
	IM_Buddy_FindUserInfoRsp,

	IM_Buddy_DelFriendNotify,


	//other
	IM_Other_HeartBeat,

	//switchservice
	IM_P2PCmdMsg,
};

//消息SID
enum IMMessageSID
{
	IM_LOGIN,
	IM_BUDDY_LIST,
	IM_MESSAGE,
	IM_File,
	IM_Group,
	IM_Other,
	IM_SwtichService,
};

//错误码
enum IMErrMsg
{
	IM_ERR_SUCCESS = 0,		//成功
	IM_ERR_JSONPARSE = -200,	//json解析失败
	IM_ERR_PBPARSE,			//pb解析失败
	IM_ERR_UNKOWNSERVID,		//未知的SID
	IM_ERR_UNKOWNCMDID,		//未知的CID
	IM_ERR_OUTPARAM_LEN,	//接收参数内存不够
	IM_ERR_MEMORY,			//内存分配失败
	IM_ERR_EXCEPTION,		//异常
	IM_ERR_NOTENOUGH,		//输入数据不够，不足以解析消息包
	IM_ERR_ENCRPYTMSG,		//解密消息数据失败
	IM_ERR_JSONPARAM,		//json参数字段有误
};


//订单推送消息状态码
enum OrderMsgStatus{
	CONSULT_DOCUMENTS_GRAB = 0, //咨询与文书代写一人抢单成功通知公众端
	LAWSUIT_ATTENDANCE_GRAB = 1, //打官司与出勤五人（最多五人）进入抢单列表通知公众端
	GRAB_SUCCESS = 2, //律师抢单成功通知律师端
	GRAB_FAID = 3, //律师抢单失败通知律师端
	ENTRUST_ACCEPT = 4, //律师委托受理通知公众端
	ENTRUST_CANCEL = 5, //公众委托取消通知律师端
	TOPUP_SUCCESS = 6, //充值成功通知客户端（包括律师端与公众端）
	TOPUP_FAILED = 7, //充值失败通知客户端（包括律师端与公众端）
	BWITHDRAWAL_SUCCESS = 8, //余额提现成功通知客户端（包括律师端与公众端）
	BWITHDRAWAL_FAILED = 9, //余额提现失败通知客户端（包括律师端与公众端）
	TWITHDRAWAL_SUCCESS = 10, //业务收益成功通知客户端（律师端）
	TWITHDRAWAL_FAILED = 11, //业务收益失败通知客户端（律师端）
	CHECK_SUCCESS = 12, //用户信息认证通知客户端（包括律师端与公众端）
	CHECK_FAILED = 13, //用户信息认证失败通知客户端（包括律师端与公众端）
	USER_CANCEL = 14, //处理过程中用户撤销订单通知律师端
	VALID_CANCEL = 15, //过期撤销订单通知律师端
	ORDER_COMPLETE = 16, //订单完成通知律师端
	ORDER_REVOKE = 17,//律师申请付款 用户撤回律师的付款金额要求
	ORDER_PAY_FAILED = 18, //订单支付失败，与TOPUP_SUCCESS属于一种MsgType
};


enum ResultType{						//这里定义了登陆返回错误码。
	REFUSE_REASON_NONE = 0,				//未知错误
	REFUSE_REASON_NO_MSG_SERVER = 1,	//没有msg_server
	REFUSE_REASON_MSG_SERVER_FULL = 2,	//msg_server已满
	REFUSE_REASON_NO_DB_SERVER = 3,		//没有db_server
	REFUSE_REASON_NO_LOGIN_SERVER = 4,	//没有login_server
	REFUSE_REASON_NO_ROUTE_SERVER = 5,	//没有route_server
	REFUSE_REASON_DB_VALIDATE_FAILED = 6,	//数据验证失败	
	REFUSE_REASON_VERSION_TOO_OLD = 7,	//客户端版本太老

};

enum KickReasonType{
	KICK_REASON_DUPLICATE_USER = 1,
	KICK_REASON_MOBILE_KICK = 2,
};

enum UserStatType{					  //用户状态：在线，离线，离开
	USER_STATUS_ONLINE = 1,
	USER_STATUS_OFFLINE = 2,
	USER_STATUS_LEAVE = 3,

};

enum SessionType{
	SESSION_TYPE_SINGLE = 1,          	//单个用户会话
	SESSION_TYPE_GROUP = 2,          	//群会话
};

enum MsgType{						//消息类型： 单聊文本，单聊音频，群聊文本，群聊音频
	MSG_TYPE_SINGLE_TEXT = 0x01,
	MSG_TYPE_SINGLE_AUDIO = 0x02,
	MSG_TYPE_GROUP_TEXT = 0x11,
	MSG_TYPE_GROUP_AUDIO = 0x12,
	MSG_TYPE_ORDER_PUSH = 0x21, //推送给律师订单消息
	MSG_TYPE_ORDER_GRAB = 0x22,	//推送给客户，律师的抢单状况
	MSG_TYPE_ORDER_RESULT = 0x23,	//通知律师抢单结果
	MSG_TYPE_ORDER_ENTRUST = 0x24, //订单委托
	MSG_TYPE_ORDER_ACCEPT = 0x25,	//委托订单受理
	MSG_TYPE_ORDER_CANCEL = 0x26, //委托订单取消
	MSG_TYPE_TOPUP_WITHDRAWAL = 0X27, //推送提现或充值消息给用户
	MSG_TYPE_USER_CHECK = 0X28, //用户身份认证消息
	MSG_TYPE_ORDER_WAITPAYMENT = 0x29, //订单等待付款通知客户端
	MSG_TYPE_ORDER_ALLCANCEL = 0x2a,	//通知律师端所有的撤销订单（包括过期撤销与用户撤销以及订单完成与用户撤单）
	MSG_TYPE_LOCATION_SHARING = 0x31,	//位置分享消息
	MSG_TYPE_FILE_TRANSFER = 0x32,	//文件消息

};

enum ClientType{					//客户端操作系统类型：
	CLIENT_TYPE_WINDOWS = 0x01,
	CLIENT_TYPE_MAC = 0x02,
	CLIENT_TYPE_IOS = 0x11,
	CLIENT_TYPE_ANDROID = 0x12,
};

enum GroupType{						//群组类型：正常群组，临时群组
	GROUP_TYPE_NORMAL = 0x01,
	GROUP_TYPE_TMP = 0x02,
};

enum GroupModifyType{				//组修改类型：添加，删除
	GROUP_MODIFY_TYPE_ADD = 0x01,
	GROUP_MODIFY_TYPE_DEL = 0x02,
};

enum FileType{						//在线文件，离线文件
	FILE_TYPE_ONLINE = 0x01,
	FILE_TYPE_OFFLINE = 0x02,
};

enum ClientFileState{				//文件传输状态定义:对方已准备好 取消 拒绝 完成
	CLIENT_FILE_PEER_READY = 0x00,
	CLIENT_FILE_CANCEL = 0x01,
	CLIENT_FILE_REFUSE = 0x02,
	CLIENT_FILE_DONE = 0x03,
};

enum ClientFileRole{				//文件传输角色定义 实时发送者 实时接受者 离线上传 离线下载	
	CLIENT_REALTIME_SENDER = 0x01,
	CLIENT_REALTIME_RECVER = 0x02,
	CLIENT_OFFLINE_UPLOAD = 0x03,
	CLIENT_OFFLINE_DOWNLOAD = 0x04,
};

enum FileServerError{			//文件传输错误码。
	FILE_SERVER_ERRNO_OK = 0x00,
	FILE_SERVER_ERRNO_CREATE_TASK_ID_ERROR = 0x01,
	FILE_SERVER_ERRNO_CREATE_TASK_ERROR = 0x02,
	FILE_SERVER_ERRNO_LOGIN_INVALID_TOKEN = 0x03,
	FILE_SERVER_ERRNO_INVALID_USER_FOR_TASK = 0x04,
	FILE_SERVER_ERRNO_PULL_DATA_WITH_INVALID_TASK_ID = 0x05,
	FILE_SERVER_ERRNO_PULL_DATA_ILLIEAGE_USER = 0x06,
	FILE_SERVER_ERRNO_PULL_DATA_MKDIR_ERROR = 0x07,
	FILE_SERVER_ERRNO_PULL_DATA_OPEN_FILE_ERROR = 0x08,
	FILE_SERVER_ERRNO_PULL_DATA_READ_FILE_HEADER_ERROR = 0x09,
	FILE_SERVER_ERRNO_PULL_DATA_ALLOC_MEM_ERROR = 0x0a,
	FILE_SERVER_ERRNO_PULL_DATA_SEEK_OFFSET_ERROR = 0x0b,
	FILE_SERVER_ERRNO_PULL_DATA_FINISHED = 0x0c,
};

enum SessionStatusType{		//状态定义，删除，正常。
	SESSION_STATUS_OK = 0x00,
	SESSION_STATUS_DELETE = 0x01,
};

enum DepartmentStatusType{		//部门状态定义。
	DEPT_STATUS_OK = 0x00,
	DEPT_STATUS_DELETE = 0x01,
};


enum FriendResStatusType{		//好友请求状态类型
	FRIENDRES_STATUS_AGREE = 0x00,    //同意
	FRIENDRES_STATUS_REFUSE = 0x01,	//拒绝
	FRIENDRES_STATUS_IGNORE = 0x02,	//忽略
};

	}
}
#endif

#ifdef __ANDROID__

#include <android/log.h>

#ifndef  LOG_TAG
#define  LOG_TAG    "Android_IMPB_JNI"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)
#endif
#endif