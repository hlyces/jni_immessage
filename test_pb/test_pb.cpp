

#include<string>
#include <ios>
#include <iostream>
#include <fstream>
using namespace std;

#include "include/imdefine.h"
#include "include/impb_interface.h"
#include "include/impb_security.h"
#include <stdio.h>
#include "json/json.h"

string ToHexString(unsigned char* bytes, int len);
void TestPb(IMMessageSID sid, IMMessageCID cid, string inParam);
void TestPass(string strPass);
void TestCrypto(string strMsgData);
void TestLogin();
void TestMessage();
void TestFile();
void TestBuddy();
void TestSwitchService();
void TestOther();

int main(void)
{
	//fstream fout("outFile.txt");

	//streambuf *oldbuf = cout.rdbuf(fout.rdbuf());//保存标准输出并定向到文件
	
	cout << "hello world" << endl;

	//TestPass("abcdef123456");
	//TestCrypto("123456abcdef");

	//TestLogin();
	TestMessage();
	//TestFile();
	//TestBuddy();
	//TestOther();
	//TestSwitchService();

#ifdef WIN32
	system("pause");
#endif
}

void TestSwitchService()
{
	string inParam = "{\"sid\": 6,\"cid\": 85,\"from_user_id\": 1000020, \"to_user_id\": 123123,\"cmd_msg_data\": \"fqwoefn[qowehfg]\"}";
	TestPb(IM_SwtichService, IM_P2PCmdMsg, inParam);
}

void TestOther()
{
	string inParam = "{\"sid\": 5,\"cid\": 84}";
	TestPb(IM_Other, IM_Other_HeartBeat, inParam);
}

void TestLogin()
{
	string inParam = "{\"sid\": 0,\"cid\": 0,\"online_status\":1,\"user_name\":\"100050\",\"password\":\"e10adc3949ba59abbe56e057f20f883e\",\"client_type\":1,\"client_version\":\"100.0.0\"}";
	TestPb(IM_LOGIN, IM_Login_Req, inParam);

	inParam = "{\"sid\": 0,\"cid\": 1,\"server_time\": 14500864,\"result_code\": 0,\"result_string\": \"未知错误\",\"online_status\": 1,\"user_token\": \"3fe52189-c196-4e2b-9219-ee061305445f\",\"user_info\": {\"user_id\": 100231,\"user_nickname\": \"cong\",\"user_gender\": 2,\"user_birthday\": \"1991-09-09\",\"user_headlink\": \"http://www.bejson.com/\",\"user_level\": 1,\"user_status\": 1,\"user_uid\": 100231,\"user_phone\": \"11111111111\",\"friend_status\":1, \"friend_groupid\": 1,\"friend_remark\": \"cong\",\"user_type\": 1,\"user_ischeck\": 1,\"user_desc\": \"adfwafqewfer\"},\"version_max\": \"1.1.9\",\"version_download\": \"http://www.bejson.com/\",\"version_filesize\": \"16.6M\"}";
	TestPb(IM_LOGIN, IM_Login_Rsp, inParam);

	inParam = "{\"sid\": 0,\"cid\": 2}";
	TestPb(IM_LOGIN, IM_Logout_Req, inParam);

	inParam = "{\"sid\": 0,\"cid\": 3,\"result_code\": 1}";
	TestPb(IM_LOGIN, IM_Logout_Rsp, inParam);

	inParam = "{\"sid\": 0,\"cid\": 4,\"user_id\": 1,\"kick_reason\": 1}";
	TestPb(IM_LOGIN, IM_KickUser, inParam);

	inParam = "{\"sid\": 0,\"cid\": 5,\"user_id\": 1,\"device_token\": \"dasjfdjajsdnfq-wefqfwe\", \"client_type\": 1, \"attach_data\": \"hello-wefqfwe\"}";
	TestPb(IM_LOGIN, IM_DeviceToken_Req, inParam);

	inParam = "{\"sid\": 0,\"cid\": 6,\"user_id\": 1,\"attach_data\": \"hello-wefqfwe\"}";
	TestPb(IM_LOGIN, IM_DeviceToken_Rsp, inParam);

	inParam = "{\"sid\": 0,\"cid\": 7,\"user_id\": 1,\"result_code\": 1}";
	TestPb(IM_LOGIN, IM_KickPCClient_Req, inParam);

	inParam = "{\"sid\": 0,\"cid\": 8,\"user_id\": 1,\"result_code\": 1}";
	TestPb(IM_LOGIN, IM_KickPCClient_Rsp, inParam);
}

