/*!
	\file game.cpp
	\brief definition of Game's methods
	\author Friday
*/

#include "Game.hpp"

namespace Game {
	void Game::addPlayer(Player *p) {
		mPlayers.push_back(p);
	}

	void Game::start() {
		//thread
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
		//AI
	}

	void Game::queueBuilding(Enums::Buildings codeBuilding, uint64_t keyBuilding) {

	}

	void Game::queueUnit(Enums::Units codeUnit, uint64_t keyBuilding) {

	}

	void Game::queueOpti(Enums::Opti codeOpti, uint64_t keyBuilding) {

	}

	void Game::createBuilding() {

	}

	void Game::createUnit() {

	}

	void Game::createOpti() {

	}

	void Game::attack(uint64_t keyAttacker, uint64_t keyTarget) {

	}

	void Game::end() {

	}
}