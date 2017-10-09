#ifndef GAME_HPP
#define GAME_HPP

/*!
	\file Game.hpp
	\brief declaration of classes Game and Player
	\author Friday
*/
#include <map>
#include <vector>

#include "../CommunicationProtocols/TCP/Client.hpp"

#include "UnitsAndBuildings/UnitsAndBuildings/BuildingsHeaders.h"
#include "UnitsAndBuildings/UnitsAndBuildings/UnitsHeaders.h"
#include "UnitsAndBuildings/UnitsAndBuildings/ResearchHeaders.h"

#include "Enums.hpp"

/*!
	\namespace Game
	\brief contains all game's things
*/
namespace Game{

	/*!
		\class Player Game.hpp Game
		\brief to play games
	*/
	class Player { 

		friend class Game;

		public:
			Player(uint64_t client, std::string pseudo)
				: mClient(client)
				, mPseudo(pseudo)
			{}
			uint64_t getClient(){return mClient;}
			Game* getGame(){return mGame;}
			Enums::Colors getColor(){return mColor;}
			Enums::Races getRace(){return mRace;}
			std::string getPseudo(){return mPseudo;}
		private:
			std::string mPseudo;
			uint64_t mClient;
			Game* mGame;
			Enums::Colors mColor;
			Enums::Races mRace;
	};

	/*!
		\class Game Game.hpp Game
		\brief regroups players in a game
	*/
	class Game{

			friend class Player;

		public : 

			static const size_t nbPlayerMax = 2;

			/*!
				\enum State
				
				\brief different states of game
			*/
			enum class State {
				Idle,/*!< waiting players*/
				Start,/*!< in progress*/
				End,/*!< end of match*/
			};

			Game()
				:state(State::Idle)
			{}

			/*!
				\brief add player to game

				\param[in] p of type Player : player to add
			*/
			void addPlayer(Player *p);
			void start();
			bool contains(Player *player) const ;
			State getState(){return state;}
			bool full();
			void changeRace(Player *p,Enums::Races race);
			void changeColor(Player *p, Enums::Colors color);
			void moveUnit(uint64_t keyUnit, int x, int y);
			void moveUnits();
			void queueBuilding(Enums::Buildings codeBuilding, uint64_t keyBuilding);
			void queueUnit(Enums::Units codeUnit, uint64_t keyBuilding);
			void queueOpti(Enums::Opti codeOpti, uint64_t keyBuilding);
			void createBuilding();
			void createUnit();
			void createOpti();
			void attack(uint64_t keyAttacker, uint64_t keyTarget);
			void setTargets();
			void end();

		private:
			std::vector<Player*> mPlayers;/*!< list of players in game*/
			std::map<uint64_t, Unit&> mUnits;
			std::map<uint64_t, Building&> mBuildings;
			State state;/*!< game state*/
	};
}

#endif