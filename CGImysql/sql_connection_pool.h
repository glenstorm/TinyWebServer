#ifndef _CONNECTION_POOL_
#define _CONNECTION_POOL_

#include <stdio.h>
#include <list>
#include <mysql/mysql.h>
#include <error.h>
#include <string.h>
#include <iostream>
#include <string>
#include "../lock/locker.h"
#include "../log/log.h"

using namespace std;

class connection_pool
{
public:
	MYSQL *GetConnection();				 //Get a database connection
	bool ReleaseConnection(MYSQL *conn); //Release a connection
	int GetFreeConn();					 //Idle connection count
	void DestroyPool();					 //Destroy every connection

	//Singleton
	static connection_pool *GetInstance();

	void init(string url, string User, string PassWord, string DataBaseName, int Port, int MaxConn, int close_log); 

private:
	connection_pool();
	~connection_pool();

	int m_MaxConn;  //Maximum number of connections
	int m_CurConn;  //Number of connections currently in use
	int m_FreeConn; //Current number of idle connections
	locker lock;
	list<MYSQL *> connList; //Connection pool
	sem reserve;

public:
	string m_url;			 //Host address
	string m_Port;		 //Database port
	string m_User;		 //Database login user name
	string m_PassWord;	 //Database login password
	string m_DatabaseName; //Database name
	int m_close_log;	//Log on/off switch
};

class connectionRAII{

public:
	connectionRAII(MYSQL **con, connection_pool *connPool);
	~connectionRAII();
	
private:
	MYSQL *conRAII;
	connection_pool *poolRAII;
};

#endif
