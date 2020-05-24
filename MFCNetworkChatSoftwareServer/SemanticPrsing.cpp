#include "pch.h"
#include "SemanticPrsing.h"


int SemanticPrsing::receivingOrder(MySQLModule* m_sql_operator, vector<string> receivingOrderVector)
{
	// TODO: 在此处添加实现代码.

	int flag = 0;//0:失败；1：登录成功；2:密码错误；3：多地登录；
	//4：退出成功；5：发送好友列表；6：发送信息返回；7：发送信息；
	//8：发送好友申请列表；9：更新好友数据库：提醒客户端更新列表
	//10：用户不存在；11：已存在关系；12：请求插入成功

	for (size_t i = 0; i < receivingOrderVector.size(); i++)
	{
		TRACE("Receive split : %s \n", receivingOrderVector[i].c_str());
	}

	string orderString[] = {"Client send","Login","Logout","ListInit","SendMSG","AddNewFriendReceive","AddNewFriendSend"};

	if (receivingOrderVector[1].compare(orderString[1]) == 0)
	{
		string userName = receivingOrderVector[2];
		string password = receivingOrderVector[3];

		string sqlSelectTitle = "SELECT * FROM user_info ";
		string sqlWhereUserName = " WHERE user_name = '";
		string sqlWherePassword = "' AND password = '";
		string sqlEnd = "'";

		string sqlUpdateTitle = "UPDATE user_info ";
		string sqlUpdateState = "SET user_state = '";

		//"UPDATE user_info SET user_state='0' WHERE user_name='LJY_Mie' ";
		
		string sqlExecute = sqlSelectTitle + sqlWhereUserName + userName + sqlEnd;

		const sql::SQLString sqlString(sqlExecute.c_str());
		sql::ResultSet *res;
		res = m_sql_operator->MySQLQuery(sqlString);
		while (res->next())
		{
			TRACE("\n");
			TRACE(" SQLLoginState : %d \n", res->getInt("id"));
			TRACE(" SQLLoginState : %s \n", res->getString("user_name").c_str());
			TRACE(" SQLLoginState : %s \n", res->getString("password").c_str());
			TRACE(" SQLLoginState : %s \n", res->getString("user_state").c_str());
			TRACE("\n");

			string passwordQuery = res->getString("password").c_str();
			string userStateQuery = res->getString("user_state").c_str();
			if (password.compare(passwordQuery) == 0)
			{
				if (userStateQuery.compare("1") == 0)
				{
					flag = 3;
				}
				else if (userStateQuery.compare("0") == 0)
				{
					string sqlUpdateExecute = sqlUpdateTitle + sqlUpdateState + "1' " + sqlWhereUserName + userName + sqlEnd;
					const sql::SQLString sqlUpdateString(sqlUpdateExecute.c_str());
					m_sql_operator->MySQLUpdate(sqlUpdateString);

					int id = res->getInt("id");
					string user_name = res->getString("user_name").c_str();

					//*clientId = id;
					*clientName = user_name;

					flag = 1;
				}
			}
			else
			{
				flag = 2;
			}
		}
		delete res;
	}
	else if (receivingOrderVector[1].compare(orderString[2]) == 0)
	{
		string userName = receivingOrderVector[2];

		string sqlUpdateTitle = "UPDATE user_info ";
		string sqlWhereUserName = " WHERE user_name = '";
		string sqlUpdateState = "SET user_state = '";
		string sqlEnd = "'";

		//"UPDATE user_info SET user_state='0' WHERE user_name='LJY_Mie' ";

		string sqlUpdateExecute = sqlUpdateTitle + sqlUpdateState + "0' " + sqlWhereUserName + userName + sqlEnd;

		const sql::SQLString sqlUpdateString(sqlUpdateExecute.c_str());
		m_sql_operator->MySQLUpdate(sqlUpdateString);
		flag = 4;
	}
	else if (receivingOrderVector[1].compare(orderString[3]) == 0)
	{
		string userName = receivingOrderVector[2];

		string sqlSelectFriendListTitle = "SELECT * FROM friend_list ";
		string sqlWhereFriendA = " WHERE friend_a = '";
		string sqlWhereFriendB = " WHERE friend_b = '";
		string sqlWhereFriendRelationship = " AND friend_relationship = 'ab' ";
		string sqlEnd = "'";

		string sqlQueryAExecute = sqlSelectFriendListTitle + sqlWhereFriendA + userName + sqlEnd + sqlWhereFriendRelationship;
		string sqlQueryBExecute = sqlSelectFriendListTitle + sqlWhereFriendB + userName + sqlEnd + sqlWhereFriendRelationship;

		CList<string> frinedNameList;

		const sql::SQLString sqlAString(sqlQueryAExecute.c_str());
		sql::ResultSet *resA;
		resA = m_sql_operator->MySQLQuery(sqlAString);
		while (resA->next())
		{

			int id = resA->getInt("id");
			string friend_a = resA->getString("friend_a").c_str();
			string friend_b = resA->getString("friend_b").c_str();
			string friend_relationship = resA->getString("friend_relationship").c_str();
			TRACE("\n");
			TRACE(" SQLInitState : %d \n", id);
			TRACE(" SQLInitState : %s \n", friend_a.c_str());
			TRACE(" SQLInitState : %s \n", friend_b.c_str());
			TRACE(" SQLInitState : %s \n", friend_relationship.c_str());
			TRACE("\n");
			
			if (userName.compare(friend_a) == 0)
			{
				frinedNameList.AddTail(friend_b);
			}
			else if (userName.compare(friend_b) == 0)
			{
				frinedNameList.AddTail(friend_a);
			}
		}

		const sql::SQLString sqlBString(sqlQueryBExecute.c_str());
		sql::ResultSet *resB;
		resB = m_sql_operator->MySQLQuery(sqlBString);
		while (resB->next())
		{

			int id = resB->getInt("id");
			string friend_a = resB->getString("friend_a").c_str();
			string friend_b = resB->getString("friend_b").c_str();
			string friend_relationship = resB->getString("friend_relationship").c_str();
			TRACE("\n");
			TRACE(" SQInittate : %d \n", id);
			TRACE(" SQInittate : %s \n", friend_a.c_str());
			TRACE(" SQInittate : %s \n", friend_b.c_str());
			TRACE(" SQInittate : %s \n", friend_relationship.c_str());
			TRACE("\n");

			if (userName.compare(friend_a) == 0)
			{
				frinedNameList.AddTail(friend_b);
			}
			else if (userName.compare(friend_b) == 0)
			{
				frinedNameList.AddTail(friend_a);
			}
		}

		memset(FNameList, 0, sizeof(FNameList));
		strcpy_s(FNameList, "");
		
		POSITION pos = frinedNameList.GetHeadPosition();
		while (pos != NULL) {
			string name = frinedNameList.GetNext(pos);
			TRACE(" Friend Test : %s \n", name.c_str());
			strcat_s(FNameList, name.c_str());
			strcat_s(FNameList, "-");
		}

		TRACE(" Friend Test : %s \n", FNameList);

		flag = 5;

		GetFriendListRequest(m_sql_operator, userName);

	}
	else if (receivingOrderVector[1].compare(orderString[4]) == 0)
	{
		string formName = receivingOrderVector[2];
		string toName = receivingOrderVector[3];
		string MSG = receivingOrderVector[4];
		string sysTime = receivingOrderVector[5];

		TRACE("\n");
		TRACE(" SQLSendMSGState : %s \n", formName.c_str());
		TRACE(" SQLSendMSGState : %s \n", toName.c_str());
		TRACE(" SQLSendMSGStatee : %s \n", MSG.c_str());
		TRACE(" SQLSendMSGStatee : %s \n", sysTime.c_str());
		TRACE("\n");

		flag = 6;
	}
	else if (receivingOrderVector[1].compare(orderString[5]) == 0)
	{
		string FNameA = receivingOrderVector[2];
		string FNameB = receivingOrderVector[3];

		string friend_a = FNameA;
		string friend_b = FNameB;

		if (FNameA >= FNameB)
		{
			friend_a = FNameB;
			friend_b = FNameA;
		}

		string sqlUpdateFriendListTitle = "UPDATE friend_list ";
		string sqlUpdateFriendship = "SET friend_relationship = 'ab'";

		string sqlWhereFriendA = " WHERE friend_a = '";
		string sqlWhereFriendB = " AND friend_b = '";

		string sqlEnd = "'";

		//"UPDATE user_info SET user_state='0' WHERE user_name='LJY_Mie' ";

		string sqlUpdateExecute = sqlUpdateFriendListTitle + sqlUpdateFriendship 
			+ sqlWhereFriendA + friend_a + sqlEnd 
			+ sqlWhereFriendB + friend_b + sqlEnd;

		const sql::SQLString sqlUpdateString(sqlUpdateExecute.c_str());
		m_sql_operator->MySQLUpdate(sqlUpdateString);
		flag = 9;
	}
	else if (receivingOrderVector[1].compare(orderString[6]) == 0)
	{
		string FNameA = receivingOrderVector[2];
		string FNameB = receivingOrderVector[3];

		string friend_a = FNameA;
		string friend_b = FNameB;
		string relationship = "a";
		string InFriendShip = "b";

		if (FNameA >= FNameB)
		{
			friend_a = FNameB;
			friend_b = FNameA;
			relationship = "b";
			InFriendShip = "a";
		}

		string sqlSelectTitle = "SELECT * FROM user_info ";
		string sqlWhereUserName = " WHERE user_name = '";
		string sqlWherePassword = "' AND password = '";
		string sqlEnd = "'";

		string sqlExecute = sqlSelectTitle + sqlWhereUserName + FNameB + sqlEnd;

		const sql::SQLString sqlString(sqlExecute.c_str());
		sql::ResultSet *res;
		res = m_sql_operator->MySQLQuery(sqlString);
		flag = 10;
		if (res->next())
		{
			TRACE("\n");
			TRACE(" SQLLoginState : %d \n", res->getInt("id"));
			TRACE(" SQLLoginState : %s \n", res->getString("user_name").c_str());
			TRACE(" SQLLoginState : %s \n", res->getString("password").c_str());
			TRACE(" SQLLoginState : %s \n", res->getString("user_state").c_str());
			TRACE("\n");
			flag = 12;
		}

		string sqlFriendTestExecute = "SELECT * FROM friend_list WHERE friend_a='"
			+ friend_a + "' AND friend_b = '" + friend_b + "'";
		const sql::SQLString sqlFriendTestString(sqlFriendTestExecute.c_str());
		sql::ResultSet *res2;
		res2 = m_sql_operator->MySQLQuery(sqlFriendTestString);
		if (res2->next())
		{
			flag = 11;
		}

		if (flag == 12)
		{
			//"INSERT INTO user_info (user_name, password, user_state) VALUES ('LJY_Mie', '333333', 1)";
			string sqlFriendTestInsert = "INSERT INTO friend_list (friend_a, friend_b, friend_relationship) VALUES ('"
				+ friend_a + "', '" + friend_b + "', '" + relationship + "')";
			const sql::SQLString sqlFriendInsertString(sqlFriendTestInsert.c_str());
			m_sql_operator->MySQLInsert(sqlFriendInsertString);
		}

	}

	return flag;
}


