// ChatConsoleDlg.cpp: 实现文件
//

#include "pch.h"
#include "MFCNetworkChatSoftwareClient.h"
#include "ChatConsoleDlg.h"
#include "afxdialogex.h"

#include "CClientSocket.h"


// ChatConsoleDlg 对话框

IMPLEMENT_DYNAMIC(ChatConsoleDlg, CDialogEx)

ChatConsoleDlg::ChatConsoleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHAT_CONSOLE, pParent)
	, m_edit_send_msg(_T(""))
	, m_edit_friend_name(_T(""))
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
	DDX_Text(pDX, IDC_EDIT_SEND_MESSAGE, m_edit_send_msg);
	DDX_Text(pDX, IDC_EDIT_FRIEND_NAME, m_edit_friend_name);
}


BEGIN_MESSAGE_MAP(ChatConsoleDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SEND_MSG, &ChatConsoleDlg::OnClickedButtonSendMsg)
	ON_BN_CLICKED(IDC_BUTTON_SEND_APP, &ChatConsoleDlg::OnClickedButtonSendApp)
	ON_BN_CLICKED(IDC_BUTTON_ACCEPT_APP, &ChatConsoleDlg::OnClickedButtonAcceptApp)
END_MESSAGE_MAP()


// ChatConsoleDlg 消息处理程序


void ChatConsoleDlg::OnClickedButtonSendMsg()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(true);

	char systemTime[512];

	SYSTEMTIME sys;
	GetLocalTime(&sys);

	sprintf_s(systemTime, sizeof(systemTime), "%4d-%02d-%02d-%02d-%02d-%02d", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond);

	CString targetUser;
	int nCurInedx = m_list_friends.GetCurSel();
	m_list_friends.GetText(nCurInedx, targetUser);

	char m_sendBuf[2048];   //初始化缓冲区
	strcpy_s(m_sendBuf, "Client send/");
	CString editMSG = _T("SendMSG/");
	strcat_s(m_sendBuf, editMSG);
	strcat_s(m_sendBuf, clientName.c_str());
	strcat_s(m_sendBuf, "/");
	strcat_s(m_sendBuf, targetUser);
	strcat_s(m_sendBuf, "/");
	strcat_s(m_sendBuf, m_edit_send_msg);
	strcat_s(m_sendBuf, "/");
	strcat_s(m_sendBuf, systemTime);

	clientSocket->Send(m_sendBuf, strlen(m_sendBuf));

	m_list_dialog.AddString("\n");
	char m_addString[32] = "";
	strcat_s(m_addString, clientName.c_str());
	strcat_s(m_addString, " to ");
	strcat_s(m_addString, targetUser);
	strcat_s(m_addString, " : ");
	m_list_dialog.AddString(m_addString);
	m_list_dialog.AddString(m_edit_send_msg);
	m_list_dialog.AddString(systemTime);
	m_list_dialog.AddString("\n");
}

void ChatConsoleDlg::OnClickedButtonSendApp()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);

	char m_name[32];
	strcpy_s(m_name, "");
	strcat_s(m_name, m_edit_friend_name);

	char m_sendBuf[2048];   //初始化缓冲区
	strcpy_s(m_sendBuf, "Client send/");
	CString editMSG = _T("AddNewFriendSend/");
	strcat_s(m_sendBuf, editMSG);
	strcat_s(m_sendBuf, clientName.c_str());
	strcat_s(m_sendBuf, "/");
	strcat_s(m_sendBuf, m_name);

	//clientSocket->Send(m_sendBuf, strlen(m_sendBuf));
}


void ChatConsoleDlg::OnClickedButtonAcceptApp()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(true);

	CString targetUser;
	int nCurInedx = m_list_new_friend.GetCurSel();
	m_list_new_friend.GetText(nCurInedx, targetUser);

	char m_sendBuf[2048];   //初始化缓冲区
	strcpy_s(m_sendBuf, "Client send/");
	CString editMSG = _T("AddNewFriendReceive/");
	strcat_s(m_sendBuf, editMSG);
	strcat_s(m_sendBuf, clientName.c_str());
	strcat_s(m_sendBuf, "/");
	strcat_s(m_sendBuf, targetUser);

	clientSocket->Send(m_sendBuf, strlen(m_sendBuf));
}
