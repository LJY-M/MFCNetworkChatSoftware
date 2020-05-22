#pragma once

#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"

//#include <cppconn/driver.h>
//#include <cppconn/exception.h>
//#include <cppconn/resultset.h>
//#include <cppconn/statement.h>

#include "jdbc/mysql_connection.h"
#include "jdbc/mysql_driver.h"
#include "jdbc/cppconn/statement.h"

class MySQLModule
{
public:
	MySQLModule();
	virtual ~MySQLModule();
	void connectTest();

public:
	sql::mysql::MySQL_Driver *driver = NULL;
	sql::Connection *con = NULL;
	sql::ResultSet* MySQLQuery(const sql::SQLString& sql);
	bool MySQLInsert(const sql::SQLString& sql);
	bool MySQLUpdate(const sql::SQLString& sqlString);
	bool MySQLDelete(const sql::SQLString& sqlString);
};

