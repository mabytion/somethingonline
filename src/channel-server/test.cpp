#include "DBManagement.h"
#include "mytype.h"
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

	vector<struct PlayerList> player_data = dbmgmt.getPlayerList(string("testaccount1"));
	
	for(int i=0;i<player_data.size();i++)
	{
		cout << player_data[i].name << " ";
		cout << player_data[i].equip[0] << " ";
		cout << player_data[i].equip[1] << endl;
	}

	return 0;
}
