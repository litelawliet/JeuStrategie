#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Enums.hpp"

namespace Game_n {
/*!
\class Player Game.hpp Game
\brief to play Games
*/
class Player {

    friend class Game;
    class Game;
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
        Game* mGame;
        uint64_t mClient;
        std::string mPseudo;
        Enums::Colors mColor;
        Enums::Races mRace;
    };
}

#endif // PLAYER_HPP
