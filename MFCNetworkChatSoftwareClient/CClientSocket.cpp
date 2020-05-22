#include "pch.h"
#include "CClientSocket.h"



CClientSocket::CClientSocket(void)
{
}


CClientSocket::~CClientSocket(void)
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
		vector<string> resultVec = split(m_receive_string, "/");

		m_semantic_prising = new SemanticPrsing();
		int flag = m_semantic_prising->receivingOrder(resultVec);

		for (size_t i = 0; i < resultVec.size(); i++)
		{
			TRACE("Receive split : %s \n", resultVec[i].c_str());
		}

		resultReduction(resultVec, flag);

	}

	CAsyncSocket::OnReceive(nErrorCode);
}


void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CAsyncSocket::OnClose(nErrorCode);
}


void CClientSocket::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CAsyncSocket::OnConnect(nErrorCode);
}

vector<string> CClientSocket::split(const string &str, const string &pattern)
{
	//const char* convert to char*
	char * strc = new char[strlen(str.c_str()) + 1];
	strcpy_s(strc, strlen(str.c_str()) + 1, str.c_str());
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

void CClientSocket::resultReduction(vector<string> resultVector, int resultFlag) {
	switch (resultFlag)
	{
	case 1:
	{
		AfxMessageBox(_T(resultVector[0].c_str()));
		ChatConsoleDlg* chatConsole = new ChatConsoleDlg;
		chatConsole->Create(IDD_CHAT_CONSOLE);
		chatConsole->ShowWindow(SW_SHOW);
		break;
	}
	case 2:
	{
		AfxMessageBox(_T(resultVector[0].c_str()));
		break;
	}
	case 3:
	{
		AfxMessageBox(_T(resultVector[0].c_str()));
		break;
	}
	default:
		break;
	}
}