void TestMessage()
{
	string strMsgData = "{\\\"path\\\":\\\"http://192.168.1.12:8700/g0/00/00/1450858353057991_140150939453.audio\\\",\\\"size\\\":234,\\\"duration\\\":2}";
	string inParam = "{\"attach_data\": \"\", \"seqNo\": 65536,\"cid\": 9, \"create_time\": 1450858353, \"from_user_id\": 100213, \"is_black\": 0,\"msg_data\": \"  "  + strMsgData + " \",\"msg_id\": 312,  \"msg_type\": 2, \"sid\": 2, \"to_session_id\": 100082}";
	TestPb(IM_MESSAGE, IM_Message_Data, inParam);
	/*inParam = "{\"sid\": 2,\"cid\": 10,\"user_id\": 100002,\"session_id\": 2,\"msg_id\": 11,\"session_type\": 1,\"is_black\": 1}";
	TestPb(IM_MESSAGE, IM_Message_DataAck, inParam);*/
	//inParam = "{\"sid\": 2,\"cid\": 11,\"user_id\": 100002,\"session_id\": 2,\"msg_id\": 11,\"session_type\": 1,\"is_black\": 1}";
	//TestPb(IM_MESSAGE, IM_Message_Data_ReadAck, inParam);
	//inParam = "{\"sid\": 2,\"cid\": 12,\"user_id\": 100002,\"session_id\": 2,\"msg_id\": 11,\"session_type\": 1,\"is_black\": 1}";
	//TestPb(IM_MESSAGE, IM_Message_Data_Notify, inParam);
	//inParam = "{\"sid\": 2,\"cid\": 13}";
	//TestPb(IM_MESSAGE, IM_Message_ClientTimeReq, inParam);
	//inParam = "{\"sid\": 2,\"cid\": 14,\"server_time\": 1450408647}";
	//TestPb(IM_MESSAGE, IM_Message_ClientTimeRsp, inParam);
	//inParam = "{\"sid\": 2,\"cid\": 15,\"user_id\": 100002, \"attach_data\": \"122123\"}";
	//TestPb(IM_MESSAGE, IM_Message_UnreadMsgCntReq, inParam);
	//inParam = "{\"sid\": 2,\"cid\": 16,\"user_id\": 100002,\"total_cnt\": 2,\"unreadinfo_list\": [{\"session_id\": 11,\"session_type\": 1,\"unread_cnt\": 10,\"latest_msg_id\": 111,\"latest_msg_data\":\"e10adc3949ba59abbe56e057f20f883e\",\"latest_msg_type\": 1,\"latest_msg_from_user_id\": 100020,\"latest_msg_time\": 1450408647},{\"session_id\": 21,\"session_type\": 1,\"unread_cnt\": 10,\"latest_msg_id\": 111,\"latest_msg_data\":\"e10adc3949ba59abbe56e057f20f883e\",\"latest_msg_type\": 1,\"latest_msg_from_user_id\": 100021,\"latest_msg_time\": 1450408647}], \"attach_data\": \"hello-wefqfwe\"}";
	//TestPb(IM_MESSAGE, IM_Message_UnreadMsgCntRsp, inParam);
	//inParam = "{\"sid\": 2,\"cid\": 17,\"user_id\": 1000020, \"session_type\": 1,\"session_id\": 10,\"msg_id_begin\": 1,\"msg_cnt\": 11, \"attach_data\": \"122123\"}";
	//TestPb(IM_MESSAGE, IM_Message_GetMsgListReq, inParam);
	//inParam = "{\"sid\": 2,\"cid\": 18,\"user_id\": 1000020, \"session_type\": 1,\"session_id\": 1,\"msg_id_begin\": 10,\"msg_list\": [{\"msg_id\": 1,\"from_session_id\": 100231,\"create_time\": 1450408647,\"msg_type\": 1,\"msg_data\": \"hellolllfcowefmpqewfpo\"},{\"msg_id\": 1,\"from_session_id\": 100231,\"create_time\": 1450408647,\"msg_type\": 1,\"msg_data\": \"hellolllfcowefmpqewfpo\"}], \"attach_data\": \"122123\"}";
	//TestPb(IM_MESSAGE, IM_Message_GetMsgListRsp, inParam);
	//inParam = "{\"sid\": 2,\"cid\": 19,\"user_id\": 1000020, \"session_type\": 1,\"session_id\": 1,\"result_code\": 1,\"attach_data\": \"fqwoefn[qowehfg]\"}";
	//TestPb(IM_MESSAGE, IM_Message_CleanMsgListReq, inParam);
	//inParam = "{\"sid\": 2,\"cid\": 20,\"user_id\": 1000020, \"session_type\": 1,\"session_id\": 1,\"result_code\": 1,\"attach_data\": \"fqwoefn[qowehfg]\"}";
	//TestPb(IM_MESSAGE, IM_Message_CleanMsgListRsp, inParam);
	//inParam = "{\"sid\": 2,\"cid\": 21,\"user_id\": 1000020, \"order_id\": 265,\"orderlist_is_null\": 1,\"attach_data\": \"fqwoefn[qowehfg]\"}";
	//TestPb(IM_MESSAGE, IM_Message_OrderStatusRead, inParam);
	//inParam = "{\"sid\": 2,\"cid\": 22,\"user_id\": 1000020, \"order_id\": 265,\"orderlist_is_null\": 1,\"attach_data\": \"fqwoefn[qowehfg]\"}";
	//TestPb(IM_MESSAGE, IM_Message_OrderStatusReadBroadcast, inParam);

}

