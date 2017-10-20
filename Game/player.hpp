#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include "Enums.hpp"

namespace Game_n {
	/*!
	\class Player Game.hpp Game
	\brief to play Games
	*/
	class Player {
		public:
			Player(uint64_t client, std::string pseudo);
			~Player();
			// GET
			uint64_t getClient() const;
			Enums::Colors getColor() const;
			Enums::Races getRace() const;
			std::string getPseudo() const;
			
			// SET
			void setPseudo(std::string pseudo);
			void setRace(Enums::Races race);
			void setColor(Enums::Colors color);
			void setClient(uint64_t client);

		private:
			uint64_t mClient;
			std::string mPseudo;
			Enums::Colors mColor;
			Enums::Races mRace;
		};
}

#endif // PLAYER_HPP
