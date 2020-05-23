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
	, m_edit_send_msg(_T(""))
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
	DDX_Text(pDX, IDC_EDIT_SEND_MESSAGE, m_edit_send_msg);
}


BEGIN_MESSAGE_MAP(ChatConsoleDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEND_MSG, &ChatConsoleDlg::OnClickedButtonSendMsg)
END_MESSAGE_MAP()


// ChatConsoleDlg 消息处理程序


void ChatConsoleDlg::OnClickedButtonSendMsg()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(true);

	CString targetUser;
	int nCurInedx = m_list_friends.GetCurSel();
	m_list_friends.GetText(nCurInedx, targetUser);

	char m_sendBuf[1024];   //初始化新对话框列表
	strcpy_s(m_sendBuf, "Client send/");
	CString editMSG = _T("SendMSG/");
	strcat_s(m_sendBuf, editMSG);
	strcat_s(m_sendBuf, clientName.c_str());
	strcat_s(m_sendBuf, "/");
	strcat_s(m_sendBuf, targetUser);
	strcat_s(m_sendBuf, "/");
	strcat_s(m_sendBuf, m_edit_send_msg);
	//clientSocket->Send(m_sendBuf, strlen(m_sendBuf));
}
