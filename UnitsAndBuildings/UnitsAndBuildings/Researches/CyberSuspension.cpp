#include "CyberSuspension.h"



CyberSuspension::CyberSuspension(Game_n::Player* p)
{
	std::cout << "CYBER SUSPENSION constructor\n";
	mOwner = p;
}


CyberSuspension::~CyberSuspension()
{
	std::cout << "CYBER SUSPENSION destructor\n";
}
