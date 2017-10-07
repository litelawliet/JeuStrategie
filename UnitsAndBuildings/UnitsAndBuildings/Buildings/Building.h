#ifndef BUILDING_HPP
#define BUILDING_HPP

#include <iostream>

class Building
{
public:
	Building();
	virtual ~Building() = 0;

	int getPV() const;
	int getMaxPV() const;
	bool isAlive() const;

	void setPV(int pv);
	void setMaxPV(int maxPV);
	//vision field

private:
	int m_pv;
	int m_maxPV;
	//vision field
};

#endif