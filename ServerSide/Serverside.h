#ifndef SERVERSIDE_H
#define SERVERSIDE_H

/*!
	\file Serverside.h
	\brief definition of Server and ServerImpl methods
	\author Friday
*/

#include "../CommunicationProtocols/TCP/Server.hpp"
#include "CommunicationProtocols\TCP\Client.hpp"
#include "../Game/Enums.hpp"
#include "../Game/Game.hpp"

#include <vector>


class ServerSide
{
	public:
		ServerSide(Network::TCP::Server *s)
			: mServer(s)
		{}
		~ServerSide();
		void update();
		Game::Game* addGame();
		void addPlayer(uint64_t client, std::string pseudo);
		bool verifyIdentity(std::string pseudo, std::string pwd);
		void joinGame(Game::Player* player, Game::Game* game);
		Game::Player* getPlayer(uint64_t client);
		Game::Game* getNotFull();
		Game::Game* getGame(Game::Player* player);
		bool readyToStart(Game::Game* game);
		void startGame(Game::Game* game);
		void changeRace(Game::Game* game, Game::Player* player, Game::Enums::Races race);
		void changeColor(Game::Game* game, Game::Player* player, Game::Enums::Colors color);
		void moveUnit(Game::Game* game, uint64_t hashCodeUnit, int x, int y);
		void queueBuilding(Game::Game* game, Game::Enums::Buildings codeBuilding, uint64_t hashCodeBuilding);
		void queueUnit(Game::Game* game, Game::Enums::Units codeUnit, uint64_t hashCodeBuilding);
		void queueOpti(Game::Game* game, Game::Enums::Opti codeOpti, uint64_t hashCodeBuilding);
		void attack(Game::Game* game, uint64_t hashCodeAttacker, uint64_t hashCodeTarget);
		void setGameEnd(Game::Game* game);
		bool ended(Game::Game* game);


	private:
		Network::TCP::Server* mServer;
		std::vector<Game::Game*> mGames;
		std::vector<Game::Player*> mPlayers;

};

#endif // SERVERSIDE_H
