// ChatConsoleDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCNetworkChatSoftwareClient.h"
#include "ChatConsoleDlg.h"
#include "afxdialogex.h"


// ChatConsoleDlg 对话框

IMPLEMENT_DYNAMIC(ChatConsoleDlg, CDialogEx)

ChatConsoleDlg::ChatConsoleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHAT_CONSOLE, pParent)
{

}

ChatConsoleDlg::~ChatConsoleDlg()
{
}

void ChatConsoleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_FRIENDS, m_list_friends);
	DDX_Control(pDX, IDC_LIST_DIALOG, m_list_dialog);
	DDX_Control(pDX, IDC_LIST_NEW_FRIEND, m_list_new_friend);
	DDX_Control(pDX, IDC_ADD_FRIEND, m_combobox_query_friend);
}


BEGIN_MESSAGE_MAP(ChatConsoleDlg, CDialogEx)
END_MESSAGE_MAP()


// ChatConsoleDlg 消息处理程序
