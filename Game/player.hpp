#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "Enums.hpp"

namespace Game_n {
	class Game;
	/*!
	\class Player Game.hpp Game
	\brief to play Games
	*/
	class Player {
		public:
			Player(uint64_t client, std::string pseudo)
				: mClient(client)
				, mPseudo(pseudo)
			{}
			~Player() {
				delete mGame;	
			}
			// GET
			uint64_t getClient() const { return mClient; }
			Enums::Colors getColor() const { return mColor; }
			Enums::Races getRace() const { return mRace; }
			std::string getPseudo() const { return mPseudo; }
			Game* getGame() const { return mGame; }
			
			// SET
			void setPseudo(std::string pseudo) { mPseudo = pseudo; }
			void setRace(Enums::Races race) { mRace = race; }
			void setColor(Enums::Colors color) { mColor = color; }
			void setClient(uint64_t client) { mClient = client; }
			void setGame(Game* g) { mGame = g; }

		private:
			uint64_t mClient;
			std::string mPseudo;
			Enums::Colors mColor;
			Enums::Races mRace;
			Game* mGame;
		};
}

#endif // PLAYER_HPP
