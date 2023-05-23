#include "DBManagement.h"
#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <vector>
using std::vector;


int main()
{
	DBManagement dbmgmt("127.0.0.1", "channel", "nasang", "gamedb");

	vector<string> player_data;
	vector<string> player_inventory;
	vector<string> player_equip;


	player_data = dbmgmt.resToVector(dbmgmt.query(string("select * from player")));
	player_inventory = dbmgmt.resToVector(dbmgmt.query(string("select * from inventory")));
	player_equip = dbmgmt.resToVector(dbmgmt.query(string("select * from equip")));
	
	for(int i=0;i<player_data.size();i++)
		cout << player_data[i] << endl;

	for(int i=0;i<player_inventory.size();i++)
		cout << player_inventory[i] << endl;
	
	for(int i=0;i<player_equip.size();i++)
		cout << player_equip[i] << endl;

	return 0;
}
