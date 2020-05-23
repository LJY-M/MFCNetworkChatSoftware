#pragma once

#include <afxsock.h>
#include "CClientSocket.h"

#include "MySQLModule.h"



class CListenSocket :
	public CAsyncSocket
{
public:
	CListenSocket();
	virtual ~CListenSocket();
	void SetListBoxMsg(CListBox * ListBox) { m_ListBoxMsg = ListBox; }   //这个ListBox是接收客户端消息的
public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//CClientSocket * GetClientByIndex(int nIndex)
	//{  //返回一个已经连接的客户端用来给指定客户端发消息
	//	return m_ClientSocketList.GetAt(m_ClientSocketList.FindIndex(nIndex));
	//}
private:
	vector<CClientSocket * > m_ClientSocketList;  //这里要维护一个已经连接的客户端列表,这样服务器可以指定向哪个客户端发消息
	CListBox * m_ListBoxMsg;
public:
	MySQLModule* m_sql_operator;
};

