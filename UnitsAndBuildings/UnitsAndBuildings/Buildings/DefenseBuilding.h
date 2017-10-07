#ifndef DEFENSE_BUILDING_HPP
#define DEFENSE_BUILDING_HPP

#include "Building.h"
class DefenseBuilding :
	public Building
{
public:
	DefenseBuilding();
	virtual ~DefenseBuilding() = 0;
};

#endif