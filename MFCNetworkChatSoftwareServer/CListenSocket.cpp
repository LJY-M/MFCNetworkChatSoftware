#include "pch.h"
#include "CListenSocket.h"


// CListenSocket

CListenSocket::CListenSocket()
{
}

CListenSocket::~CListenSocket()
{
}


void CListenSocket::OnAccept(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���
	TRACE("Current position : %s \n", &__FUNCTION__);
	if (nErrorCode == 0)//����ɹ�
	{
		CClientSocket* pNewClientSocket = new CClientSocket(); //����һ���Ѿ����ӵĿͻ���
		BOOL bAccept = Accept(*pNewClientSocket);
		if (bAccept)
		{
			m_ClientSocketList.AddTail(pNewClientSocket);
			//pNewClientSocket->SetListBox(m_ListBoxMsg);
			CString SocketName;
			UINT len = 100;
			pNewClientSocket->GetSockName(SocketName, len);
			TRACE("Client  : %s request connect.\n", (LPCTSTR)SocketName);
			//m_ListBox->AddString(SocketName);           //�ͻ����б�����ʾ����Ѿ����ӵĿͻ���ip
		}
		else
		{
			DWORD dwErr = GetLastError();
			CString strErr;
			strErr.Format(_T("accept ������=%d"), dwErr);
			delete pNewClientSocket;
			AfxMessageBox(strErr);
		}
	}

	CAsyncSocket::OnAccept(nErrorCode);
}


void CListenSocket::OnClose(int nErrorCode)
{
	// TODO: �ڴ����ר�ô����/����û���

	CAsyncSocket::OnClose(nErrorCode);
}
