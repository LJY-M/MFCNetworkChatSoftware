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

	CAsyncSocket::OnReceive(nErrorCode);
}


void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CAsyncSocket::OnClose(nErrorCode);
}