void TestBuddy()
{
	string inParam = "{\"sid\": 1,\"cid\": 46,\"user_id\": 1000020, \"latest_update_time\": 412341243,\"attach_data\": \"fqwoefn[qowehfg]\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_RecentContactSessionReq, inParam);
	inParam = "{\"sid\": 1,\"cid\": 47,\"user_id\": 1000020, \"contact_session_list\": [{\"session_id\": 12,\"session_type\": 1,\"session_status\": 0,\"updated_time\": 1450408647,\"latest_msg_id\": 22,\"latest_msg_data\": \"fqwefqwe\",\"latest_msg_type\": 1,\"latest_msg_from_user_id\": 123}],\"attach_data\": \"fqwoefnqowehfg\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_RecentContactSessionRsp, inParam);
	inParam = "{\"sid\": 1,\"cid\": 48,\"user_stat\": {\"user_id\": 46,\"status\": 1,\"client_type\": 2}}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_UserStatNotify, inParam);
	inParam = "{\"sid\": 1,\"cid\": 49,\"user_id\": 49,\"user_id_list\": [12,23,34],\"attach_data\": \"fqwef\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_UsersInfoReq, inParam);
	inParam = "{\"sid\": 1,\"cid\": 50,\"user_id\": 49,\"latest_update_time\": 32121423,\"user_list\": [{\"user_nickname\": \"qq\",\"user_gender\": 1,\"user_id\": 1,\"user_birthday\": \"1991-09-09\",\"user_headlink\": \"www.baidu.com\",\"user_level\": 1,\"user_status\": 2,\"user_uid\": 100231,\"user_phone\": \"18588257680\",\"friend_groupid\": 1,\"friend_remark\": \"2132dwqdewf\",\"friend_status\": 1,\"user_type\": 1,\"user_ischeck\": 1,\"user_desc\": \"1450408647\"},{\"user_nickname\": \"qq\",\"user_gender\": 1,\"user_birthday\": \"1991-09-09\",\"user_headlink\": \"www.baidu.com\",\"user_level\": 1,\"user_status\": 2,\"user_uid\": 100231,\"user_phone\": \"18588257680\",\"friend_groupid\": 1,\"friend_remark\": \"2132dwqdewf\",\"friend_status\": 1,\"user_type\": 1,\"user_id\": 1,\"user_ischeck\": 1,\"user_desc\": \"1450408647\"}], \"attach_data\": \"fqwef\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_UsersInfoRsp, inParam);  //alluserrsp
	inParam = "{\"sid\": 1,\"cid\": 51,\"user_id\": 49,\"result_code\": 1,\"session_type\": 1,\"session_id\": 1,\"attach_data\": \"fqwef\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_RemoveSessionReq, inParam);
	inParam = "{\"sid\": 1,\"cid\": 52,\"user_id\": 49,\"result_code\": 1,\"session_type\": 1,\"session_id\": 1,\"attach_data\": \"fqwef\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_RemoveSessionRsp, inParam); 
	inParam = "{\"sid\": 1,\"cid\": 53,\"user_id\": 49,\"latest_update_time\": 32121423, \"user_list\":[{\"user_nickname\": \"qq\",\"user_gender\": 1,\"user_id\": 1,\"user_birthday\": \"1991-09-09\",\"user_headlink\": \"www.baidu.com\",\"user_level\": 1,\"user_status\": 2,\"user_uid\": 100231,\"user_phone\": \"18588257680\",\"friend_groupid\": 1,\"friend_remark\": \"2132dwqdewf\",\"friend_status\": 1,\"user_type\": 1,\"user_ischeck\": 1,\"user_desc\": \"1450408647\"},{\"user_nickname\": \"qq\",\"user_gender\": 1,\"user_id\": 1,\"user_birthday\": \"1991-09-09\",\"user_headlink\": \"www.baidu.com\",\"user_level\": 1,\"user_status\": 2,\"user_uid\": 100231,\"user_phone\": \"18588257680\",\"friend_groupid\": 1,\"friend_remark\": \"2132dwqdewf\",\"friend_status\": 1,\"user_type\": 1,\"user_id\": 1,\"user_ischeck\": 1,\"user_desc\": \"1450408647\"}], \"attach_data\": \"fqwef\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_AllUserReq, inParam);
	inParam = "{\"sid\": 1,\"cid\": 54,\"user_id\": 49,\"latest_update_time\": 32121423,\"user_list\": [{\"user_nickname\": \"qq\",\"user_gender\": 1,\"user_id\": 1,\"user_birthday\": \"1991-09-09\",\"user_headlink\": \"www.baidu.com\",\"user_level\": 1,\"user_status\": 2,\"user_uid\": 100231,\"user_phone\": \"18588257680\",\"friend_groupid\": 1,\"friend_remark\": \"2132dwqdewf\",\"friend_status\": 1,\"user_type\": 1,\"user_ischeck\": 1,\"user_desc\": \"1450408647\"},{\"user_nickname\": \"qq\",\"user_gender\": 1,\"user_id\": 1,\"user_birthday\": \"1991-09-09\",\"user_headlink\": \"www.baidu.com\",\"user_level\": 1,\"user_status\": 2,\"user_uid\": 100231,\"user_phone\": \"18588257680\",\"friend_groupid\": 1,\"friend_remark\": \"2132dwqdewf\",\"friend_status\": 1,\"user_type\": 1,\"user_ischeck\": 1,\"user_desc\": \"1450408647\"}], \"attach_data\": \"fqwef\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_AllUserRsp, inParam);
	inParam = "{\"sid\": 1,\"cid\": 55,\"user_id\": 49,\"user_id_list\": [12,23,34],\"attach_data\": \"fqwef\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_UsersStatReq, inParam);
	inParam = "{\"sid\": 1,\"cid\": 56,\"user_id\": 49,\"user_stat_list\": [{\"user_id\": 100001,\"status\": 1,\"client_type\": 2}, {\"user_id\": 102001,\"status\": 1,\"client_type\": 2}],\"attach_data\": \"fqwef\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_UsersStatRsp, inParam);
	inParam = "{\"sid\": 1,\"cid\": 57,\"user_id\": 49,\"login_stat\": 1}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_PCLoginStatusNotify, inParam);
	inParam = "{\"sid\": 1,\"cid\": 58,\"user_id\": 49,\"session_type\": 1,\"session_id\": 1}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_RemoveSessionNotify, inParam);
	inParam = "{\"sid\": 1,\"cid\": 59,\"user_id\": 49,\"latest_update_time\": 2133321,\"dept_list\": [{\"group_id\": 1,\"group_flag\": 60,\"group_name\": \"49\",\"group_sort\": 1}],\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_DepartmentReq, inParam);
	inParam = "{\"sid\": 1,\"cid\": 60,\"user_id\": 49,\"latest_update_time\": 2133321,\"dept_list\": [{\"group_id\": 1,\"group_flag\": 60,\"group_name\": \"49\",\"group_sort\": 1}],\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_DepartmentRsp, inParam);
	inParam = "{\"sid\": 1,\"cid\": 61,\"from_user_id\": 49,\"to_user_id\": 2133321,\"friend_groupid\": 1,\"friend_remark\": \"dqwd\",\"extra_info\": \"qqqqq\",\"user_nickname\": \"qq\",\"user_headlink\": \"dwefewqrfeqf\",\"user_gender\": 1,\"user_uid\": 100231,\"attach_data\": \"dqwefdqweffewrgt\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_AddFriendReq, inParam);
	inParam = "{\"sid\": 1,\"cid\": 62,\"user_id\": 49,\"result_code\": 1,\"friend_id\": 100001,\"friendres_status_type\": 1,\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_AddFriendRsp, inParam);  //IMCommonOperFriendRes
	inParam = "{\"sid\": 1,\"cid\": 63,\"from_user_id\": 49,\"to_user_id\": 1,\"friend_groupid\": 1,\"friendres_status_type\": 1,\"friend_remark\": \"dqwefqwe\",\"refuse_reason\": \"dqwefqwe\",\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_ReverseAddFriendReq, inParam);
	inParam = "{\"sid\": 1,\"cid\": 64,\"user_id\": 49,\"result_code\": 1,\"friend_id\": 100001,\"friendres_status_type\": 1,\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_ReverseAddFriendRsp, inParam);
	inParam = "{\"sid\": 1,\"cid\": 65,\"user_id\": 49,\"result_code\": 1,\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_DelFriendReq, inParam); //IMCommonOperFriendGroupRes
	inParam = "{\"sid\": 1,\"cid\": 66,\"user_id\": 49,\"result_code\": 1,\"friend_id\": 100001,\"friendres_status_type\": 1,\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_DelFriendRsp, inParam);
	inParam = "{\"sid\": 1,\"cid\": 67,\"user_id\": 49,\"friend_id\": 1,\"friend_nick\": \"dqwefqwef\",\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_ChgFiendRemarkReq, inParam);
	inParam = "{\"sid\": 1,\"cid\": 68,\"user_id\": 49,\"result_code\": 1,\"friend_id\": 100001,\"friendres_status_type\": 1,\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_ChgFiendRemarkRsp, inParam);
	inParam = "{\"sid\": 1,\"cid\": 69,\"user_id\": 49,\"group_name\": \"hehe\",\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_CreateFiendGroupReq, inParam);
	inParam = "{\"sid\": 1,\"cid\": 70,\"user_id\": 49,\"result_code\": 1,\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_CreateFiendGroupRsp, inParam);
	inParam = "{\"sid\": 1,\"cid\": 71,\"user_id\": 49,\"result_code\": 1,\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_DelFiendGroupReq, inParam);
	inParam = "{\"sid\": 1,\"cid\": 72,\"user_id\": 49,\"result_code\": 1,\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_DelFiendGroupRsp, inParam);
	inParam = "{\"sid\": 1,\"cid\": 73,\"user_id\": 49,\"group_id\": 1,\"friend_id_list\": [12,21,23],\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_MoveFiendGroupReq, inParam);
	inParam = "{\"sid\": 1,\"cid\": 74,\"user_id\": 49,\"result_code\": 1,\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_MoveFiendGroupRsp, inParam);
	inParam = "{\"sid\": 1,\"cid\": 75,\"user_id\": 49,\"friend_id\": 1,\"friend_nick\": \"dqwefqwef\",\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_ChgFiendGroupNameReq, inParam);
	inParam = "{\"sid\": 1,\"cid\": 76,\"user_id\": 49,\"result_code\": 1,\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_ChgFiendGroupNameRsp, inParam);
	inParam = "{\"sid\": 1,\"cid\": 77,\"from_user_id\": 49,\"to_user_id\": 1,\"friendres_status_type\": 1,\"user_nickname\": \"dqwefdqwe\",\"user_headlink\": \"dqwefqwe\",\"user_gender\": 1,\"user_uid\": 1,\"refuse_reason\": \"fqwefqwef\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_FiendNotifyReq, inParam);
	inParam = "{\"sid\": 1,\"cid\": 78,\"from_user_id\": 49,\"to_user_id\": 1}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_FiendNotifyRsp, inParam);
	inParam = "{\"sid\": 1,\"cid\": 79,\"user_id\": 49,\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_GetAddFriendReq, inParam);
	inParam = "{\"sid\": 1,\"cid\": 80,\"user_id\": 49,\"addfriend_info_list\": [{\"oper_user_id\": 100231,\"oper_time\": 1450408647,\"extra_info\": \"dqwef\",\"user_nickname\": \"rdqwerf\",\"user_headlink\": \"www.baidu.com\",\"user_gender\": 1,\"user_uid\": 1000001}],\"agree_info_list\": [{\"oper_user_id\": 100231,\"oper_time\": 1450408647,\"extra_info\": \"dqwef\",\"user_nickname\": \"rdqwerf\",\"user_headlink\": \"www.baidu.com\",\"user_gender\": 1,\"user_uid\": 1000001}],\"refuse_info_list\": [{\"oper_user_id\": 100231,\"oper_time\": 1450408647,\"extra_info\": \"dqwef\",\"user_nickname\": \"rdqwerf\",\"user_headlink\": \"www.baidu.com\",\"user_gender\": 1,\"user_uid\": 1000001}],\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_GetAddFriendRsp, inParam);
	inParam = "{\"sid\": 1,\"cid\": 81,\"user_id\": 49,\"find_string\": \"dqwefqwe\",\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_FindUserInfoReq, inParam);
	inParam = "{\"sid\": 1,\"cid\": 82,\"user_id\": 49,\"latest_update_time\": 32121423,\"user_list\": [{\"user_nickname\": \"qq\",\"user_id\":1000001, \"user_gender\": 1,\"user_birthday\": \"1991-09-09\",\"user_headlink\": \"www.baidu.com\",\"user_level\": 1,\"user_status\": 2,\"user_uid\": 100231,\"user_phone\": \"18588257680\",\"friend_groupid\": 1,\"friend_remark\": \"2132dwqdewf\",\"friend_status\": 1,\"user_type\": 1,\"user_ischeck\": 1,\"user_desc\": \"1450408647\"},{\"user_nickname\": \"qq\",\"user_id\":1000001, \"user_gender\": 1,\"user_birthday\": \"1991-09-09\",\"user_headlink\": \"www.baidu.com\",\"user_level\": 1,\"user_status\": 2,\"user_uid\": 100231,\"user_phone\": \"18588257680\",\"friend_groupid\": 1,\"friend_remark\": \"2132dwqdewf\",\"friend_status\": 1,\"user_type\": 1,\"user_ischeck\": 1,\"user_desc\": \"1450408647\"}], \"attach_data\": \"fqwef\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_FindUserInfoRsp, inParam);
	inParam = "{\"sid\": 1,\"cid\": 83,\"user_id\": 49,\"result_code\": 1,\"friend_id\": 100001,\"friendres_status_type\": 1,\"attach_data\": \"dqwefqwe\"}";
	TestPb(IM_BUDDY_LIST, IM_Buddy_DelFriendNotify, inParam);
}

