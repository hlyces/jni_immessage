#ifndef __IMDEFINE__H__
#define __IMDEFINE__H__

namespace IM{
	namespace IMPB{

//��ϢCID
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

//��ϢSID
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

//������
enum IMErrMsg
{
	IM_ERR_SUCCESS = 0,		//�ɹ�
	IM_ERR_JSONPARSE = -200,	//json����ʧ��
	IM_ERR_PBPARSE,			//pb����ʧ��
	IM_ERR_UNKOWNSERVID,		//δ֪��SID
	IM_ERR_UNKOWNCMDID,		//δ֪��CID
	IM_ERR_OUTPARAM_LEN,	//���ղ����ڴ治��
	IM_ERR_MEMORY,			//�ڴ����ʧ��
	IM_ERR_EXCEPTION,		//�쳣
	IM_ERR_NOTENOUGH,		//�������ݲ����������Խ�����Ϣ��
	IM_ERR_ENCRPYTMSG,		//������Ϣ����ʧ��
	IM_ERR_JSONPARAM,		//json�����ֶ�����
};


//����������Ϣ״̬��
enum OrderMsgStatus{
	CONSULT_DOCUMENTS_GRAB = 0, //��ѯ�������дһ�������ɹ�֪ͨ���ڶ�
	LAWSUIT_ATTENDANCE_GRAB = 1, //���˾��������ˣ�������ˣ����������б�֪ͨ���ڶ�
	GRAB_SUCCESS = 2, //��ʦ�����ɹ�֪ͨ��ʦ��
	GRAB_FAID = 3, //��ʦ����ʧ��֪ͨ��ʦ��
	ENTRUST_ACCEPT = 4, //��ʦί������֪ͨ���ڶ�
	ENTRUST_CANCEL = 5, //����ί��ȡ��֪ͨ��ʦ��
	TOPUP_SUCCESS = 6, //��ֵ�ɹ�֪ͨ�ͻ��ˣ�������ʦ���빫�ڶˣ�
	TOPUP_FAILED = 7, //��ֵʧ��֪ͨ�ͻ��ˣ�������ʦ���빫�ڶˣ�
	BWITHDRAWAL_SUCCESS = 8, //������ֳɹ�֪ͨ�ͻ��ˣ�������ʦ���빫�ڶˣ�
	BWITHDRAWAL_FAILED = 9, //�������ʧ��֪ͨ�ͻ��ˣ�������ʦ���빫�ڶˣ�
	TWITHDRAWAL_SUCCESS = 10, //ҵ������ɹ�֪ͨ�ͻ��ˣ���ʦ�ˣ�
	TWITHDRAWAL_FAILED = 11, //ҵ������ʧ��֪ͨ�ͻ��ˣ���ʦ�ˣ�
	CHECK_SUCCESS = 12, //�û���Ϣ��֤֪ͨ�ͻ��ˣ�������ʦ���빫�ڶˣ�
	CHECK_FAILED = 13, //�û���Ϣ��֤ʧ��֪ͨ�ͻ��ˣ�������ʦ���빫�ڶˣ�
	USER_CANCEL = 14, //����������û���������֪ͨ��ʦ��
	VALID_CANCEL = 15, //���ڳ�������֪ͨ��ʦ��
	ORDER_COMPLETE = 16, //�������֪ͨ��ʦ��
	ORDER_REVOKE = 17,//��ʦ���븶�� �û�������ʦ�ĸ�����Ҫ��
	ORDER_PAY_FAILED = 18, //����֧��ʧ�ܣ���TOPUP_SUCCESS����һ��MsgType
};


enum ResultType{						//���ﶨ���˵�½���ش����롣
	REFUSE_REASON_NONE = 0,				//δ֪����
	REFUSE_REASON_NO_MSG_SERVER = 1,	//û��msg_server
	REFUSE_REASON_MSG_SERVER_FULL = 2,	//msg_server����
	REFUSE_REASON_NO_DB_SERVER = 3,		//û��db_server
	REFUSE_REASON_NO_LOGIN_SERVER = 4,	//û��login_server
	REFUSE_REASON_NO_ROUTE_SERVER = 5,	//û��route_server
	REFUSE_REASON_DB_VALIDATE_FAILED = 6,	//������֤ʧ��	
	REFUSE_REASON_VERSION_TOO_OLD = 7,	//�ͻ��˰汾̫��

};

enum KickReasonType{
	KICK_REASON_DUPLICATE_USER = 1,
	KICK_REASON_MOBILE_KICK = 2,
};

enum UserStatType{					  //�û�״̬�����ߣ����ߣ��뿪
	USER_STATUS_ONLINE = 1,
	USER_STATUS_OFFLINE = 2,
	USER_STATUS_LEAVE = 3,

};

enum SessionType{
	SESSION_TYPE_SINGLE = 1,          	//�����û��Ự
	SESSION_TYPE_GROUP = 2,          	//Ⱥ�Ự
};

enum MsgType{						//��Ϣ���ͣ� �����ı���������Ƶ��Ⱥ���ı���Ⱥ����Ƶ
	MSG_TYPE_SINGLE_TEXT = 0x01,
	MSG_TYPE_SINGLE_AUDIO = 0x02,
	MSG_TYPE_GROUP_TEXT = 0x11,
	MSG_TYPE_GROUP_AUDIO = 0x12,
	MSG_TYPE_ORDER_PUSH = 0x21, //���͸���ʦ������Ϣ
	MSG_TYPE_ORDER_GRAB = 0x22,	//���͸��ͻ�����ʦ������״��
	MSG_TYPE_ORDER_RESULT = 0x23,	//֪ͨ��ʦ�������
	MSG_TYPE_ORDER_ENTRUST = 0x24, //����ί��
	MSG_TYPE_ORDER_ACCEPT = 0x25,	//ί�ж�������
	MSG_TYPE_ORDER_CANCEL = 0x26, //ί�ж���ȡ��
	MSG_TYPE_TOPUP_WITHDRAWAL = 0X27, //�������ֻ��ֵ��Ϣ���û�
	MSG_TYPE_USER_CHECK = 0X28, //�û������֤��Ϣ
	MSG_TYPE_ORDER_WAITPAYMENT = 0x29, //�����ȴ�����֪ͨ�ͻ���
	MSG_TYPE_ORDER_ALLCANCEL = 0x2a,	//֪ͨ��ʦ�����еĳ����������������ڳ������û������Լ�����������û�������
	MSG_TYPE_LOCATION_SHARING = 0x31,	//λ�÷�����Ϣ
	MSG_TYPE_FILE_TRANSFER = 0x32,	//�ļ���Ϣ

};

enum ClientType{					//�ͻ��˲���ϵͳ���ͣ�
	CLIENT_TYPE_WINDOWS = 0x01,
	CLIENT_TYPE_MAC = 0x02,
	CLIENT_TYPE_IOS = 0x11,
	CLIENT_TYPE_ANDROID = 0x12,
};

enum GroupType{						//Ⱥ�����ͣ�����Ⱥ�飬��ʱȺ��
	GROUP_TYPE_NORMAL = 0x01,
	GROUP_TYPE_TMP = 0x02,
};

enum GroupModifyType{				//���޸����ͣ���ӣ�ɾ��
	GROUP_MODIFY_TYPE_ADD = 0x01,
	GROUP_MODIFY_TYPE_DEL = 0x02,
};

enum FileType{						//�����ļ��������ļ�
	FILE_TYPE_ONLINE = 0x01,
	FILE_TYPE_OFFLINE = 0x02,
};

enum ClientFileState{				//�ļ�����״̬����:�Է���׼���� ȡ�� �ܾ� ���
	CLIENT_FILE_PEER_READY = 0x00,
	CLIENT_FILE_CANCEL = 0x01,
	CLIENT_FILE_REFUSE = 0x02,
	CLIENT_FILE_DONE = 0x03,
};

enum ClientFileRole{				//�ļ������ɫ���� ʵʱ������ ʵʱ������ �����ϴ� ��������	
	CLIENT_REALTIME_SENDER = 0x01,
	CLIENT_REALTIME_RECVER = 0x02,
	CLIENT_OFFLINE_UPLOAD = 0x03,
	CLIENT_OFFLINE_DOWNLOAD = 0x04,
};

enum FileServerError{			//�ļ���������롣
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

enum SessionStatusType{		//״̬���壬ɾ����������
	SESSION_STATUS_OK = 0x00,
	SESSION_STATUS_DELETE = 0x01,
};

enum DepartmentStatusType{		//����״̬���塣
	DEPT_STATUS_OK = 0x00,
	DEPT_STATUS_DELETE = 0x01,
};


enum FriendResStatusType{		//��������״̬����
	FRIENDRES_STATUS_AGREE = 0x00,    //ͬ��
	FRIENDRES_STATUS_REFUSE = 0x01,	//�ܾ�
	FRIENDRES_STATUS_IGNORE = 0x02,	//����
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