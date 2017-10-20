/*!
	\file game.cpp
	\brief definition of Game's methods
	\author Friday
*/

#include "Game.hpp"
#include "player.hpp"

namespace Game_n {

	void Game::addPlayer(Player *p) {
		mPlayers.push_back(p);
	}

	void Game::start() {
		state = State::Start;
	}

	bool Game::contains(Player *player) const{
		for (auto p : mPlayers) {
			if (p == player) return true;
		}

		return false;
	}

	bool Game::full() {
		return nbPlayerMax == mPlayers.size();
	}

	void Game::changeRace(Player *p, Enums::Races race) {
		p->mRace = race;
	}

	void Game::changeColor(Player *p, Enums::Colors color) {
		p->mColor = color;
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

	void Game::createOpti(Research research, Player* owner) {
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
			if (!it->second) mBuildings[mBuildings.end()->first+1] = it->first;
		}

		for (auto it = mQueueUnits.begin(); it != mQueueUnits.end(); it++) {
			it->second--;
			if (!it->second) mUnits[mUnits.end()->first + 1] = it->first;
		}

		for (auto it = mQueueResearchs.begin(); it != mQueueResearchs.end(); it++) {
			it->second--;
			if (!it->second) createOpti(it->first, it->first.getOwner());
		}
	}

	void Game::end() {
		//check end of game
	}
}
