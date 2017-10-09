/*!
	\file handler.cpp
	\brief handle functions definition
	\author Friday
*/

#include "CommunicationProtocols\Messages.hpp"
#include "ServerSide\Serverside.h"
#include "handler.h"

using namespace Network::Messages;

Base handle(ServerSide *s,UserInfo msg){
	if(s->verifyIdentity(msg.mPseudo,msg.mPasswd)){
		s->addPlayer(msg.idFrom,msg.mPseudo);
		return Accept(Base::Result::Success);
	}//s->verifyIdentity(msg.pseudo,msg.mdp)
	return Accept(Base::Result::Fail);
}

Base handle(ServerSide *s,CreateGame msg){
	if(msg.result==Base::Result::Success){
		try{
			Game::Game* newGame = s->addGame();
			s->joinGame(s->getPlayer(msg.idFrom), newGame);
			return msg;
		}
		catch(int e){
			return CreateGame(Base::Result::Fail);
		}
	}//msg.result==Base::Result::Success
	return msg;
}

Base handle(ServerSide *s,JoinGame msg){
	if(msg.result==Base::Result::Success){
		try{
			s->joinGame(s->getPlayer(msg.idFrom), s->getNotFull());
			return msg;
		}
		catch(int e){
			return JoinGame(Base::Result::Fail);
		}
	}//msg.result==Base::Result::Success
	return msg;
}

Base handle(ServerSide *s,StartGame msg){
	if(msg.result==Base::Result::Success){
		try{
			Game::Game* game = s->getGame(s->getPlayer(msg.idFrom));
			if(s->readyToStart(game)){
				s->startGame(game);
				return msg;
			}
			else{// !s->readyToStart(game)
				return StartGame(Base::Result::Fail);
			}//s->readyToStart(game)
		}
		catch(int e){
			return StartGame(Base::Result::Fail);
		}
	}//msg.Result==Base::Result::Success
	return msg;
}

Base handle(ServerSide *s,SelectRace msg){
	s->changeRace(s->getGame(s->getPlayer(msg.idFrom)), s->getPlayer(msg.idFrom), msg.m_codeRace);
	return msg;
}

Base handle(ServerSide *s,SelectColor msg){
	s->changeColor(s->getGame(s->getPlayer(msg.idFrom)), s->getPlayer(msg.idFrom), msg.m_codeColor);
	return msg;
}

Base handle(ServerSide *s,MoveUnit msg){
	s->moveUnit(s->getGame(s->getPlayer(msg.idFrom)),msg.m_hashCodeUnit,msg.m_x,msg.m_y);
	return msg;
}

Base handle(ServerSide *s,QueueBuilding msg){
	s->queueBuilding(s->getGame(s->getPlayer(msg.idFrom)),msg.m_codeBuilding,msg.m_hashCodeBuilding);
	return msg;
}

Base handle(ServerSide *s,QueueUnit msg){
	s->queueUnit(s->getGame(s->getPlayer(msg.idFrom)), msg.m_codeUnit, msg.m_hashCodeBuilding);
	return msg;
}

Base handle(ServerSide *s,QueueOpti msg){
	s->queueOpti(s->getGame(s->getPlayer(msg.idFrom)), msg.m_codeOpti, msg.m_hashCodeBuilding);
	return msg;
}

Base handle(ServerSide *s,Attack msg){
	s->attack(s->getGame(s->getPlayer(msg.idFrom)), msg.m_hashCodeAttacker, msg.m_hashCodeTarget);
	return msg;
}

Base handle(ServerSide *s,Quit msg){
	Game::Game* game = s->getGame(s->getPlayer(msg.idFrom));
	s->setGameEnd(game);
	return Quit(s->ended(game) ? Quit::Status::Ended : Quit::Status::NotEnded);
}
