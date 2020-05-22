#include "pch.h"
#include "MySQLModule.h"

using namespace std;

MySQLModule::MySQLModule() {
	/* �������� */
	driver = sql::mysql::get_mysql_driver_instance();
	if (driver == NULL)
	{
		TRACE(" SQLState : driver = null \n");
	}
	con = driver->connect("tcp://127.0.0.1:3306/network_chat_platform", "root", "121025");
	if (con == NULL)
	{
		TRACE(" SQLState : con = null \n");
	}
	/* ���� MySQL ���ݿ� test  */
	con->setSchema("network_chat_platform");

	AfxMessageBox(_T("���ݿ����ӳɹ���"));
}

MySQLModule::~MySQLModule()
{
}

void MySQLModule::connectTest()
{
	try {
		sql::mysql::MySQL_Driver *driver = NULL;
		sql::Connection *con = NULL;
		//sql::Statement *stmt;
		//sql::ResultSet *res;

		/* �������� */
		driver = sql::mysql::get_mysql_driver_instance();
		if (driver == NULL)
		{
			TRACE(" SQLState : driver = null \n");
		}
		con = driver->connect("tcp://127.0.0.1:3306/network_chat_platform", "root", "121025");
		if (con == NULL)
		{
			TRACE(" SQLState : con = null \n");
		}
		/* ���� MySQL ���ݿ� test  */
		con->setSchema("network_chat_platform");

		AfxMessageBox(_T("���ӳɹ���"));

		//��ѯ
		int flag = 0;
		sql::Statement *stmt = con->createStatement();
		sql::ResultSet *res;
		res = stmt->executeQuery("SELECT * FROM user_info");
		while (res->next())
		{
			TRACE(" SQLState : %d \n", res->getInt("id"));
			TRACE(" SQLState : %s \n", res->getString("user_name").c_str());
			TRACE(" SQLState : %s \n", res->getString("password").c_str());
			TRACE(" SQLState : %s \n", res->getString("user_state").c_str());
			//cout << res->getInt("id") << endl;
			//cout << res->getString("phone").c_str() << endl;
			//cout << res->getString("imsi").c_str() << endl;
		}

		//��ѯ
		//bool retValue = stmt->execute("SELECT * FROM user_info");
		//if (retValue) {
		//	res = stmt->getResultSet();
		//	while (res->next())
		//	{
		//		TRACE(" SQLState : %d \n", res->getInt("id"));
		//		TRACE(" SQLState : %s \n", res->getString("user_name").c_str());
		//		TRACE(" SQLState : %s \n", res->getString("password").c_str());
		//		TRACE(" SQLState : %s \n", res->getString("user_state").c_str());
		//	}
		//}

		//����
		//retValue = stmt->execute("INSERT INTO user_info (user_name, password, user_state) VALUES ('LJY_Mie', '333333', 1)");
		//int updateCount = 0;
		//if (!retValue)
		//{
		//	updateCount = stmt->getUpdateCount();
		//}

		//�޸�
		//bool retValue = stmt->execute("UPDATE user_info SET user_state='0' WHERE user_name='LJY_Mie' ");

		//ɾ��
		//bool retValue = stmt->execute("DELETE FROM user_info WHERE user_name='LJY_Mie' ");

		//stmt = con->createStatement();
		//res = stmt->executeQuery("SELECT 'Hello World!' AS _message");
		//while (res->next()) {
		//	cout << "\t... MySQL replies: ";
		//	/* ��ȡĳ������ֵͨ������ */
		//	cout << res->getString("_message") << endl;
		//	cout << "\t... MySQL says it again: ";
		//	/* ͨ������ƫ����, 1 �����һ�� */
		//	cout << res->getString(1) << endl;
		//}
		//delete res;
		//delete stmt;
		//delete con;

	}
	catch (sql::SQLException &e) {
		//cout << "# ERR: SQLException in " << __FILE__;
		//cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		//cout << "# ERR: " << e.what();
		//cout << " (MySQL error code: " << e.getErrorCode();
		//cout << ", SQLState: " << e.getSQLState() << " )" << endl;

		TRACE("# ERR: SQLException in  : %s \n", __FILE__);
		//TRACE("on line : %s \n", __LINE__);
		TRACE("# ERR : %s \n", e.what());
		TRACE(" (MySQL error code : %s \n", e.getErrorCode());
		TRACE(" SQLState : %s \n", e.getSQLState());

		AfxMessageBox(_T("����ʧ�ܣ�"));
	}
}


