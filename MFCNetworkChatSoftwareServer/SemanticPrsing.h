#pragma once
#include <afxsock.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>

#include "MySQLModule.h"

using namespace std;

class SemanticPrsing
{
public:
	SemanticPrsing() {};
	~SemanticPrsing() {};
	int receivingOrder(MySQLModule* m_sql_operator, vector<string> receivingOrderVector);

	void setClientName(string* Name) { clientName = Name; }

	string* clientName;
	int* clientId;

	char FNameList[1024];

	char FListRequest[1024];
	// 获取好友申请列表
	int GetFriendListRequest(MySQLModule* m_sql_operator, string userName);
};

