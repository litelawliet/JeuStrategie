#ifndef CHARGED_WEAPON_HPP
#define CHARGED_WEAPON_HPP

#include "Research.h"
class ChargedWeapon :
	public Research
{
public:
	ChargedWeapon(Game_n::Player* p);
	~ChargedWeapon();
};

#endif