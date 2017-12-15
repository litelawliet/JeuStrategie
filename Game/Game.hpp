#ifndef GAME_HPP
#define GAME_HPP

/*!
    \file Game.hpp
    \brief declaration of classes Game and Player
	\author Friday
*/

#include <vector>
#include <map>

#include "CommunicationProtocols/TCP/Client.hpp"

#include "UnitsAndBuildings/Entities.h"

#include "Enums.hpp"
#include "Player.hpp"

/*!
    \namespace Game_n
    \brief contains all Game's things
*/

namespace Game_n {
	/*!
		\class Game Game.hpp Game
		\brief regroups players in a Game
	*/
    class Game {
        public :
            static const size_t NB_PLAYER_MAX = 2;

			Game();
			~Game();

            /*!
                \brief add player to Game

                \param[in] p of type Player : player to add
            */
            void addPlayer(Player *p);
            void start();
            bool contains(Player *player) const ;
            Enums::State getState(){return state;}
            bool full();
            void changeRace(Player& p,Enums::Races race);
            void changeColor(Player& p, Enums::Colors color);
            void moveUnit(uint64_t keyUnit, int x, int y);
            void moveUnits();
            void queueBuilding(Enums::Buildings codeBuilding);
            void queueUnit(Enums::Units codeUnit);
            void queueOpti(Enums::Opti codeOpti);
            void createBuilding();
            void createUnit();
            void createOpti(Research& research, Player& owner);
            void attack(uint64_t keyAttacker, uint64_t keyTarget);
            void setTargets();
            void end();
			void upQueues();

        private:
            std::vector<Player*> mPlayers;/*!< list of players in Game*/
            std::map<uint64_t, Unit&> mUnits;
            std::map<uint64_t, Building&> mBuildings;
			std::map<Building*, int> mQueueBuildings;
			std::map<Unit*, int> mQueueUnits;
			std::map<Research*, int> mQueueResearchs;
			Enums::State state;
			uint64_t idBuilding;
			uint64_t idUnit;
			uint64_t idOpti;
    };

}

#endif
