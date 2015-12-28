
#ifndef _OTHER_H_
#define _OTHER_H_


#include "IM.Other.pb.h"

#include "imdefine.h"
using namespace IM::IMPB;

#include <string>
#include "json/json.h"
#include "ImPduBase.h"
#include <sstream>

using namespace std;

class CIMOther
{
public:
	CIMOther();
	~CIMOther();

	static int HandleSID_Other_Send(IMMessageCID cid, const Json::Value& jsInParam, unsigned char* OutParam, int& outLen);
	static int HandleSID_Other_Receive(CImPdu* pPdu, string& OutParam);

private:
	static int EncodeHeartBeat(const Json::Value& jsInParam, unsigned char* OutParam, int& len);
	static int DecodeIMHeartBeat(CImPdu* pPdu, string& OutParam);

};

#endif
