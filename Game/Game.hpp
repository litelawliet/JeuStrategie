#pragma once

/*!
	\file Game.hpp
	\brief declaration of classes Game and Player
	\author Friday
*/
#include <map>

#include "../CommunicationProtocols/TCP/Client.hpp"

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
		public:
			Player(uint64_t idClient, std::string pseudo);
			uint64_t getClient(){return mIdClient;}
			uint64_t getGame(){return mIdGame;}
			Enums::Colors getColor(){return mColor;}
			Enums::Races getRace(){return mRace;}
			std::string getPseudo(){return pseudo;}
		private:
			std::string pseudo;
			uint64_t mIdClient;
			uint64_t mIdGame;
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

			static const byte nbPlayerMax = 2;

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
			State getState(){return State;}
			bool full();
			void changeRace(Player *p,Enums::Races race);
			void changeColor(Player *p, Enums::Colors color);
			void moveUnit(uint64_t keyUnit, int x, int y);
			void queueBuilding(Enums::Buildings codeBuilding, uint64_t keyBuilding);
			void queueUnit(Enums::Units codeUnit, uint64_t keyBuilding);
			void queueOpti(Enums::Opti codeOpti, uint64_t keyBuilding);
			void createBuilding();
			void createUnit();
			void createOpti();
			void attack(uint64_t keyAttacker, uint64_t keyTarget);
			void end();

		private:
			std::vector<Player*> players;/*!< list of players in game*/
			std::map<uint64_t, Unit> units;
			std::map<uint64_t, Buildings> buildings;
			State state;/*!< game state*/
	};
}
