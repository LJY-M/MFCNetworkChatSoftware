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
	CClientSocket * GetClientByIndex(int nIndex)  //返回一个已经连接的客户端用来给指定客户端发消息
	{
		return m_ClientSocketList.GetAt(m_ClientSocketList.FindIndex(nIndex));
	}
private:
	CList<CClientSocket * > m_ClientSocketList;  //这里要维护一个已经连接的客户端列表,这样服务器可以指定向哪个客户端发消息
};

