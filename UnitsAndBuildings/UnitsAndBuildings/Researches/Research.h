#ifndef RESEARCH_HPP
#define RESEARCH_HPP

#include <iostream>
#include "../../../Game/Player.hpp"

class Research
{
	public:
		Research();
		Research(Game_n::Player* p);
		virtual ~Research();

		Game_n::Player& getOwner();

	protected:
		Game_n::Player* mOwner;
};

#endif