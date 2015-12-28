
#ifndef _SWITCHSERVICE_H_
#define _SWITCHSERVICE_H_


#include "IM.SwitchService.pb.h"

#include "imdefine.h"
using namespace IM::IMPB;

#include <string>
#include "json/json.h"
#include "ImPduBase.h"
#include <sstream>

using namespace std;

class CIMSwitchService
{
public:
	CIMSwitchService();
	~CIMSwitchService();

	static int HandleSID_SwitchService_Send(IMMessageCID cid, const Json::Value& jsInParam, unsigned char* OutParam, int& outLen);
	static int HandleSID_SwitchService_Receive(CImPdu* pPdu, string& OutParam);

private:
	static int EncodeP2PCmdMsg(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeP2PCmdMsg(CImPdu* pPdu, string& OutParam);

};

#endif
