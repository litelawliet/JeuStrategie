#ifndef GAME_HPP
#define GAME_HPP

/*!
    \file Game.hpp
    \brief declaration of classes Game and Player
	\author Friday
*/

#include <QMap>
#include <QVector>

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
            void queueBuilding(Enums::Buildings codeBuilding, uint64_t keyBuilding);
            void queueUnit(Enums::Units codeUnit, uint64_t keyBuilding);
            void queueOpti(Enums::Opti codeOpti, uint64_t keyBuilding);
            void createBuilding();
            void createUnit();
            void createOpti(Research& research, Player& owner);
            void attack(uint64_t keyAttacker, uint64_t keyTarget);
            void setTargets();
            void end();
			void upQueues();

        private:
            QVector<Player*> mPlayers;/*!< list of players in Game*/
            QMap<uint64_t, Unit*> mUnits;
            QMap<uint64_t, Building&> mBuildings;
			QMap<Building*, int> mQueueBuildings;
			QMap<Unit*, int> mQueueUnits;
			QMap<Research*, int> mQueueResearchs;
			Enums::State state;
    };

}

#endif
