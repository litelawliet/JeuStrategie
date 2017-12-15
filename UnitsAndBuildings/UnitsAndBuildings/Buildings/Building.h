#ifndef BUILDING_HPP
#define BUILDING_HPP

#include <iostream>
#include "../../../Game/Player.hpp"

class Building
{
public:
Building(Game_n::Player owner, int timeQueue)
	: mTimeQueue(timeQueue)
	, mOwner(owner)
	{}
	virtual ~Building();

	int getPV() const;
	int getMaxPV() const;
	bool isAlive() const;

	void setPV(int pv);
	void setMaxPV(int maxPV);
	//vision field
	virtual int getTimeQueue() {
		return mTimeQueue;
	}
	Game_n::Player& getOwner();


private:
	Game_n::Player* mOwner;
	int m_pv;
	int m_maxPV;
	//vision field
	int mTimeQueue;
};

#endif