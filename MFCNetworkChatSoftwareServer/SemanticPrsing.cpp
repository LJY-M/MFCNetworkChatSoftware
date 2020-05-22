#include "pch.h"
#include "SemanticPrsing.h"


int SemanticPrsing::receivingOrder(MySQLModule* m_sql_operator, vector<string> receivingOrderVector)
{
	// TODO: 在此处添加实现代码.

	int flag = 0;//0:失败；1：登录成功；2:密码错误；3：多地登录；4：退出成功

	for (size_t i = 0; i < receivingOrderVector.size(); i++)
	{
		TRACE("Receive split : %s \n", receivingOrderVector[i].c_str());
	}

	string orderString[] = {"Client send","Login","Logout"};

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
			TRACE(" SQLState : %d \n", res->getInt("id"));
			TRACE(" SQLState : %s \n", res->getString("user_name").c_str());
			TRACE(" SQLState : %s \n", res->getString("password").c_str());
			TRACE(" SQLState : %s \n", res->getString("user_state").c_str());
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
	return flag;
}
