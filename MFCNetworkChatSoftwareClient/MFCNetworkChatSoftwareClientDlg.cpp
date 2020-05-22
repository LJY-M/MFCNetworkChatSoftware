
// MFCNetworkChatSoftwareClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCNetworkChatSoftwareClient.h"
#include "MFCNetworkChatSoftwareClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCNetworkChatSoftwareClientDlg 对话框



CMFCNetworkChatSoftwareClientDlg::CMFCNetworkChatSoftwareClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCNETWORKCHATSOFTWARECLIENT_DIALOG, pParent)
	, m_edit_user_name(_T(""))
	, m_edit_password(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCNetworkChatSoftwareClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_edit_user_name);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_edit_password);
}

BEGIN_MESSAGE_MAP(CMFCNetworkChatSoftwareClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOG, &CMFCNetworkChatSoftwareClientDlg::OnClickedButtonLog)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CMFCNetworkChatSoftwareClientDlg 消息处理程序

BOOL CMFCNetworkChatSoftwareClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//ShowWindow(SW_MAXIMIZE);

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCNetworkChatSoftwareClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCNetworkChatSoftwareClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCNetworkChatSoftwareClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCNetworkChatSoftwareClientDlg::OnClickedButtonLog()
{
	// TODO: 在此添加控件通知处理程序代码
	BOOL bInit = AfxSocketInit();
	if (!bInit)
	{
		AfxMessageBox(_T("socket 初始化失败 "));
		return;
	}

	if (m_ClientSocket == NULL)
	{
		m_ClientSocket = new CClientSocket();
		m_ClientSocket->Create();
	}
	else
	{
		m_ClientSocket->Close();
		return;
	}

	CString m_IP  = _T("192.168.0.103");
	m_ClientSocket->Connect(m_IP, 10101);

	//m_ClientSocket->SetListBox(&m_ListBox);

	Sleep(5000);
	UpdateData(TRUE);

	char m_sendBuf[1024];   //消息缓冲区 
	strcpy_s(m_sendBuf, "Client send/");
	CString editMSG = _T("Login/");
	strcat_s(m_sendBuf, editMSG);
	strcat_s(m_sendBuf, m_edit_user_name);
	strcat_s(m_sendBuf, "/");
	strcat_s(m_sendBuf, m_edit_password);
	m_ClientSocket->Send(m_sendBuf, strlen(m_sendBuf));
}


void CMFCNetworkChatSoftwareClientDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (MessageBox("确定要退出程序吗？", "退出提示", MB_ICONINFORMATION | MB_YESNO) == IDNO)
		return; //注意无返回值
	//CDialog::OnClose();

	if (m_ClientSocket != NULL)
	{
		char m_sendBuf[1024];   //消息缓冲区 
		strcpy_s(m_sendBuf, "Client send/");
		CString editMSG = _T("Logout/");
		strcat_s(m_sendBuf, editMSG);
		strcat_s(m_sendBuf, m_edit_user_name);
		m_ClientSocket->Send(m_sendBuf, strlen(m_sendBuf));
	}

	CDialogEx::OnClose();
}