// 获取好友申请列表
int SemanticPrsing::GetFriendListRequest(MySQLModule* m_sql_operator, string userName)
{
	// TODO: 在此处添加实现代码.
	string sqlSelectFriendListTitle = "SELECT * FROM friend_list ";
	string sqlWhereFriendA = " WHERE friend_a = '";
	string sqlWhereFriendB = " WHERE friend_b = '";
	string sqlWhereFriendRelationshipA = " AND friend_relationship = 'a' ";
	string sqlWhereFriendRelationshipB = " AND friend_relationship = 'b' ";
	string sqlEnd = "'";

	string sqlQueryAExecute = sqlSelectFriendListTitle + sqlWhereFriendA + userName + sqlEnd + sqlWhereFriendRelationshipB;
	string sqlQueryBExecute = sqlSelectFriendListTitle + sqlWhereFriendB + userName + sqlEnd + sqlWhereFriendRelationshipA;

	CList<string> frinedRequestList;

	const sql::SQLString sqlAString(sqlQueryAExecute.c_str());
	sql::ResultSet *resA;
	resA = m_sql_operator->MySQLQuery(sqlAString);
	while (resA->next())
	{

		int id = resA->getInt("id");
		string friend_a = resA->getString("friend_a").c_str();
		string friend_b = resA->getString("friend_b").c_str();
		string friend_relationship = resA->getString("friend_relationship").c_str();
		TRACE("\n");
		TRACE(" SQLAFState : %d \n", id);
		TRACE(" SQLAFState : %s \n", friend_a.c_str());
		TRACE(" SQLAFState : %s \n", friend_b.c_str());
		TRACE(" SQLAFState : %s \n", friend_relationship.c_str());
		TRACE("\n");


		frinedRequestList.AddTail(friend_b);
	}

	const sql::SQLString sqlBString(sqlQueryBExecute.c_str());
	sql::ResultSet *resB;
	resB = m_sql_operator->MySQLQuery(sqlBString);
	while (resB->next())
	{

		int id = resB->getInt("id");
		string friend_a = resB->getString("friend_a").c_str();
		string friend_b = resB->getString("friend_b").c_str();
		string friend_relationship = resB->getString("friend_relationship").c_str();
		TRACE("\n");
		TRACE(" SQAFtate : %d \n", id);
		TRACE(" SQAFtate : %s \n", friend_a.c_str());
		TRACE(" SQAFtate : %s \n", friend_b.c_str());
		TRACE(" SQAFtate : %s \n", friend_relationship.c_str());
		TRACE("\n");


		frinedRequestList.AddTail(friend_a);
	}
	
	//memset(FListRequest, 0, sizeof(FListRequest) / sizeof(char));
	memset(FListRequest, 0, sizeof(FListRequest));
	strcpy_s(FListRequest, "");

	POSITION pos = frinedRequestList.GetHeadPosition();
	while (pos != NULL) {
		string name = frinedRequestList.GetNext(pos);
		TRACE(" Friend Test : %s \n", name.c_str());
		strcat_s(FListRequest, name.c_str());
		strcat_s(FListRequest, "-");
	}

	TRACE(" Friend Test : %s \n", FListRequest);

	return 8;
}
