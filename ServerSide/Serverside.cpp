/*!
	\file ServerSide.hpp
	\brief declaration of classe ServerSide
	\author Friday
*/

#include "Serverside.h"

ServerSide::~ServerSide(){
	delete mServer;
}

void ServerSide::update(){
	mServer->update();
}

Game::Game* ServerSide::addGame(){
	mGames.push_back(&(Game::Game()));
	return mGames.at(mGames.size()-1);
}

void ServerSide::addPlayer(uint64_t client, std::string pseudo){
	mPlayers.push_back(&(Game::Player(client,pseudo)));
}

bool ServerSide::verifyIdentity(std::string pseudo, std::string pwd){
	return true;
}

void ServerSide::joinGame(Game::Player* player, Game::Game* game){
	game->addPlayer(player);
}

Game::Player* ServerSide::getPlayer(uint64_t idClient){
	for(auto player : mPlayers){
		if( mServer->get(player->getClient()) == mServer->get(idClient)) return player;
	}
	return nullptr;
}

Game::Game* ServerSide::getNotFull(){
	for(auto game : mGames){
		if(!game->full()) return game;
	}
	return nullptr;
}

Game::Game* ServerSide::getGame(Game::Player* player){
	for (auto game : mGames) {
		if (!game->contains(player)) return game;
	}
	return nullptr;
}

bool ServerSide::readyToStart(Game::Game* game){
	return game->full();
}

void ServerSide::startGame(Game::Game* game){
	game->start();
}

void ServerSide::changeRace(Game::Game* game, Game::Player* player, Game::Enums::Races race){
	game->changeRace(player,race);
}

void ServerSide::changeColor(Game::Game* game, Game::Player* player, Game::Enums::Colors color){
	game->changeColor(player,color);
}

void ServerSide::moveUnit(Game::Game* game, uint64_t hashCodeUnit, int x, int y){
	game->moveUnit(hashCodeUnit,x,y);
}

void ServerSide::queueBuilding(Game::Game* game, Game::Enums::Buildings codeBuilding, uint64_t hashCodeBuilding){
	game->queueBuilding(codeBuilding, hashCodeBuilding);
}

void ServerSide::queueUnit(Game::Game* game, Game::Enums::Units codeUnit, uint64_t hashCodeBuilding){
	game->queueUnit(codeUnit, hashCodeBuilding);
}

void ServerSide::queueOpti(Game::Game* game, Game::Enums::Opti codeOpti, uint64_t hashCodeBuilding){
	game->queueOpti(codeOpti, hashCodeBuilding);
}

void ServerSide::attack(Game::Game* game, uint64_t hashCodeAttacker, uint64_t hashCodeTarget){
	game->attack(hashCodeAttacker, hashCodeTarget);
}

void ServerSide::setGameEnd(Game::Game* game){
	game->end();
}

bool ServerSide::ended(Game::Game* game){
	return game->getState() == Game::Game::State::End;
}
