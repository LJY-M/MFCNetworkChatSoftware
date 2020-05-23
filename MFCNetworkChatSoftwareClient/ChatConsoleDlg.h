#pragma once
//#include <iostream>
#include <string>

//#include "CClientSocket.h"

class CClientSocket;

using namespace std;

// ChatConsoleDlg 对话框

class ChatConsoleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ChatConsoleDlg)

public:
	ChatConsoleDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ChatConsoleDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHAT_CONSOLE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	// 当前好友列表
	CListBox m_list_friends;
	// 对话框窗口，显示信息用
	CListBox m_list_dialog;
	// 好友申请列表
	CListBox m_list_new_friend;
	// 查询用户下拉框
	CComboBox m_combobox_query_friend;

	string clientName;

	CClientSocket * clientSocket;


	afx_msg void OnClickedButtonSendMsg();
	// 信息发送栏
	CString m_edit_send_msg;
};
