#ifndef SERVERSIDE_H
#define SERVERSIDE_H

/*!
	\file Serverside.h
	\brief definition of Server and ServerImpl methods
	\author Friday
*/

#include "../CommunicationProtocols/TCP/Server.hpp"
#include "../Game/Enums.hpp"
#include "../Game/Game.hpp"

#include <map>


class ServerSide
{
	public:
		ServerSide(Server *s)
			: mServer(&s)
		{}
		~ServerSide();
		void update();
		uint64_t addGame();
		void addPlayer(uint64_t idClient);
		bool testIdentity();
		void joinGame(uint64_t idPlayer, uint64_t idGame);
		uint64_t getPlayer(uint64_t idClient);
		uint64_t getNotFull();
		uint64_t getGame(uint64_t idPlayer);
		bool readyToStart(uint64_t idGame);
		void startGame(uint64_t idGame);
		void changeRace(uint64_t idGame, uint64_t idPlayer, Game::Enums::Races race);
		void changeColor(uint64_t idGame, uint64_t idPlayer, Game::Enums::Colors color);
		void moveUnit(uint64_t idGame, int hashCodeUnit, int x, int y);
		void queueBuilding(uint64_t idGame, Game::Enums::Buildings codeBuilding, int hashCodeBuilding);
		void queueUnit(uint64_t idGame, Game::Enums::Units codeUnit, int hashCodeBuilding);
		void queueOpti(uint64_t idGame, Game::Enums::Opti codeOpti, int hashCodeBuilding);
		void attack(uint64_t idGame, int hashCodeAttacker, int hashCodeTarget);
		void setGameEnd(uint64_t idGame);
		bool ended(uint64_t idGame);


	private:
		Server* mServer;
		std::map<uint64_t, Game> mGames;
		std::map<uint64_t, Player> mPlayers;

};

#endif // SERVERSIDE_H
