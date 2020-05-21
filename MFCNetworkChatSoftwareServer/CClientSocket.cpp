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

		//char szBuf[1024] = { 0 };
		//INT nReceiveCounts = Receive((VOID*)szBuf, 1024);
		//if (m_ListBox != NULL)
		//	m_ListBox->AddString((LPCTSTR)szBuf);

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