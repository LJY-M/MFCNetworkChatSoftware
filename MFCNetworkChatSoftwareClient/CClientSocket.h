#pragma once
#include <afxsock.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>

#include "SemanticPrsing.h"
#include "resource.h"
#include "ChatConsoleDlg.h"

//class ChatConsoleDlg;

using namespace std;

class CClientSocket :
	public CAsyncSocket
{
public:
	CClientSocket(void);
	virtual ~CClientSocket(void);

	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);

	void SetListBox(CListBox * ListBox) { m_ListBox = ListBox; }
	CListBox * m_ListBox;

	vector<string> split(const string &str, const string &pattern);

	SemanticPrsing* m_semantic_prising;

	void resultReduction(vector<string> resultVector, int resultFlag);

	string* clientName;

	// 当前好友列表
	CListBox* m_list_friends;
	// 对话框窗口，显示信息用
	CListBox* m_list_dialog;
	// 好友申请列表
	CListBox* m_list_new_friend;
	// 查询用户下拉框
	CComboBox* m_combobox_query_friend;
};

