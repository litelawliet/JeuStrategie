#ifndef SERVERSIDE_H
#define SERVERSIDE_H

/*!
	\file Serverside.h
	\brief definition of Server and ServerImpl methods
	\author Friday
*/

#include "CommunicationProtocols/Sockets.hpp"

#include <QtSql/qsqldatabase.h>
#include <QtSql/qsqlquery.h>
#include <QtSql/qtsqlglobal.h>
#include <qstring.h>

#include "../CommunicationProtocols/TCP/Server.hpp"
#include "CommunicationProtocols/TCP/Client.hpp"
#include "../Game/Enums.hpp"
#include "../Game/Game.hpp"

#include <vector>


class ServerSide
{
	public:
		ServerSide(Network::TCP::Server *s, QSqlDatabase *sql)
			: mServer(s)
			, mSQL(sql)
		{}
        ServerSide(Network::TCP::Server *s) :
            mServer(s)
        {

        }
		~ServerSide();

		/*!
			\brief update server and games
		*/
		void update();

		/*!
			\brief create a new game
			\return added game of type Game*
		*/
        Game_n::Game* addGame();

		/*!
			\brief create a new player
			
			\param[in] client of type uint64_t : client id
			\param[in] pseudo of type std::string : player's pseudo
		*/
		void addPlayer(uint64_t client, std::string pseudo);

		/*!
			\brief verify if a player is registered in the database

			\param[in] pseudo of type std::string : player's pseudo
			\param[in] pwd of type std::string : player's password

			\return true if registered, false otherwise
		*/
		bool verifyIdentity(std::string pseudo, std::string pwd);

		/*!
			\brief allow a player to join a game

			\param[in] player of type Player* : player who wants to join
			\param[in] game of type Game* : game to join
		*/
        void joinGame(Game_n::Player* player, Game_n::Game* game);

		/*!
			\brief get player by his client identifier

			\param[in] client of type uint64_t : client id
			
			\return a Player* or nullptr
		*/
        Game_n::Player* getPlayer(uint64_t client);

		/*!
			\brief find the first non-full game available

			\return a Game* or nullptr
		*/
        Game_n::Game* getNotFull();

		/*!
			\brief get a game by its players

			\param[in] player of type Player*

			\return a Game* or nullptr
		*/
        Game_n::Game* getGame(Game_n::Player* player);

		/*!
			\brief say if a game is ready to start

			\param[in] game of type Game*

			\return true if ready to start, false otherwise
		*/
        bool readyToStart(Game_n::Game* game);

		/*!
			\brief start the game

			\param[in] game of type Game* : game to start
		*/
        void startGame(Game_n::Game* game);

		/*!
			\brief change a player's race

			\param[in] game of type Game* : selected game
			\param[in]player of type Player* : selected player
            \param[in] race of type Game_n::Enums::Races : new race
		*/
        void changeRace(Game_n::Game* game, Game_n::Player* player, Game_n::Enums::Races race);

		/*!
			\brief change a player's color

			\param[in] game of type Game* : selected game
			\param[in]player of type Player* : selected player
            \param[in] color of type Game_n::Enums::Colors : new color
		*/
        void changeColor(Game_n::Game* game, Game_n::Player* player, Game_n::Enums::Colors color);

		/*!
			\brief update unit's arrival

			\param[in] game of type Game* : selected game
			\param[in] hashCodeUnit of type uint64_t : selected unit
			\param[in] x of type int : new arrival x
			\param[in] y of type int : new arrival y
		*/
        void moveUnit(Game_n::Game* game, uint64_t hashCodeUnit, int x, int y);

		/*!
			\brief queue a new building
			
			\param[in] game of type Game* : selected game
            \param[in] codeBuilding of type Game_n::Enums::Buildings : building to queue
			\param[in] hashCodeBuilding of type uint64_t : queuing building
		*/
        void queueBuilding(Game_n::Game* game, Game_n::Enums::Buildings codeBuilding, uint64_t hashCodeBuilding);

		/*!
			\brief queue a new unit

			\param[in] game of type Game* : selected game
            \param[in] codeUnit of type Game_n::Enums::Units : unit to queue
			\param[in] hashCodeBuilding of type uint64_t : queuing building
		*/
        void queueUnit(Game_n::Game* game, Game_n::Enums::Units codeUnit, uint64_t hashCodeBuilding);

		/*!
			\brief queue a new opti

			\param[in] game of type Game* : selected game
            \param[in] codeOpti of type Game_n::Enums::Opti : opti to queue
			\param[in] hashCodeBuilding of type uint64_t : queuing building
		*/
        void queueOpti(Game_n::Game* game, Game_n::Enums::Opti codeOpti, uint64_t hashCodeBuilding);

		/*!
			\brief update a target

			\param[in] game of type Game* : selected game
			\param[in] hashCodeAttacker of type uint64_t : selected attacker
			\param[in] hashCodeTarget of type uint64_t : selected target
		*/
        void attack(Game_n::Game* game, uint64_t hashCodeAttacker, uint64_t hashCodeTarget);

		/*!
			\brief set end of game

			\param[in] game of type Game* : selected game
		*/
        void setGameEnd(Game_n::Game* game);

		/*!
			\brief tell if a game is ended

			\param[in] game of type Game* : selected game

			\return true if ended, false otherwise
		*/
        bool ended(Game_n::Game* game);


	private:
		Network::TCP::Server* mServer;/*!< Server protocols*/
		QSqlDatabase* mSQL;/*!< MySQL protocols*/
        std::vector<Game_n::Game*> mGames;/*!< list of games*/
        std::vector<Game_n::Player*> mPlayers;/*!< list of players*/

};

#endif // SERVERSIDE_H
