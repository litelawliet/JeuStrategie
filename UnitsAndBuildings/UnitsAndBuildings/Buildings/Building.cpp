#include "Building.h"



Building::Building()
{
	std::cout << "BUILDING constructor\n";
}


Building::~Building()
{
	std::cout << "BUILDING destructor\n";
}

int Building::getPV() const
{
	return m_pv;
}

int Building::getMaxPV() const
{
	return m_maxPV;
}

bool Building::isAlive() const
{
	return m_pv > 0;
}

void Building::setPV(int pv)
{
	m_pv > m_maxPV ? m_pv = m_maxPV : (m_pv <= 0 ? m_pv = 0 : m_pv = pv);
}

void Building::setMaxPV(int maxPV)
{
	m_maxPV <= 0 ? m_maxPV = 0 : m_maxPV = maxPV;
}
