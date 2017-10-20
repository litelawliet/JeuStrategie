#include "Research.h"



Research::Research()
{
	std::cout << "RESEARCH constructor\n";
}


Research::~Research()
{
	std::cout << "RESEARCH destructor\n";
}

Game::Player* Research::getOwner() {
	return owner;
}