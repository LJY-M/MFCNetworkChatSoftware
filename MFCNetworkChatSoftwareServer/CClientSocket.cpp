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
	// TODO: �ڴ����ר�ô����/����û���

	CAsyncSocket::OnReceive(nErrorCode);
}


void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CAsyncSocket::OnClose(nErrorCode);
}