sql::ResultSet* MySQLModule::MySQLQuery(const sql::SQLString& sqlString)
{
	// TODO: �ڴ˴����ʵ�ִ���.

	try
	{
		//��ѯ
		sql::Statement *stmt = con->createStatement();
		sql::ResultSet *res = NULL;

		res = stmt->executeQuery(sqlString);

		delete stmt;

		return res;
	}
	catch (sql::SQLException &e)
	{
		TRACE(" (MySQL error code : %s \n", e.getErrorCode());
		//TRACE(" SQLState : %s \n", e.getSQLState());
	}

	//res = stmt->executeQuery("SELECT * FROM user_info");
	//while (res->next())
	//{
	//	TRACE(" SQLState : %d \n", res->getInt("id"));
	//	TRACE(" SQLState : %s \n", res->getString("user_name").c_str());
	//	TRACE(" SQLState : %s \n", res->getString("password").c_str());
	//	TRACE(" SQLState : %s \n", res->getString("user_state").c_str());
	//	//cout << res->getInt("id") << endl;
	//	//cout << res->getString("phone").c_str() << endl;
	//	//cout << res->getString("imsi").c_str() << endl;
	//}

	//��ѯ
	//bool retValue = stmt->execute("SELECT * FROM user_info");
	//if (retValue) {
	//	res = stmt->getResultSet();
	//	while (res->next())
	//	{
	//		TRACE(" SQLState : %d \n", res->getInt("id"));
	//		TRACE(" SQLState : %s \n", res->getString("user_name").c_str());
	//		TRACE(" SQLState : %s \n", res->getString("password").c_str());
	//		TRACE(" SQLState : %s \n", res->getString("user_state").c_str());
	//	}
	//}

	
}


bool MySQLModule::MySQLInsert(const sql::SQLString& sqlString)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	try
	{
		//����
		sql::Statement *stmt = con->createStatement();
		bool retValue;

		retValue = stmt->execute(sqlString);
		//retValue = stmt->execute("INSERT INTO user_info (user_name, password, user_state) VALUES ('LJY_Mie', '333333', 1)");
		
		uint64_t updateCount = 0;
		if (!retValue)
		{
			updateCount = stmt->getUpdateCount();
			TRACE(" SQLState updateCount : %d \n", updateCount);
		}

		delete stmt;

		return retValue;
	}
	catch (sql::SQLException &e)
	{
		TRACE(" (MySQL error code : %s \n", e.getErrorCode());
		TRACE(" SQLState : %s \n", e.getSQLState());
	}
}


bool MySQLModule::MySQLUpdate(const sql::SQLString& sqlString)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	try
	{
		//����
		sql::Statement *stmt = con->createStatement();
		bool retValue;

		retValue = stmt->execute(sqlString);
		//bool retValue = stmt->execute("UPDATE user_info SET user_state='0' WHERE user_name='LJY_Mie' ");

		delete stmt;

		return retValue;
	}
	catch (sql::SQLException &e)
	{
		TRACE(" (MySQL error code : %s \n", e.getErrorCode());
		TRACE(" SQLState : %s \n", e.getSQLState());
	}
}


bool MySQLModule::MySQLDelete(const sql::SQLString& sqlString)
{
	// TODO: �ڴ˴����ʵ�ִ���.
	try
	{
		//ɾ��
		sql::Statement *stmt = con->createStatement();
		bool retValue;

		retValue = stmt->execute(sqlString);
		//bool retValue = stmt->execute("DELETE FROM user_info WHERE user_name='LJY_Mie' ");

		delete stmt;

		return retValue;
	}
	catch (sql::SQLException &e)
	{
		TRACE(" (MySQL error code : %s \n", e.getErrorCode());
		TRACE(" SQLState : %s \n", e.getSQLState());
	}
}
