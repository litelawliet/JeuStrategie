#ifndef UNIT_HPP
#define UNIT_HPP

#include <iostream>
#include "../../../Game/Player.hpp"

class Unit
{
	public:
		Unit(Game_n::Player* owner, int timeQueue)
			: mOwner(owner)
			, mTimeQueue(timeQueue)
		{}
		virtual ~Unit();

		virtual int getTimeQueue() {
			return mTimeQueue;
		}
		Game_n::Player& getOwner();

	private:
		int mTimeQueue;
		Game_n::Player* mOwner;
};

#endif