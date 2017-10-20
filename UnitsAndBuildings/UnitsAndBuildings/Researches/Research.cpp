#include "Research.h"



Research::Research()
{
}

Research::Research(Game_n::Player* p)
	: mOwner(new Game_n::Player(*p))
{
	std::cout << "RESEARCH constructor\n";
}


Research::~Research()
{
	std::cout << "RESEARCH destructor\n";
	delete mOwner;
}

Game_n::Player& Research::getOwner() {
	return *mOwner;
}