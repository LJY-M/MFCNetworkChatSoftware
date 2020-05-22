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
}


BEGIN_MESSAGE_MAP(ChatConsoleDlg, CDialogEx)
END_MESSAGE_MAP()


// ChatConsoleDlg 消息处理程序
