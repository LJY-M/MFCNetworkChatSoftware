#include "pch.h"
#include "CClientSocket.h"


// CClientSocket


CClientSocket::CClientSocket()
{
	//m_ListBox = NULL;
}

CClientSocket::~CClientSocket()
{

}

void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	TRACE("Current position : %s \n", &__FUNCTION__);
	if (nErrorCode == 0)
	{
		char m_StringToReceive[1024];
		int length = Receive(m_StringToReceive, sizeof(m_StringToReceive), 0);
		m_StringToReceive[length] = '\0';
		TRACE("Receive from client : %s \n", m_StringToReceive);

		string m_receive_string = m_StringToReceive;
		vector<string> resultVec = split(m_receive_string,"/");

		m_semantic_prising = new SemanticPrsing();
		int flag = m_semantic_prising->receivingOrder(m_sql_operator, resultVec);

		for (size_t i = 0; i<resultVec.size(); i++)
		{
			TRACE("Receive split : %s \n", resultVec[i].c_str());
		}

		CString SocketName;
		UINT len = 100;
		GetSockName(SocketName, len);
		char addString[1024] = "Client "; 
		strcat_s(addString, SocketName.GetBuffer(0));
		strcat_s(addString, " : ");
		strcat_s(addString, m_StringToReceive);

		m_ListBox->AddString(addString);

		resultReduction(resultVec, flag);

		//if (flag == 1)
		//{
		//	char addLoginString[1024] = "User ";
		//	strcat_s(addLoginString, resultVec[2].c_str());
		//	strcat_s(addLoginString, " Login Successfully ! ");

		//	m_ListBox->AddString(addLoginString);
		//}

	}

	CAsyncSocket::OnReceive(nErrorCode);
}


void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	TRACE("Current position : %s \n", &__FUNCTION__);
	Close();
	AfxMessageBox(_T("断开"));

	CAsyncSocket::OnClose(nErrorCode);
}

vector<string> CClientSocket::split(const string &str, const string &pattern)
{
	//const char* convert to char*
	char * strc = new char[strlen(str.c_str()) + 1];
	strcpy_s(strc,strlen(str.c_str())+1 ,str.c_str());
	vector<string> resultVec;
	char *buf;
	char* tmpStr = strtok_s(strc, pattern.c_str(), &buf);
	while (tmpStr != NULL)
	{
		resultVec.push_back(string(tmpStr));
		tmpStr = strtok_s(NULL, pattern.c_str(), &buf);
	}

	delete[] strc;

	return resultVec;
}

void CClientSocket::resultReduction(vector<string> resultVector, int resultFlag)
{
	// TODO: 在此处添加实现代码.
	switch (resultFlag)
	{
	case 1:
	{
		char addLogin1String[1024] = "User ";
		strcat_s(addLogin1String, resultVector[2].c_str());
		strcat_s(addLogin1String, " Login Successfully !/1");

		m_ListBox->AddString(addLogin1String);

		Send(addLogin1String, strlen(addLogin1String));
		break;
	}
	case 2:
	{
		char addLogin2String[1024] = "User ";
		strcat_s(addLogin2String, resultVector[2].c_str());
		strcat_s(addLogin2String, " Wrong Password !/2");

		m_ListBox->AddString(addLogin2String);

		Send(addLogin2String, strlen(addLogin2String));
		break;
	}
	case 3: 
	{
		char addLogin3String[1024] = "User ";
		strcat_s(addLogin3String, resultVector[2].c_str());
		strcat_s(addLogin3String, " Repeat Login !/3");

		m_ListBox->AddString(addLogin3String);

		Send(addLogin3String, strlen(addLogin3String));
		break;
	}
	default:
		break;
	}
}
