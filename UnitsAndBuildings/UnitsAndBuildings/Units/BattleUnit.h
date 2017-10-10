#ifndef BATTLE_UNIT_HPP
#define BATTLE_UNIT_HPP

#include "Unit.h"
class BattleUnit :
	public Unit
{
public:
	BattleUnit();
	virtual ~BattleUnit() = 0;
};

#endif