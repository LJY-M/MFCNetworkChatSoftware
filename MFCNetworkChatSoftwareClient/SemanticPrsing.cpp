#include "pch.h"
#include "SemanticPrsing.h"

int SemanticPrsing::receivingOrder(vector<string> receivingOrderVector) {

	int flag = 0;//0:ʧ�ܣ�1����½�ɹ���2:�������3����ص�¼

	for (size_t i = 0; i < receivingOrderVector.size(); i++)
	{
		TRACE("Receive split : %s \n", receivingOrderVector[i].c_str());
	}

	flag = atoi(receivingOrderVector[1].c_str());

	return flag;
}