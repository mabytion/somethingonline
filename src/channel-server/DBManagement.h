#include "mytype.h"
#include "Character.h"
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
	DBManagement();
	DBManagement(string, string, string, string);
	~DBManagement();
	DBManagement& setServer(string);
	DBManagement& setUser(string);
	DBManagement& setPasswd(string);
	DBManagement& setDB(string);
	void connSetup();
	MYSQL_RES* query(string);
	vector<string> resToVector(MYSQL_RES*, int);
	vector<struct PlayerList> getPlayerList(string);
	vector<string> getPlayerDataOne(string);
	vector<string> getInventoryAll(string);
	vector<string> getEquipAll(string);
	DBManagement& setEquipAll(string, int, int);
	DBManagement& setInventoryAll(string, int*);
	DBManagement& setPlayerDataAll(Player);

};

#endif
