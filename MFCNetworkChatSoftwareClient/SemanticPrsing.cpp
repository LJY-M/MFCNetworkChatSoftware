#include "pch.h"
#include "SemanticPrsing.h"

int SemanticPrsing::receivingOrder(vector<string> receivingOrderVector) {

	int flag = 0;//0:失败；1：登陆成功；2:密码错误；3：多地登录

	for (size_t i = 0; i < receivingOrderVector.size(); i++)
	{
		TRACE("Receive split : %s \n", receivingOrderVector[i].c_str());
	}

	flag = atoi(receivingOrderVector[1].c_str());

	return flag;
}