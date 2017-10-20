/*!
	\file handler.cpp
	\brief handle functions definition
	\author Friday
*/

#include "CommunicationProtocols/Messages.hpp"
#include "ServerSide/Serverside.h"
#include "Handler.h"

using namespace Network::Messages;

Base handle(ServerSide *s, Base msg) {
	if (msg.is<UserInfo>()) return handle(s, msg.as<UserInfo>());
	if (msg.is<CreateGame>()) return handle(s, msg.as<CreateGame>());
	if (msg.is<JoinGame>()) return handle(s, msg.as<JoinGame>());
	if (msg.is<StartGame>()) return handle(s, msg.as<StartGame>());
	if (msg.is<SelectRace>()) return handle(s, msg.as<SelectRace>());
}

Base handle(ServerSide *s,const UserInfo *msg){
	if(s->verifyIdentity(msg->mPseudo,msg->mPasswd)){
		s->addPlayer(msg->idFrom,msg->mPseudo);
		return Accept(Base::Result::Success);
	}//s->verifyIdentity(msg.pseudo,msg.mdp)
	return Accept(Base::Result::Fail);
}

Base handle(ServerSide *s,const CreateGame *msg){
	if(msg->result==Base::Result::Success){
		try{
            Game_n::Game* newGame = s->addGame();
			s->joinGame(s->getPlayer(msg->idFrom), newGame);
			return CreateGame(*msg);
		}
		catch(int e){
			return CreateGame(Base::Result::Fail);
		}
	}//msg.result==Base::Result::Success
	return CreateGame(*msg);
}

Base handle(ServerSide *s,const JoinGame *msg){
	if(msg->result==Base::Result::Success){
		try{
			s->joinGame(s->getPlayer(msg->idFrom), s->getNotFull());
			return JoinGame(*msg);
		}
		catch(int e){
			return JoinGame(Base::Result::Fail);
		}
	}//msg.result==Base::Result::Success
	return JoinGame(*msg);
}

Base handle(ServerSide *s, const StartGame *msg){
	if(msg->result==Base::Result::Success){
		try{
            Game_n::Game* game = s->getGame(s->getPlayer(msg->idFrom));
			if(s->readyToStart(game)){
				s->startGame(game);
				return StartGame(*msg);
			}
			else{// !s->readyToStart(game)
				return StartGame(Base::Result::Fail);
			}//s->readyToStart(game)
		}
		catch(int e){
			return StartGame(Base::Result::Fail);
		}
	}//msg.Result==Base::Result::Success
	return StartGame(*msg);
}

Base handle(ServerSide *s, const SelectRace *msg){
	s->changeRace(s->getGame(s->getPlayer(msg->idFrom)), s->getPlayer(msg->idFrom), msg->m_codeRace);
	return SelectRace(*msg);
}

Base handle(ServerSide *s, const SelectColor *msg){
	s->changeColor(s->getGame(s->getPlayer(msg->idFrom)), s->getPlayer(msg->idFrom), msg->m_codeColor);
	return SelectColor(*msg);
}

Base handle(ServerSide *s, const MoveUnit *msg){
	s->moveUnit(s->getGame(s->getPlayer(msg->idFrom)),msg->m_hashCodeUnit,msg->m_x,msg->m_y);
	return MoveUnit(*msg);
}

Base handle(ServerSide *s, const QueueBuilding *msg){
	s->queueBuilding(s->getGame(s->getPlayer(msg->idFrom)),msg->m_codeBuilding,msg->m_hashCodeBuilding);
	return QueueBuilding(*msg);
}

Base handle(ServerSide *s, const QueueUnit *msg){
	s->queueUnit(s->getGame(s->getPlayer(msg->idFrom)), msg->m_codeUnit, msg->m_hashCodeBuilding);
	return QueueUnit(*msg);
}

Base handle(ServerSide *s, const QueueOpti *msg){
	s->queueOpti(s->getGame(s->getPlayer(msg->idFrom)), msg->m_codeOpti, msg->m_hashCodeBuilding);
	return QueueOpti(*msg);
}

Base handle(ServerSide *s, const Attack *msg){
	s->attack(s->getGame(s->getPlayer(msg->idFrom)), msg->m_hashCodeAttacker, msg->m_hashCodeTarget);
	return Attack(*msg);
}

Base handle(ServerSide *s, const Quit *msg){
    Game_n::Game* game = s->getGame(s->getPlayer(msg->idFrom));
	s->setGameEnd(game);
	return Quit(s->ended(game) ? Quit::Status::Ended : Quit::Status::NotEnded);
}
