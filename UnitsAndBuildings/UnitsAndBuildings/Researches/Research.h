#ifndef RESEARCH_HPP
#define RESEARCH_HPP

#include <iostream>
#include "../../../Game/Game.hpp"

class Research
{
public:
	Research();
	virtual ~Research();
	Game_n::Player& getOwner() { return mOwner; }

private:
	Game_n::Player& mOwner;
};

#endif