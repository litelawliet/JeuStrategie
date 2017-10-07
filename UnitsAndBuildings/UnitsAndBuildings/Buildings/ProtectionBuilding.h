#ifndef PROTECTION_BUILDING_HPP
#define PROTECTION_BUILDING_HPP

#include "Building.h"
class ProtectionBuilding :
	public Building
{
public:
	ProtectionBuilding();
	virtual ~ProtectionBuilding() = 0;
};

#endif