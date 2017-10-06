#ifndef HANDLER_H
#define HANDLER_H
/*!
	\file handler.h
	\brief handle functions definition
	\author Friday
*/
#include "../CommunicationProtocols/Sockets.hpp"
#include "../CommunicationProtocols/TCP/Server.hpp"
#include "../CommunicationProtocols/Messages.hpp"
#include "../CommunicationProtocols/Errors.hpp"
#include "../Game/Game.hpp"

using namespace Network;
using namespace Network::Messages;

/*!
	\brief handle UserInfo message
	\param[in] msg of type UserData
	\return an Accept message
 */
Base handle(ServerSide *s,UserInfo msg);

/*!
	\brief handle a CreateGame
	\param[in] msg of type CreateGame
	\return a message
 */
Base handle(ServerSide *s,CreateGame msg);

Base handle(ServerSide *s,JoinGame msg);

Base handle(ServerSide *s,StartGame msg);

Base handle(ServerSide *s,SelectRace msg);

Base handle(ServerSide *s,SelectColor msg);

Base handle(ServerSide *s,MoveUnit msg);

Base handle(ServerSide *s,QueueBuilding msg);

Base handle(ServerSide *s,QueueUnit msg);

Base handle(ServerSide *s,QueueOpti msg);

Base handle(ServerSide *s,Attack msg);

Base handle(ServerSide *s,Quit msg);

#endif // HANDLER_H
