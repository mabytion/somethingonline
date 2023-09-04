#include "DBManagement.h"

DBManagement::DBManagement()
{
	
}

DBManagement::DBManagement(string _server, string _user, string _passwd, string _db)
{
	setServer(_server).setUser(_user).setPasswd(_passwd).setDB(_db).connSetup();
}

DBManagement::~DBManagement()
{
//	mysql_free_result(res);
//	mysql_close(connection);
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

void DBManagement::connSetup()
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

vector<string> DBManagement::resToVector(MYSQL_RES* res, int count)
{
	vector<string> vec;

	while((row = mysql_fetch_row(res)) != NULL)
	{
		for(int i=0;i<count;i++)
		{
			vec.push_back(row[i]);
		}

		vec.push_back("");
	}

	return vec;
}

vector<struct PlayerList> DBManagement::getPlayerList(string _id)
{
	vector<struct PlayerList> result;
	vector<string> tmp;
	struct PlayerList pl[3];
	string sql;

	sql.append("SELECT p.name, e.equip1, e.equip2");
	sql.append(" FROM player p");
	sql.append(" INNER JOIN equip e");
	sql.append(" ON p.name = e.name");
	sql.append(" WHERE p.id = ");
	sql.push_back('\"');
	sql.append(_id);
	sql.push_back('\"');

	tmp = resToVector(query(sql), 3);

	for(int i=0;i<tmp.size();i++)
	{
		switch(i%4)
		{
			case 0:
				pl[i/4].name = tmp[i];
				break;
			case 1:
				pl[i/4].equip[0] = atoi(tmp[i].c_str());
				break;
			case 2:
				pl[i/4].equip[1] = atoi(tmp[i].c_str());
				break;
			case 3:
				result.push_back(pl[i/4]);
		}

	}

	return result;
}

vector<string> DBManagement::getPlayerDataOne(string _name)
{
	vector<string> result;
	string sql;

	sql.append("SELECT p.id, p.name, p.map,");
	sql.append(" p.money, e.equip1, e.equip2,");
	sql.append(" i.slot1, i.slot2, i.slot3,");
	sql.append(" i.slot4, i.slot5, i.slot6,");
	sql.append(" i.slot7, i.slot8, i.slot9,");
	sql.append(" i.slot10, i.slot11, i.slot12,");
	sql.append(" i.slot13, i.slot14, i.slot15");
	sql.append(" FROM player p");
	sql.append(" INNER JOIN equip e");
	sql.append(" ON p.name=e.name");
	sql.append(" INNER JOIN inventory i");
	sql.append(" ON e.name=i.name");
	sql.append(" WHERE p.name=");
	sql.push_back('\"');
	sql.append(_name);
	sql.push_back('\"');

	result = resToVector(query(sql), 21);

	return result;
}

vector<string> DBManagement::getInventoryAll(string _name)
{
	vector<string> result;
	string sql;

	sql.append("SELECT p.name, i.slot1, i.slot2, i.slot3,");
	sql.append(" i.slot4, i.slot5, i.slot6,");
	sql.append(" i.slot7, i.slot8, i.slot9,");
	sql.append(" i.slot10, i.slot11, i.slot12,");
	sql.append(" i.slot13, i.slot14, i.slot15");
	sql.append(" FROM player p");
	sql.append(" INNER JOIN inventory i");
	sql.append(" ON p.name = i.name");
	sql.append(" WHERE p.name = ");
	sql.push_back('\"');
	sql.append(_name);
	sql.push_back('\"');

	result = resToVector(query(sql), 16);

	return result;
}

vector<string> DBManagement::getEquipAll(string _name)
{
	vector<string> result;
	string sql;

	sql.append("SELECT p.name, e.equip1, e.equip2");
	sql.append(" FROM player p");
	sql.append(" INNER JOIN equip e");
	sql.append(" ON p.name = e.name");
	sql.append(" WHERE p.name = ");
	sql.push_back('\"');
	sql.append(_name);
	sql.push_back('\"');

	result = resToVector(query(sql), 3);
}

DBManagement& DBManagement::setEquipAll(string _name, int _equip1, int _equip2)
{
	string sql;

	sql.append("INSERT INTO equip");
	sql.append(" ( name, equip1, equip2 )");
	sql.append(" VALUES (").append(_name).push_back(',');
	sql.append(_equip1).push_back(',').append(_equip2).push_back(')');
	sql.append(" ON DUPLICATE KEY");
	sql.append(" UPDATE equip1=");
	sql.append(to_string(_equip1));
	sql.push_back(',');
	sql.append(" equip2=");
	sql.append(to_string(_equip2));

	query(sql);

	return *this;
}

DBManagement& DBManagement::setInventoryAll(string _name, int* _slot;)
{
	string sql;

	sql.append("INSERT INTO inventory");
	sql.append(" VALUES (");
	sql.append(_slot[0]).push_back(',');
	sql.append(_slot[1]).push_back(',');
	sql.append(_slot[2]).push_back(',');
	sql.append(_slot[3]).push_back(',');
	sql.append(_slot[4]).push_back(',');
	sql.append(_slot[5]).push_back(',');
	sql.append(_slot[6]).push_back(',');
	sql.append(_slot[7]).push_back(',');
	sql.append(_slot[8]).push_back(',');
	sql.append(_slot[9]).push_back(',');
	sql.append(_slot[10]).push_back(',');
	sql.append(_slot[11]).push_back(',');
	sql.append(_slot[12]).push_back(',');
	sql.append(_slot[13]).push_back(',');
	sql.append(_slot[14]).push_back(',');
	sql.append(_slot[15]).push_back(')');
	sql.append(" ON DUPLICATE KEY");
	sql.append(" UPDATE");
	sql.append(" slot1=").sql.append(_slot[0]).sql.push_back(',');
	sql.append(" slot2=").sql.append(_slot[1]).sql.push_back(',');
	sql.append(" slot3=").sql.append(_slot[2]).sql.push_back(',');
	sql.append(" slot4=").sql.append(_slot[3]).sql.push_back(',');
	sql.append(" slot5=").sql.append(_slot[4]).sql.push_back(',');
	sql.append(" slot6=").sql.append(_slot[5]).sql.push_back(',');
	sql.append(" slot7=").sql.append(_slot[6]).sql.push_back(',');
	sql.append(" slot8=").sql.append(_slot[7]).sql.push_back(',');
	sql.append(" slot9=").sql.append(_slot[8]).sql.push_back(',');
	sql.append(" slot10=").sql.append(_slot[9]).sql.push_back(',');
	sql.append(" slot11=").sql.append(_slot[10]).sql.push_back(',');
	sql.append(" slot12=").sql.append(_slot[11]).sql.push_back(',');
	sql.append(" slot13=").sql.append(_slot[12]).sql.push_back(',');
	sql.append(" slot14=").sql.append(_slot[13]).sql.push_back(',');
	sql.append(" slot15=").sql.append(_slot[14]);

	query(sql);


	return *this;
}

DBManagement& DBManagement::setPlayerDataAll(Player* pl)
{
	string sql;
	int* _inventory = pl->getInventoryAll();
	int* _equip = pl->getEquipAll();

	sql.append("INSERT ALL");
	sql.append("INTO player p").push_back(' ');
	sql.append("VALUES (").push_back(' ');
	sql.append(pl->getID()).push_back(',');
	sql.append(pl->getName()).push_back(',');
	sql.append(to_string(pl->getMap()).push_back(',');
	sql.append(to_string(pl->getMoney()).push_back(')'));
	sql.append("ON DUPLICATE KEY").push_back(' ');
	sql.append("UPDATE p.map=").push_back(',');
	sql.append("p.money=").append(to_string(pl->getMoney()).push_back(')').push_back(' ');
	sql.append("INTO equip e").push_back(' ');
	sql.append("VALUES (");
	sql.append(_name).push_back(',');
	sql.append(to_string(_equip[0]).push_back(',');
	sql.append(to_string(_equip[1]).push_back(')');
	sql.append("ON DUPLICATE KEY").push_back(' ');
	sql.append("UPDATE e.equip1=").append(to_string(_equip[0])).push_back(',');
	sql.append("e.equip2=").append(to_string(_equip[1])).push_back(')');
	sql.append("INTO inventory i").push_back(' ');
	sql.append("VALUES (");
	sql.append(to_string(_inventory[0])).push_back(",");
	sql.append(to_string(_inventory[1])).push_back(",");
	sql.append(to_string(_inventory[2])).push_back(",");
	sql.append(to_string(_inventory[3])).push_back(",");
	sql.append(to_string(_inventory[4])).push_back(",");
	sql.append(to_string(_inventory[5])).push_back(",");
	sql.append(to_string(_inventory[6])).push_back(",");
	sql.append(to_string(_inventory[7])).push_back(",");
	sql.append(to_string(_inventory[8])).push_back(",");
	sql.append(to_string(_inventory[9])).push_back(",");
	sql.append(to_string(_inventory[10])).push_back(",");
	sql.append(to_string(_inventory[11])).push_back(",");
	sql.append(to_string(_inventory[12])).push_back(",");
	sql.append(to_string(_inventory[13])).push_back(",");
	sql.append(to_string(_inventory[14])).push_back(")");
	sql.append("ON DUPLICATE KEY").push_back(' ');
	sql.append("UPDATE").push_back(' ');
	spl.append("slot1=").append(to_string(_inventory[0]).push_back(',');
	spl.append("slot2=").append(to_string(_inventory[1]).push_back(',');
	spl.append("slot3=").append(to_string(_inventory[2]).push_back(',');
	spl.append("slot4=").append(to_string(_inventory[3]).push_back(',');
	spl.append("slot5=").append(to_string(_inventory[4]).push_back(',');
	spl.append("slot6=").append(to_string(_inventory[5]).push_back(',');
	spl.append("slot7=").append(to_string(_inventory[6]).push_back(',');
	spl.append("slot8=").append(to_string(_inventory[7]).push_back(',');
	spl.append("slot9=").append(to_string(_inventory[8]).push_back(',');
	spl.append("slot10=").append(to_string(_inventory[9]).push_back(',');
	spl.append("slot11=").append(to_string(_inventory[10]).push_back(',');
	spl.append("slot12=").append(to_string(_inventory[11]).push_back(',');
	spl.append("slot13=").append(to_string(_inventory[12]).push_back(',');
	spl.append("slot14=").append(to_string(_inventory[13]).push_back(',');
	spl.append("slot15=").append(to_string(_inventory[14]).push_back(')');
	sql.append("SELECT * FROM player;");

	query(sql);


	return *this;
}
