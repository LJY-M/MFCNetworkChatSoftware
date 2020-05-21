
// MFCNetworkChatSoftwareClientDlg.h: 头文件
//

#pragma once
#include "CClientSocket.h"


// CMFCNetworkChatSoftwareClientDlg 对话框
class CMFCNetworkChatSoftwareClientDlg : public CDialogEx
{
// 构造
public:
	CMFCNetworkChatSoftwareClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCNETWORKCHATSOFTWARECLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CClientSocket * m_ClientSocket;
	CListBox m_ListBox;
	afx_msg void OnClickedButtonLog();
	// 登录时输入的用户名
	CString m_edit_user_name;
	// 登录时输入的密码
	CString m_edit_password;
};
