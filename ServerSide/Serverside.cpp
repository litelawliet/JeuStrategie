/*!
	\file ServerSide.hpp
	\brief declaration of classe ServerSide
	\author Friday
*/

#include "Serverside.h"

ServerSide::~ServerSide(){
	delete *mServer;
	delete mGames;
	delete mPlayers;
}

void ServerSide::update(){
	mServer->update();
}

uint64_t ServerSide::addGame(){
	return mGames.insert(Game()).first;
}

void ServerSide::addPlayer(uint64_t idClient){
	mPlayers.insert(Player(mServer->get(idClient)));
}

bool ServerSide::testIdentity(){
	return true;
}

void ServerSide::joinGame(uint64_t idPlayer, uint64_t idGame){
	mGames.at(idGame).addPlayer(&(mPlayers.at(idPlayer)));
}

uint64_t ServerSide::getPlayer(uint64_t idClient){
	for(mPlayers::iterator it=mPlayers.begin(); it!=mPlayers.end(); it++){
		if(it.second.getClient()==mServer->get(idClient)) return it.first;
	}
	return NULL;
}

uint64_t ServerSide::getNotFull(){
	for(mGames::iterator it=mGames.begin(); it!=mGames.end(); it++){
		if(!it.second.full()) return it.first;
	}
	return NULL;
}

uint64_t ServerSide::getGame(uint64_t idPlayer){
	return getGame(mPlayers.at(idPlayer));
}

bool ServerSide::readyToStart(uint64_t idGame){
	return mGames.at(idGame).full();
}

void ServerSide::startGame(uint64_t idGame){
	mGames.at(idGame).start();
}

void ServerSide::changeRace(uint64_t idGame, uint64_t idPlayer, Game::Enums::Races race){
	mGames.at(idGame).changeRace(idPlayer,race);
}

void ServerSide::changeColor(uint64_t idGame, uint64_t idPlayer, Game::Enums::Colors color){
	mGames.at(idGame).changeColor(idPlayer,color);
}

void ServerSide::moveUnit(uint64_t idGame, uint64_t hashCodeUnit, int x, int y){
	mGames.at(idGame).moveUnit(hashCodeUnit,x,y);
}

void ServerSide::queueBuilding(uint64_t idGame, Game::Enums::Buildings codeBuilding, uint64_t hashCodeBuilding){
	mGames.at(idGame).queueBuilding(codeBuilding, hashCodeBuilding);
}

void ServerSide::queueUnit(uint64_t idGame, Game::Enums::Units codeUnit, uint64_t hashCodeBuilding){
	mGames.at(idGame).queueUnit(codeUnit, hashCodeBuilding);
}

void ServerSide::queueOpti(uint64_t idGame, Game::Enums::Opti codeOpti, uint64_t hashCodeBuilding){
	mGames.at(idGame).queueOpti(codeOpti, hashCodeBuilding);
}

void ServerSide::attack(uint64_t idGame, uint64_t hashCodeAttacker, uint64_t hashCodeTarget){
	mGames.at(idGame).attack(hashCodeAttacker, hashCodeTarget);
}

void ServerSide::setGameEnd(uint64_t idGame){
	mGames.at(idGame).end();
}

bool ServerSide::ended(uint64_t idGame){
	return mGames.at(idGame).getState() == Game::Game::State::End;
}
