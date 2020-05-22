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
};

