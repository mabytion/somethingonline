#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;

#include <vector>
using std::vector;

#include <mysql/mysql.h>

#ifndef DBManagement_H
#define DBManagement_H

class DBManagement
{
private:
	MYSQL* connection;
	MYSQL_RES* res;
	MYSQL_ROW row;

	string server;	
	string user;
	string passwd;
	string db;

public:
	DBManagement(void);
	DBManagement(string, string, string, string);
	~DBManagement(void);
	DBManagement& setServer(string);
	DBManagement& setUser(string);
	DBManagement& setPasswd(string);
	DBManagement& setDB(string);
	void connSetup();
	MYSQL_RES* query(string);
	vector<string> resToVector(MYSQL_RES*);
	vector<string> getPlayerDataAll(string);
	vector<string> getPlaterDataOne(string);
	vector<string> getInventoryOne(string);
	vector<string> getEquipOne(string);
	

};

#endif
