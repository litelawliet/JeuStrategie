#include "ChargedWeapon.h"



ChargedWeapon::ChargedWeapon(Game_n::Player* p)
{
	std::cout << "CHARGED WEAPON constructor\n";
	mOwner = p;
}


ChargedWeapon::~ChargedWeapon()
{
	std::cout << "CHARGED WEAPON destructor\n";
}
