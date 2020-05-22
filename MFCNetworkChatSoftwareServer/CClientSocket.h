#pragma once
#include <afxsock.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>

#include "MySQLModule.h"
#include "SemanticPrsing.h"

using namespace std;

class CClientSocket :
	public CAsyncSocket
{
public:
	CClientSocket();
	virtual ~CClientSocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	VOID SetListBox(CListBox * ListBox) { m_ListBox = ListBox; }
	CListBox * m_ListBox;

	vector<string> split(const string &str, const string &pattern);

	SemanticPrsing* m_semantic_prising;
	MySQLModule* m_sql_operator;
	void resultReduction(vector<string> resultVector, int resultFlag);
};

