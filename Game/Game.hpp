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
namespace Game {

	/*!
		\class Player Game.hpp Game
		\brief to play games
	*/
	class Player {
		private:
			Network::TCP::Client client;
	};

	/*!
		\class Game Game.hpp Game
		\brief regroups players in a game
	*/
	class Game {
		public : 

			/*!
				\enum State
				
				\brief different states of game
			*/
			enum class State {
				Idle,/*!< waiting players*/
				Start,/*!< in progress*/
				End,/*!< end of match*/
			};
			/*!
				\brief add player to game

				\param[in] p of type Player : player to add
			*/
			void addPlayer(Player p);
			void startGame();

		private:
			std::map<uint64_t, Player> players;/*!< list of players in game*/
			State state;/*!< game state*/
	};
}