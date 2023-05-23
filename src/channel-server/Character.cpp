#incldue <"Character.h">

Character::Character()
{

}
Character::~Character()
{
	close(fd);
}
Character& Character::setFD(int _fd) { fd = _fd; return *this; }
Character& Character::setSockAddr(struct sockaddr_in _c_addr) { c_addr = _c_addr; return *this; }
Character& Character::setName(std::string _name) { name = _name; return *this; }
Character& Character::setHP(int _hp) { hp = _hp; return *this; }
Character& Character::setMoney(int _money) { money = _money; return *this; }
Character& Character::setPosition(struct Position _pos) { pos = _pos; return *this; }
Character& Character::setPosition(int _x, int _y) { pos.x = _x; pos.y = _y; return *this; }
Character& Character::setPositionX(int _x) { pos.x = _x; return *this; }
Character& Character::setPositionY(int _y) { pos.y = _y; return *this; }
Character& Character::setAtt(int _att) { att = _att; return *this; }
Character& Character::setDef(int _def) { def = _def; return *this; }
Character& Character::setSpeed(double _speed) { speed = _speed; return *this; }
Character& Character::setAttackSpeed(double _attack_speed) { attack_speed = _attack_speed; return *this; }
int Character::getFD(void) { return fd; }
struct sockaddr_in Character::getSockAddr(void) { return c_addr; }
std::string Character::getName(void) { return name; }
int Character::getHP(void) { return hp; }
int Character::getMoney(void) { return money; }
struct Position Character::getPosition(void) { return pos; }
int Character::getPositionX(void) { return pos.x; }
int Character::getPositionY(void) { return pox.y; }
int Character::getAtt(void) { return att; }
int Character::getDef(void) { return def; }
double Character::getSpeed(void) { return speed; }
double Character::getAttackSpeed(void) { return attack_speed; }


Player::void setInventoryAll(int* _inventory)
{
	for(int i=0;i<(sizeof(_inventory)/4);i++)
		inventory[i] = _inventory[i];
}
Player::void setInventoryOne(int index, int code) { inventory[index] = code; }
Player::void setEquipAll(int* _equip)
{
	for(int i=0;i<(sizeof(_inventory)/4);i++)
		equip[i] = _equip[i];
}
Player::void setEquipOne(int index, int code) { equip[index] = code; }
Player::int* getInventoryAll(void) { return inventory; }
Player::int getInventoryOne(int index) { return inventory[index]; }
Player::int* getEquipAll(void) { return equip; }
Player::int getEquipOne(int) { return equip[index]; }

int NPC::getDropTable(void) { return drop_table; }
int NPC::getExpTable(void) { return exp_table; }
void NPC::drop(void) { }
