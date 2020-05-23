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

	// ��ǰ�����б�
	CListBox* m_list_friends;
	// �Ի��򴰿ڣ���ʾ��Ϣ��
	CListBox* m_list_dialog;
	// ���������б�
	CListBox* m_list_new_friend;
	// ��ѯ�û�������
	CComboBox* m_combobox_query_friend;
};

