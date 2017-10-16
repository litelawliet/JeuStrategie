/*!
	\file ServerSide.hpp
	\brief declaration of classe ServerSide
	\author Friday
*/

#include "Serverside.h"

ServerSide::~ServerSide(){
	delete mServer;
	delete mSQL;
}

void ServerSide::update(){
	mServer->update();//receive and send messages
    for (auto game : mGames) {
        game->moveUnits();//move all units
        game->setTargets();//set all targets
        game->end();//check all ends
	}
}

Game_n::Game* ServerSide::addGame(){
    mGames.push_back(new Game_n::Game());
    return mGames.at(mGames.size()-1);
}

void ServerSide::addPlayer(uint64_t client, std::string pseudo){
    mPlayers.push_back(new Game_n::Player(client,pseudo));
}

bool ServerSide::verifyIdentity(std::string pseudo, std::string pwd){
	std::string squery = "SELECT player.id FROM player WHERE " + pseudo + "=player.pseudo AND " + pwd + "=player.password";
	QSqlQuery query(*mSQL);
	query.exec(QString(squery.c_str()));
	if (!query.next()) return false;
	return true;
}

void ServerSide::joinGame(Game_n::Player* player, Game_n::Game* game){
    game->addPlayer(player);
}

Game_n::Player* ServerSide::getPlayer(uint64_t idClient){
	for(auto player : mPlayers){
		if( mServer->get(player->getClient()) == mServer->get(idClient)) return player;
	}
	return nullptr;
}

Game_n::Game* ServerSide::getNotFull(){
    for(auto game : mGames){
        if(!game->full()) return game;
	}
	return nullptr;
}

Game_n::Game* ServerSide::getGame(Game_n::Player* player){
    for (auto game : mGames) {
        if (!game->contains(player)) return game;
	}
	return nullptr;
}

bool ServerSide::readyToStart(Game_n::Game* game){
    return game->full();
}

void ServerSide::startGame(Game_n::Game* game){
    game->start();
}

void ServerSide::changeRace(Game_n::Game* game, Game_n::Player* player, Game_n::Enums::Races race){
    game->changeRace(player,race);
}

void ServerSide::changeColor(Game_n::Game* game, Game_n::Player* player, Game_n::Enums::Colors color){
    game->changeColor(player,color);
}

void ServerSide::moveUnit(Game_n::Game* game, uint64_t hashCodeUnit, int x, int y){
    game->moveUnit(hashCodeUnit,x,y);
}

void ServerSide::queueBuilding(Game_n::Game* game, Game_n::Enums::Buildings codeBuilding, uint64_t hashCodeBuilding){
    game->queueBuilding(codeBuilding, hashCodeBuilding);
}

void ServerSide::queueUnit(Game_n::Game* game, Game_n::Enums::Units codeUnit, uint64_t hashCodeBuilding){
    game->queueUnit(codeUnit, hashCodeBuilding);
}

void ServerSide::queueOpti(Game_n::Game* game, Game_n::Enums::Opti codeOpti, uint64_t hashCodeBuilding){
    game->queueOpti(codeOpti, hashCodeBuilding);
}

void ServerSide::attack(Game_n::Game* game, uint64_t hashCodeAttacker, uint64_t hashCodeTarget){
    game->attack(hashCodeAttacker, hashCodeTarget);
}

void ServerSide::setGameEnd(Game_n::Game* game){
    game->end();
}

bool ServerSide::ended(Game_n::Game* game){
    return game->getState() == Game_n::Game::State::End;
}
