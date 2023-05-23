#include <iostream>
#include <string>
#include <sys/socket.h>

#ifndef Character_H
#define Character_H

struct Position
{
	int X;
	int Y;
};

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
	int getFD(void);
	struct sockaddr getSockAddr(void);
	std::string getName(void);
	int getHP(void);
	int getMoney(void);
	struct Postition getPosition(void);
	int getPositionX(void);
	int getPositionY(void);
	int getAtt(void);
	int getDef(void);
	int getMap(void);
	double getSpeed(void);
	double getAttackSpeed(void);

	virtual void attack();
	virtual void hit();
	virtual void move();

};

Class Player
{
private:
	int inventory[30];
	int equip[2];

public:
	void setInventoryAll(int*);
	void setInventoryOne(int, int);
	void setEquipAll(int*);
	void setEquipOne(int, int);
	int* getInventoryAll(void);
	int getInventoryOne(int);
	int* getEquipAll(void);
	int getEquipOne(int);

};

Class NPC
{
private: 
	int drop_table;
	int exp_table;

public:
	int getDropTable(void);
	int getExpTable(void);

	void drop();

};

#endif