void TestFile()
{
	string inParam = "{\"sid\": 3,\"cid\": 23,\"user_id\": 1000020, \"task_id\": \"265\",\"file_role\": 1}";
	TestPb(IM_File, IM_File_Login_Req, inParam);
	inParam = "{\"sid\": 3,\"cid\": 24,\"result_code\": 1000020, \"task_id\": \"265\"}";
	TestPb(IM_File, IM_File_Login_Rsp, inParam);
	inParam = "{\"sid\": 3,\"cid\": 25,\"state\": 1, \"task_id\": \"265\", \"user_id\": 100020}";
	TestPb(IM_File, IM_File_State, inParam);
	inParam = "{\"sid\": 3,\"cid\": 26,\"task_id\":  \"265\", \"user_id\": 265, \"trans_mode\": 1, \"offset\": 100020, \"data_size\": 123}";
	TestPb(IM_File, IM_File_Pull_Data_Req, inParam);
	inParam = "{\"sid\": 3,\"cid\": 27,\"task_id\": \"265\", \"user_id\": 265, \"result_code\": 1, \"offset\": 100020, \"file_data\": \"fqwefqewf\"}";
	TestPb(IM_File, IM_File_Pull_Data_Rsp, inParam);
	inParam = "{\"sid\": 3,\"cid\": 28,\"from_user_id\": 1, \"to_user_id\": 265, \"file_name\": \"deqwfwe\", \"file_size\": 100020, \"trans_mode\": 1}";
	TestPb(IM_File, IM_File_Request, inParam);
	inParam = "{\"sid\": 3,\"cid\": 29,\"from_user_id\": 1, \"to_user_id\": 265, \"file_name\": \"deqwfwe\", \"result_code\": 1, \"task_id\": \"265\", \"trans_mode\": 1, \"ip_addr_list\":[{\"ip\": \"100.101.102.103\",\"port\": 26},{\"ip\": \"100.101.102.103\",\"port\": 27},{\"ip\": \"100.101.102.103\",\"port\": 28}]}";
	TestPb(IM_File, IM_File_Response, inParam);
	inParam = "{\"sid\": 3,\"cid\": 30,\"from_user_id\": 1, \"to_user_id\": 265, \"file_name\": \"deqwfwe\", \"file_size\": 100020, \"task_id\": \"265\", \"trans_mode\": 1, \"offline_ready\": 0, \"ip_addr_list\":[{\"ip\": \"100.101.102.103\",\"port\": 26},{\"ip\": \"100.101.102.103\",\"port\": 27},{\"ip\": \"100.101.102.103\",\"port\": 28}]}";
	TestPb(IM_File, IM_File_Notify, inParam);
	inParam = "{\"sid\": 3,\"cid\": 31,\"user_id\": 1, \"offline_file_list\": [{\"from_user_id\": 1,\"file_name\": \"deqwfwe\", \"file_size\": 100020, \"task_id\": \"265\",\"ip_addr_list\":[{\"ip\": \"100.101.102.103\",\"port\": 26},{\"ip\": \"100.101.102.103\",\"port\": 27},{\"ip\": \"100.101.102.103\",\"port\": 28}],\"send_time\": 14235432},{\"from_user_id\": 1,\"file_name\": \"deqwfwe\", \"file_size\": 100020, \"task_id\": \"265\",\"ip_addr_list\":[{\"ip\": \"100.101.102.103\",\"port\": 26},{\"ip\": \"100.101.102.103\",\"port\": 27},{\"ip\": \"100.101.102.103\",\"port\": 28}],\"send_time\": 14235432}], \"attach_data\": \"deqwfwe\"}";
	TestPb(IM_File, IM_File_Has_Offline_Req, inParam);
	inParam = "{\"sid\": 3,\"cid\": 32,\"user_id\": 1, \"offline_file_list\": [{\"from_user_id\": 1,\"file_name\": \"deqwfwe\", \"file_size\": 100020, \"task_id\": \"265\",\"ip_addr_list\":[{\"ip\": \"100.101.102.103\",\"port\": 26},{\"ip\": \"100.101.102.103\",\"port\": 27},{\"ip\": \"100.101.102.103\",\"port\": 28}],\"send_time\": 14235432},{\"from_user_id\": 1,\"file_name\": \"deqwfwe\", \"file_size\": 100020, \"task_id\": \"265\",\"ip_addr_list\":[{\"ip\": \"100.101.102.103\",\"port\": 26},{\"ip\": \"100.101.102.103\",\"port\": 27},{\"ip\": \"100.101.102.103\",\"port\": 28}],\"send_time\": 14235432}], \"attach_data\": \"deqwfwe\"}";
	TestPb(IM_File, IM_File_Has_Offline_Rsp, inParam);
	inParam = "{\"sid\": 3,\"cid\": 33,\"from_user_id\": 1, \"to_user_id\": 265, \"file_name\": \"deqwfwe\", \"file_size\": 100020, \"task_id\": \"265\",\"ip_addr_list\":[{\"ip\": \"100.101.102.103\",\"port\": 26},{\"ip\": \"100.101.102.103\",\"port\": 27},{\"ip\": \"100.101.102.103\",\"port\": 28}]}";
	TestPb(IM_File, IM_File_Add_Offline_Req, inParam);
	inParam = "{\"sid\": 3,\"cid\": 34,\"from_user_id\": 1, \"to_user_id\": 265, \"task_id\": \"265\"}";
	TestPb(IM_File, IM_File_Del_Offline_Req, inParam);
}

