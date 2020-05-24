#include "pch.h"
#include "CClientSocket.h"



CClientSocket::CClientSocket(void)
{
}


CClientSocket::~CClientSocket(void)
{
}


void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	TRACE("Current position : %s \n", &__FUNCTION__);
	if (nErrorCode == 0)
	{
		char m_StringToReceive[1024];
		int length = Receive(m_StringToReceive, sizeof(m_StringToReceive), 0);
		m_StringToReceive[length] = '\0';
		TRACE("Receive from server : %s \n", m_StringToReceive);

		string m_receive_string = m_StringToReceive;
		vector<string> resultVec = split(m_receive_string, "/");

		m_semantic_prising = new SemanticPrsing();
		int flag = m_semantic_prising->receivingOrder(resultVec);

		for (size_t i = 0; i < resultVec.size(); i++)
		{
			TRACE("Receive split : %s \n", resultVec[i].c_str());
		}

		resultReduction(resultVec, flag);

	}

	CAsyncSocket::OnReceive(nErrorCode);
}


void CClientSocket::OnClose(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CAsyncSocket::OnClose(nErrorCode);
}


void CClientSocket::OnConnect(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类

	CAsyncSocket::OnConnect(nErrorCode);
}

vector<string> CClientSocket::split(const string &str, const string &pattern)
{
	//const char* convert to char*
	char * strc = new char[strlen(str.c_str()) + 1];
	strcpy_s(strc, strlen(str.c_str()) + 1, str.c_str());
	vector<string> resultVec;
	char *buf;
	char* tmpStr = strtok_s(strc, pattern.c_str(), &buf);
	while (tmpStr != NULL)
	{
		resultVec.push_back(string(tmpStr));
		tmpStr = strtok_s(NULL, pattern.c_str(), &buf);
	}

	delete[] strc;

	return resultVec;
}

void CClientSocket::resultReduction(vector<string> resultVector, int resultFlag) {
	switch (resultFlag)
	{
	case 1:
	{
		AfxMessageBox(_T(resultVector[0].c_str()));
		ChatConsoleDlg* chatConsole = new ChatConsoleDlg;
		chatConsole->Create(IDD_CHAT_CONSOLE);
		chatConsole->ShowWindow(SW_SHOW);

		m_list_friends = &(chatConsole->m_list_friends);
		m_list_dialog = &(chatConsole->m_list_dialog);
		m_list_new_friend = &(chatConsole->m_list_new_friend);
		//m_combobox_query_friend = &(chatConsole->m_combobox_query_friend);

		chatConsole->clientName = *clientName;
		chatConsole->clientSocket = this;

		char m_sendBuf[1024];   //初始化缓冲区
		strcpy_s(m_sendBuf, "Client send/");
		CString editMSG = _T("ListInit/");
		strcat_s(m_sendBuf, editMSG);
		strcat_s(m_sendBuf, (*clientName).c_str());
		Send(m_sendBuf, strlen(m_sendBuf));

		break;
	}
	case 2:
	{
		AfxMessageBox(_T(resultVector[0].c_str()));
		break;
	}
	case 3:
	{
		AfxMessageBox(_T(resultVector[0].c_str()));
		break;
	}
	case 5:
	{
		if (resultVector.size() < 3)
		{
			break;
		}
		string friendListString = resultVector[2];
		vector<string> friendVec = split(friendListString, "-");
		for (size_t i = 0; i < friendVec.size(); i++)
		{
			TRACE("friend split : %s \n", friendVec[i].c_str());
			m_list_friends->AddString(friendVec[i].c_str());
		}
		break;
	}
	case 6:
	{
		string returnMSG = resultVector[2];
		if (returnMSG.compare("Failed") == 0)
		{
			AfxMessageBox(_T("您的好友已下线！"));
		}
		TRACE("MSG Return : %s \n", returnMSG.c_str());
		break;
	}
	case 7:
	{
		string fromName = resultVector[2];
		string MSG = resultVector[4];
		string sysTime = resultVector[5];

		m_list_dialog->AddString("");
		m_list_dialog->AddString(fromName.c_str());
		m_list_dialog->AddString(MSG.c_str());
		m_list_dialog->AddString(sysTime.c_str());
		m_list_dialog->AddString("");
		break;
	}
	case 8:
	{
		if (resultVector.size() < 3)
		{
			break;
		}
		string friendRequestListString = resultVector[2];
		vector<string> friendRequestVec = split(friendRequestListString, "-");
		for (size_t i = 0; i < friendRequestVec.size(); i++)
		{
			TRACE("friend split : %s \n", friendRequestVec[i].c_str());
			m_list_new_friend->AddString(friendRequestVec[i].c_str());
		}
		break;
	}
	case 9:
	{

		TRACE("Client Refetch List ！\n");

		m_list_friends->ResetContent();
		m_list_new_friend->ResetContent();

		char m_sendBuf[1024];   //初始化缓冲区
		strcpy_s(m_sendBuf, "Client send/");
		CString editMSG = _T("ListInit/");
		strcat_s(m_sendBuf, editMSG);
		strcat_s(m_sendBuf, (*clientName).c_str());

		Send(m_sendBuf, strlen(m_sendBuf));

		break;
	}
	case 10:
	{
		AfxMessageBox(_T(resultVector[0].c_str()));
		break;
	}
	case 11:
	{
		AfxMessageBox(_T(resultVector[0].c_str()));
		break;
	}
	default:
		break;
	}
}