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
