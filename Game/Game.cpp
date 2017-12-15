/*!
	\file game.cpp
	\brief definition of Game's methods
	\author Friday
*/

#include "Game.hpp"

namespace Game_n {

	Game::Game()
		:state(Enums::State::Idle)
	{
		idBuilding = 0;
		idUnit = 0;
		idOpti = 0;
	}
	
	Game::~Game() {}

	void Game::addPlayer(Player* p) {
		mPlayers.push_back(p);
	}

	void Game::start() {
		state = Enums::State::Start;
	}

	bool Game::contains(Player* player) const{
		for (auto p : mPlayers) {
			if (p == player) return true;
		}

		return false;
	}

	bool Game::full() {
		return NB_PLAYER_MAX == mPlayers.size();
	}

	void Game::changeRace(Player& p, Enums::Races race) {
		p.setRace(race);
	}

	void Game::changeColor(Player& p, Enums::Colors color) {
		p.setColor(color);
	}

	void Game::moveUnit(uint64_t keyUnit, int x, int y) {
	}

	void Game::moveUnits() {
		//AI
	}

	void Game::queueBuilding(Enums::Buildings codeBuilding) {
		Building* u;
		switch (codeBuilding) {
			case Enums::Buildings::CC:
				u = new Headquarter();
				break;
			case Enums::Buildings::CCS:
				u = new SecondaryHeadquarter();
				break;
			case Enums::Buildings::Supplying:
				u = new Refueling();
				break;
			case Enums::Buildings::Drill:
				u = new DrillingMachine();
				break;
			case Enums::Buildings::Factory:
				u = new Factory();
				break;
			case Enums::Buildings::Barrack:
				u = new Barrack();
				break;
			case Enums::Buildings::Armory:
				u = new Armory();
				break;
			case Enums::Buildings::Bunker:
				u = new Headquarter();
				break;
			case Enums::Buildings::Laboratory:
				u = new Laboratory();
				break;
			case Enums::Buildings::Barricade:
				u = new Headquarter();
				break;
			case Enums::Buildings::Wall:
				u = new Wall();
				break;
			case Enums::Buildings::Door:
				u = new Gate();
				break;
			case Enums::Buildings::GroundDefense:
				u = new GroundTurret();
				break;
			case Enums::Buildings::AirDefense:
				u = new AirTurret();
				break;
			case Enums::Buildings::Foundry:
				u = new Headquarter();
				break;
			case Enums::Buildings::CyberFactory:
				u = new CyberFactory();
				break;
			case Enums::Buildings::UltimateWeapon:
				u = new UltimateWeapon();
				break;
			case Enums::Buildings::Airport:
				u = new Airport();
				break;
		}
		mQueueBuildings[u] = u->getTimeQueue();
	}

	void Game::queueUnit(Enums::Units codeUnit) {
		Unit* u = nullptr;
		switch (codeUnit) {
			case Enums::Units::LightSoldier:
				u = new LightInfantry();
				break;
			case Enums::Units::HeavySoldier:
				u = new HeavyInfantry;
				break;
			case Enums::Units::CleaningSoldier:
				u = new CleaningInfantry();
				break;
			case Enums::Units::LightVehicle:
				u = new LightVehicle();
				break;
			case Enums::Units::HeavyVehicle:
				u = new HeavyVehicle();
				break;
			case Enums::Units::LightPlane:
				u = new LightAviation;
				break;
			case Enums::Units::HeavyPlane:
				u = new HeavyAviation();
				break;
			case Enums::Units::VCS:
				u = new Harvester();
				break;
			case Enums::Units::Medics:
				u = new Medic();
				break;
		}
		mQueueUnits[u] = u->getTimeQueue();
	}

	void Game::queueOpti(Enums::Opti codeOpti) {
		//:ah:
	}

	void Game::createBuilding() {
		//Creating building
	}

	void Game::createUnit() {
		//Creating unit
	}

	void Game::createOpti(Research& research, Player& owner) {
		//Creating opti
	}

	void Game::attack(uint64_t keyAttacker, uint64_t keyTarget) {
		//set target of attackers
	}

	void Game::setTargets() {
		//set targets of all units
	}

	void Game::upQueues() {
		for (auto it = mQueueBuildings.begin(); it != mQueueBuildings.end(); it++) {
			it->second--;
			if (it->second != 0) 
				mBuildings[mBuildings.end()->first + 1] = *(it->first);
		}

		for (auto it = mQueueUnits.begin(); it != mQueueUnits.end(); it++) {
			it->second--;
			if (it->second != 0)
				mUnits[mUnits.end()->first + 1] = *(it->first);
		}

		for (auto it = mQueueResearchs.begin(); it != mQueueResearchs.end(); it++) {
			it->second--;
			if (it->second != 0)
				createOpti(*(it->first),it->first->getOwner());
		}
	}

	void Game::end() {
		//check end of game
	}
}