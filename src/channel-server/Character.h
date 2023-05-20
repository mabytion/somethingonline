#include <iostream>
#include <string>

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
	std::string name;
	int hp;
	int money;
	struct Position pos;
	int att;
	int def;
	double speed;
	double attack_speed;

public:
	void setFD(int);
	void setName(std::string);
	void setHP(int);
	void setMoney(int);
	void setPosition(struct Position);
	void setPosition(int, int);
	void setPositionX(int);
	void setPositionY(int);
	void setAtt(int);
	void setDef(int);
	void setSpeed(double);
	void setAttackSpeed(double);
	int getFD(void);
	std::string getName(void);
	int getHP(void);
	int getMoney(void);
	struct Postition getPosition(void);
	int getPositionX(void);
	int getPositionY(void);
	int getAtt(void);
	int getDef(void);
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
