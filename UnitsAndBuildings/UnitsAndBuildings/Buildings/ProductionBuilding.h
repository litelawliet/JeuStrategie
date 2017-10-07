#ifndef PRODUCTION_BUILDING_HPP
#define PRODUCTION_BUILDING_HPP

#include "Building.h"
class ProductionBuilding :
	public Building
{
public:
	ProductionBuilding();
	virtual ~ProductionBuilding() = 0;
};

#endif