#include "DBManagement.h"

DBManagement::DBManagement(void)
{
	
}

DBManagement::DBManagement(string _server, string _user, string _passwd, string _db)
{
	setServer(_server).setUser(_user).setPasswd(_passwd).setDB(_db).connSetup();
}

DBManagement::~DBManagement(void)
{
	mysql_free_result(res);
	mysql_close(connection);
}

DBManagement& DBManagement::setServer(string _server)
{
	server = _server;

	return *this;
}

DBManagement& DBManagement::setUser(string _user)
{
	user = _user;

	return *this;
}

DBManagement& DBManagement::setPasswd(string _passwd)
{
	passwd = _passwd;

	return *this;
}

DBManagement& DBManagement::setDB(string _db)
{
	db = _db;

	return *this;
}

void DBManagement::connSetup(void)
{
	
	connection = mysql_init(NULL);
	if(!mysql_real_connect(connection, server.c_str(), user.c_str(), passwd.c_str(), db.c_str(), 0, NULL, 0))
	{
		cout << "Connection Error: " << mysql_error(connection) << endl;
		exit(1);
	}
}

MYSQL_RES* DBManagement::query(string sql)
{
	if(mysql_query(connection, sql.c_str()))
	{
		cout << "MYSQL Query error: " << mysql_error(connection);
	}

	return mysql_use_result(connection);
}

vector<string> DBManagement::resToVector(MYSQL_RES* res)
{
	vector<string> vec;

	while((row = mysql_fetch_row(res)) != NULL)
	{
		vec.push_back(row[0]);
	}

	return vec;
}

vector<string> DBManagement::getInventoryOne(string)
{
	
}
