/*!
	\file game.cpp
	\brief definition of Game's methods
	\author Friday
*/

#include "Game.hpp"

namespace Game_n {

	Game::Game()
		:state(Enums::State::Idle)
	{}
	
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

	void Game::queueBuilding(Enums::Buildings codeBuilding, uint64_t keyBuilding) {
		//Queuing buildings
	}

	void Game::queueUnit(Enums::Units codeUnit, uint64_t keyBuilding) {
		//Queuing units
	}

	void Game::queueOpti(Enums::Opti codeOpti, uint64_t keyBuilding) {
		//Queuing opti
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

	// !!!!! Erreur avec l'utilisation de mBuildings et mQueueBuildings (it) lors de l'affectation (typage)
	void Game::upQueues() {
		for (QMap<Building*, int>::iterator it = mQueueBuildings.begin(); it != mQueueBuildings.end(); it++) {
			it.value()--;
			if (!it.value()) 
				mBuildings[mBuildings.end().key() + 1] = *it.key();
		}

		for (QMap<Unit*, int>::iterator it = mQueueUnits.begin(); it != mQueueUnits.end(); it++) {
			it.value()--;
			if (!it.value())
				mUnits[mUnits.end().key() + 1] = it.key();
		}

		for (QMap<Research*, int>::iterator it = mQueueResearchs.begin(); it != mQueueResearchs.end(); it++) {
			it.value()--;
			if (!it.value())
				// !!!!! Deuxième paramètre doit être de type Game_n::Player& et non Game_n::Research& (*it.key() étant de type Game_n::Research&).
				//createOpti(*it.key(), *it.key());
				;
		}
	}

	void Game::end() {
		//check end of game
	}
}
