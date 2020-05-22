#pragma once


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
};