string ToHexString(unsigned char* bytes, int len)
{
	char hexDigits[] = "0123456789ABCDEF";
	char* chars = new char[len * 2];
	for (int i = 0; i < len; i++)
	{
		int b = bytes[i];//十六进制转化为十进制 0x34->52
		chars[i * 2] = hexDigits[b >> 4];
		chars[i * 2 + 1] = hexDigits[b & 0xF];
	}
	string s = string(chars);

	delete chars;

	return s;
}

void TestPb(IMMessageSID sid, IMMessageCID cid, string inParam)
{
	cout << "\n\nBegin TestPb--------------------------------------\n";
	Json::Reader jsReader(Json::Features::strictMode());
	Json::Value jsInParam;
	if (!jsReader.parse(inParam, jsInParam))
	{
		cout << "\nerror_parsejson";
		return;
	}
	Json::FastWriter jsWriter;
	inParam = jsWriter.write(jsInParam);
	cout << "\n\ninParam:" << inParam ;

	//jsInParam["jstr"] = inParam;
	//inParam = jsWriter.write(jsInParam);
	//cout << "\n\ninParam:" << inParam;

	unsigned char* szOutParam = new unsigned char[1024 * 4];
	int nOutLen = 1024 * 4;
	int nSeqNo = 123456;
	int tSeqNo;

	int nRet = IMReq(sid, cid, inParam, szOutParam, nOutLen);

	cout << szOutParam << endl;

	if (nRet<0)
	{
		cout << "\nerror_IMReq:" << nRet << endl;
		return;
	}
	cout <<"\nIMReq:" << nRet;

	cout <<"\nHex:" << ToHexString(szOutParam, nOutLen);
	cout << "\nLen:"<< nOutLen;

	FILE* fp = NULL;

	if (fp = fopen("out.data", "w"))
	{
		fwrite(szOutParam, nOutLen, 1, fp);
		fclose(fp);
	}

	string OutParam;
	cout << "=======" << sizeof(szOutParam) << endl;
	nRet = IMRsp(szOutParam, nOutLen, OutParam, tSeqNo);
	
	if (nRet < 0)
	{
		cout << "\nerror_IMRsp:" << nRet;
		return;
	}
	cout <<"\nIMRsp:"<< nRet;
	cout <<"\nLen:"<< nOutLen;
	cout <<"\nOutParam:"<< OutParam << endl;
	cout << "tSqeNO===" << tSeqNo << endl;

	if (inParam != OutParam)
	{
		cout << "\nerror_Req<>Rsp";
	}

	delete[] szOutParam;
	szOutParam = NULL;
	cout << "\nEnd TestPb---------------------------------------------\n";
}

