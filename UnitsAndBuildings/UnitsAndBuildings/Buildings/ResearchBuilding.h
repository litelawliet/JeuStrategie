#ifndef RESEARCH_BUILDING_HPP
#define RESEARCH_BUILDING_HPP

#include "Building.h"
class ResearchBuilding :
	public Building
{
public:
	ResearchBuilding();
	virtual ~ResearchBuilding() = 0;
};

#endif