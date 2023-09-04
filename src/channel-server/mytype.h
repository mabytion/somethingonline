#include <string>
using std::string;

#ifndef MYTYPE_H
#define MYTYPE_H

struct Position
{
    int X;
    int Y;
};

struct PlayerList
{
	string name = "";
	int equip[2] = {0,0};
};

#endif
