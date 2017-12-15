#ifndef RESEARCH_HPP
#define RESEARCH_HPP

#include <iostream>
#include "../../../Game/Player.hpp"

class Research
{
	public:
		Research();
		Research(Game_n::Player* owner, int timeQueue)
			: mOwner(owner)
			, mTimeQueue(timeQueue)
		{}
		virtual ~Research();

		Game_n::Player& getOwner();
		virtual int getTimeQueue() {
			return mTimeQueue;
		}

	protected:
		int mTimeQueue;
		Game_n::Player* mOwner;
};

#endif