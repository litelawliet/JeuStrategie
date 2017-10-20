#ifndef HANDLER_H
#define HANDLER_H
/*!
	\file handler.h
	\brief handle functions definition
	\author Friday
*/
#include "ServerSide/Serverside.h"
#include "../CommunicationProtocols/Sockets.hpp"
#include "../CommunicationProtocols/TCP/Server.hpp"
#include "../CommunicationProtocols/Messages.hpp"
#include "../CommunicationProtocols/Errors.hpp"
#include "../Game/Game.hpp"

using namespace Network;
using namespace Network::Messages;

Base handle(ServerSide *s, Base msg);

/*!
	\brief handle UserInfo message
	\param[in] msg of type UserData
	\return an Accept message
 */
Base handle(ServerSide *s,const UserInfo *msg);

/*!
    \brief handle a CreateGame_n
    \param[in] msg of type CreateGame_n
	\return a message
 */
Base handle(ServerSide *s,const CreateGame *msg);

/*!
	\brief handle a JoinGa�e
    \param[in] msg of type JoinGame_n
	\return a message
*/
Base handle(ServerSide *s,const JoinGame *msg);

/*!
    \brief handle a StartGame_n
    \param[in] msg of type StartGame_n
	\return a message
*/
Base handle(ServerSide *s,const StartGame *msg);

/*!
	\brief handle a SelectRace
	\param[in] msg of type SelectRace
	\return a message
*/
Base handle(ServerSide *s,const SelectRace *msg);

/*!
	\brief handle a SelectColor
	\param[in] msg of type SelectColor
	\return a message
*/
Base handle(ServerSide *s,const SelectColor *msg);

/*!
	\brief handle a MoveUnit
	\param[in] msg of type MoveUnit
	\return a message
*/
Base handle(ServerSide *s,const MoveUnit *msg);

/*!
	\brief handle a QueueBuilding
	\param[in] msg of type QueueBuilding
	\return a message
*/
Base handle(ServerSide *s,const QueueBuilding *msg);

/*!
	\brief handle a QueueUnit
	\param[in] msg of type QueueUnit
	\return a message
*/
Base handle(ServerSide *s,const QueueUnit *msg);

/*!
	\brief handle a QueueOpti
	\param[in] msg of type QueueOpti
	\return a message
*/
Base handle(ServerSide *s,const QueueOpti *msg);

/*!
	\brief handle a Attack
	\param[in] msg of type Attack
	\return a message
*/
Base handle(ServerSide *s,const Attack *msg);

/*!
	\brief handle a Quit
	\param[in] msg of type Quit
	\return a message
*/
Base handle(ServerSide *s,const Quit *msg);

#endif // HANDLER_H
