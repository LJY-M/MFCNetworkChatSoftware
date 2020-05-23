#include "pch.h"
#include "SemanticPrsing.h"


int SemanticPrsing::receivingOrder(MySQLModule* m_sql_operator, vector<string> receivingOrderVector)
{
	// TODO: 在此处添加实现代码.

	int flag = 0;//0:失败；1：登录成功；2:密码错误；3：多地登录；4：退出成功；5：发送好友列表；6：发送信息

	for (size_t i = 0; i < receivingOrderVector.size(); i++)
	{
		TRACE("Receive split : %s \n", receivingOrderVector[i].c_str());
	}

	string orderString[] = {"Client send","Login","Logout","ListInit","SendMSG"};

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
			TRACE(" SQLState : %d \n", id);
			TRACE(" SQLState : %s \n", friend_a.c_str());
			TRACE(" SQLState : %s \n", friend_b.c_str());
			TRACE(" SQLState : %s \n", friend_relationship.c_str());
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
	return flag;
}
