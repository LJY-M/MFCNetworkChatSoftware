#pragma once
#include <afxsock.h>
#include "CClientSocket.h"


class CListenSocket :
	public CAsyncSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();
public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	CClientSocket * GetClientByIndex(int nIndex)  //����һ���Ѿ����ӵĿͻ���������ָ���ͻ��˷���Ϣ
	{
		return m_ClientSocketList.GetAt(m_ClientSocketList.FindIndex(nIndex));
	}
private:
	CList<CClientSocket * > m_ClientSocketList;  //����Ҫά��һ���Ѿ����ӵĿͻ����б�,��������������ָ�����ĸ��ͻ��˷���Ϣ
};

