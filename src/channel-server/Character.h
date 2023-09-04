#include <iostream>
#include <string>
#include <sys/socket.h>
#include <"mytype.h">

#ifndef Character_H
#define Character_H

Class Character
{
private:
	int fd;
	struct sockaddr c_addr;
	std::string name;
	int hp = 10;
	int money;
	struct Position pos = {0,0};
	int att = 10;
	int def = 10;
	int map;
	double speed = 0.5;
	double attack_speed = 0.5;

public:
	Character();
	~Character();
	Character& setFD(int);
	Character& setSockAddr(struct sockaddr);
	Character& setName(std::string);
	Character& setHP(int);
	Character& setMoney(int);
	Character& setPosition(struct Position);
	Character& setPosition(int, int);
	Character& setPositionX(int);
	Character& setPositionY(int);
	Character& setAtt(int);
	Character& setDef(int);
	Character& setMap(int);
	Character& setSpeed(double);
	Character& setAttackSpeed(double);
	int getFD();
	struct sockaddr getSockAddr();
	std::string getName();
	int getHP();
	int getMoney();
	struct Postition getPosition();
	int getPositionX();
	int getPositionY();
	int getAtt();
	int getDef();
	int getMap();
	double getSpeed();
	double getAttackSpeed();

	virtual void attack();
	virtual void hit();
	virtual void move();

};

Class Player
{
private:
	std::string id;
	int inventory[15];
	int equip[2];

public:
	void setID();
	void setInventoryAll(int*);
	void setInventoryOne(int, int);
	void setEquipAll(int*);
	void setEquipOne(int, int);
	string getID();
	int* getInventoryAll();
	int getInventoryOne(int);
	int* getEquipAll();
	int getEquipOne(int);

};

Class NPC
{
private: 
	int drop_table;
	int exp_table;

public:
	int getDropTable();
	int getExpTable();

	void drop();

};

#endif
