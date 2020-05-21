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
};