void TestCrypto(string strMsgData)
{
	cout << "\n\nBegin TestCrypto\n";
	char * pMsgData = NULL;
	uint32_t nMsgLen = 0;

	int retCode = EncryptMsg(strMsgData.c_str(), strMsgData.length(), &pMsgData, nMsgLen);

	cout <<"msg:"<<strMsgData<<"\nencrpt_msg:"<< pMsgData << endl <<"encrpt_len:"<< nMsgLen << endl;

	string strMsg = "";
	//DecryptMsg
	char * pOutData = NULL;
	uint32_t nOutLen0 = 0;
	retCode = DecryptMsg(pMsgData, nMsgLen, &pOutData, nOutLen0);
	if (retCode == 0 && nOutLen0 > 0 && pOutData != 0)
	{
		strMsg = std::string(pOutData, nOutLen0);
		cout <<"decrypt:"<< strMsg << endl <<"decrpt_len:"<< nOutLen0 << endl;
		Free(pOutData);
		pOutData = NULL;
	}

	Free(pMsgData);
	pMsgData = NULL;
	cout << "End TestCrypto\n";
}

void TestPass(string strPass)
{
	cout << "\n\nBegin TestPass\n";
	char * pMsgData = NULL;
	uint32_t nMsgLen = 0;
	EncryptPass(strPass.c_str(), strPass.length(), &pMsgData, nMsgLen);
	cout << "pass:" << strPass <<"\nencrypt_pass:"<< pMsgData << endl <<"encrypt_len:"<< nMsgLen << endl;
	Free(pMsgData);
	pMsgData = NULL;
	cout << "End TestPass\n";
}