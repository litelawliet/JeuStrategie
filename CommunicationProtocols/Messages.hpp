#pragma once

/*!
	\file Messages.hpp
	\brief Messages' class definition
	\author Friday
*/

#ifndef	_WIN32
    #include <stdint.h>
#endif

#include <vector>
#include "../Game/Enums.hpp"
#include "Sockets.hpp"

typedef unsigned char uc;
typedef std::vector<unsigned char> vUc;

/*!
	\namespace Network
	\brief contains all network things
*/
namespace Network
{
	/*!
		\namespace Messages
		\brief contains all message things
	*/
	namespace Messages
	{
#define DECLARE_MESSAGE(name) friend class Base; static const Base::Type StaticType = Base::Type::name
		/*!
			\class Base Messages.hpp Messages
			\brief reference class for all messages
		*/
		class Base
		{
			public:
				/*!
					\brief assert if a message is an instance of a type M
					\return true if the message is an instance of type M, false otherwise
				*/
				template<class M>
				bool is() const { return mType == M::StaticType; }
				/*!
					\brief cast a message into another type M
					\return casted message
				*/
				template<class M>
				const M* as() const { return static_cast<const M*>(this); }

				sockaddr_in from;/*!< sender's address*/
				uint64_t idFrom;/*!< sender's id attributed by the server*/

			protected:
				/*!
					\enum Type
					\brief define each type of message
				*/
				enum class Type {
					Connection,/*!< connection message */
					Disconnection,/*!< disconnection message */
					UserData,/*!< to send user's datas*/
					CreateGame,/*!< to ask server to create a new game or inform client that's created well*/
					JoinGame,/*!< to ask server to join a created game or inform client that's joined well*/
					StartGame,/*!< when game's full, starts it or inform that's started*/
					SelectRace,/*!< to inform server about the race choice*/
					SelectColor,/*!< to inform server about the color choice*/
					MoveUnit,/*!< to move a single unit*/
					CreateUnit,/*!< to create a single unit*/
					CreateBuilding,/*!< to create a single building*/
					CreateOpti,/*!< to create a single optimisation*/
					QueueBuilding,/*!< to queue a single building in construction queue*/
					QueueUnit,/*!< to queue a single unit in unit queue*/
					QueueOpti,/*! to queue a single optimisation*/
					Attack,/*!< to attack*/
					DestroyUnit,/*!< to inform about a single unit's death*/
					DestroyBuilding,/*!< to inform about a single building's death*/
					EndGame,/*!< inform about the end and who win*/
					Quit,/*!< to stop the game*/
				};

				/*!
					\enum Result
					\brief tell about the action fail or success
				*/
				enum class Result {
					Success,
					Fail,
				};

				/*!
					\brief default constructor
					\param[in] type variable of type Type which is the message's type
				*/
				Base(Type type)
					: mType(type)
				{}

				/*!
					\brief to format messages into linear datas which can be send by TCP
					\return formated datas
				*/
				vUc toUserData() { return vUc{}; };
			private:
				Type mType;/*!< message's type*/
		};

		/*!
			\class Connection Messages.hpp Messages
			\brief to send when connecting
		*/
		class Connection : public Base
		{
			DECLARE_MESSAGE(Connection);
			public:
				/*!
					\enum Result
					\brief define connection's states
				*/
				enum class Result {
					Success,/*!< connection successful*/
					Failed,/*!< connection failed*/
				};
				/*!
					\brief default constructor
					\param[in] Result
				*/
				Connection(Result r)
					: Base(Type::Connection)
					, result(r)
				{}

				Result result;/*!< connection result*/
		};

		/*!	
			\class Disconnection Messages.hpp Messages
			\brief to send when disconnecting
		*/
		class Disconnection : public Base
		{
			DECLARE_MESSAGE(Disconnection);
			public:
				/*!
					\enum Reason
					\brief define different reasons about disconnection
				*/
				enum class Reason {
					Disconnected,/*!< Average reason*/
					Lost,/*!< error*/
				};

				/*!
					\brief default constructor
					\param[in] r type of Reason which is the reason of disconnection
				*/
				Disconnection(Reason r)
					: Base(Type::Disconnection)
					, reason(r)
				{}

				Reason reason;/*!< disconnection reason*/
		};

		/*!
			\class CreateGame Messages.hpp Messages
			\brief to send to create a game
		*/
		class CreateGame : public Base
		{
			DECLARE_MESSAGE(CreateGame);
			public:
				/*!
					\brief default constructor
					\param[in] r of type Result which is the creation's result
				*/
				CreateGame(Result r)
					: Base(Type::CreateGame)
					, result(r)
				{}

				vUc toUserData();

				Result result;/*!< creation's result*/
		};

		/*!
			\class JoinGame Messages.hpp Messages
			\brief to send to join an existing game
		*/
		class JoinGame : public Base
		{
			DECLARE_MESSAGE(JoinGame);
			public:
				
				/*!
					\brief default constructor
					\param[in] r of type Result which is the joining result
				*/
				JoinGame(Result r)
					: Base(Type::JoinGame)
					, result(r)
				{}

				vUc toUserData();

				Result result;/*!< joining result*/
		};

		/*!
			\class StartGame Messages.hpp Messages
			\brief to send when the game is ready and can start
		*/
		class StartGame : public Base
		{
			DECLARE_MESSAGE(StartGame);
			public:
				
				/*!
					\brief default constructor
					\param[in] r of type Result
				*/
				StartGame(Result r)
					: Base(Type::StartGame)
					, result(r)
				{}

				vUc toUserData();

				Result result;/*!< starting result*/
		};
		
		/*!
			\class SelectRace Messages.hpp Messages
			\brief to send when a player is selecting a race
		*/
		class SelectRace : public Base
		{
			DECLARE_MESSAGE(SelectRace);
			public:

				/*
					\brief default constructor
					\param[in] codeRace of type Game::Enums::Races
				*/
				SelectRace(Game::Enums::Races codeRace)
					:Base(Type::SelectRace)
					, m_codeRace(codeRace)
				{}

				vUc toUserData();

				Game::Enums::Races m_codeRace;/*!< race's code*/
		};

		/*!
			\class SelectColor Messages.hpp Messages
			\brief to send when a player is selecting a color
		*/
		class SelectColor : public Base
		{
			DECLARE_MESSAGE(SelectColor);
			public:

				/*!
					\brief default constructor
					\param[in] codeColor of type Game::Enums::Colors
				*/
				SelectColor(Game::Enums::Colors codeColor)
					: Base(Type::SelectColor)
					, m_codeColor(codeColor)
				{}

				vUc toUserData();

				Game::Enums::Colors m_codeColor;/*!< color's code*/
		};

		/*!
			\class MoveUnit Messages.hpp Messages
			\brief to send when a player move a unit
		*/
		class MoveUnit : public Base
		{
			DECLARE_MESSAGE(MoveUnit);
			public:

				/*!
					\brief default constructor
					\param[in] hashCodeUnit of type int : unit identifier
					\param[in] x of type int : destination's x
					\param[in] y of type int : destination's y
				*/
				MoveUnit(int hashCodeUnit, int x, int y)
					: Base(Type::MoveUnit)
					, m_hashCodeUnit(hashCodeUnit)
					, m_x(x)
					, m_y(y)
				{}

				vUc toUserData();

				int m_hashCodeUnit;/*!< unit's identifier*/
				int m_x;/*!< destination's x*/
				int m_y;/*!< destination's y*/
		};

		/*!
			\class CreateUnit Messagess.hpp Messages
			\brief to send when a unit is created
			\deprecated
		*/
		class CreateUnit : public Base
		{
			DECLARE_MESSAGE(CreateUnit);
			public:

				/*!
					\brief default constructor
					\param[in] codeUnit of type Game::Enums::Units : code of the unit to create
					\param[in] x of type int : x position
					\param[in] y of type int : y position
					\deprecated
				*/
				CreateUnit(Game::Enums::Units codeUnit, int x, int y)
					: Base(Type::CreateUnit)
					, m_codeUnit(codeUnit)
					, m_x(x)
					, m_y(y)
				{}

				vUc toUserData();

				Game::Enums::Units m_codeUnit;/*!< unit's code to create*/
				int m_x;/*!< x position*/
				int m_y;/*!< y position*/
		};

		/*!
			\class QueueUnit Messages.hpp Messages
			\brief to send when queueing units
		*/
		class QueueUnit : public Base
		{
			DECLARE_MESSAGE(QueueUnit);
			public:

				/*!
					\brief default constructor
					\param[in] codeUnit of type Game::Enums::Units : the unit to queue
					\param[in] hashCodeBuilding of type int : the building which has to queue the unit
				*/
				QueueUnit(Game::Enums::Units codeUnit, int hashCodeBuilding)
					: Base(Type::QueueUnit)
					, m_codeUnit(codeUnit)
					, m_hashCodeBuilding(hashCodeBuilding)
				{}

				vUc toUserData();

				Game::Enums::Units m_codeUnit;/*!< unit's code to queue*/
				int m_hashCodeBuilding;/*!< the building which has to queue the unit*/
		};

		/*!
			\class Attack Messagess.hpp Messages
			\brief to send when something is attacking something else
		*/
		class Attack : public Base
		{
			DECLARE_MESSAGE(Attack);
			public:

				/*!
					\brief default constructor
					\param[in] hashCodeAttacker of type int : identifier of the attacker
					\param[in] hashCodeTarget of type int : identifier of the target
				*/
				Attack(int hashCodeAttacker, int hashCodeTarget)
					: Base(Type::Attack)
					, m_hashCodeAttacker(hashCodeAttacker)
					, m_hashCodeTarget(hashCodeTarget)
				{}

				vUc toUserData();

				int m_hashCodeAttacker;/*!< attacker's id*/
				int m_hashCodeTarget;/*!< target's id*/
		};

		/*!
			\class DestroyUnit Messages.hpp Messages
			\brief to send when a unit is supposed to die
		*/
		class DestroyUnit : public Base
		{
			DECLARE_MESSAGE(DestroyUnit);
			public:

				/*!
					\brief default constructor
					\param[in] hashCodeUnit of type int : unit's identifier
				*/
				DestroyUnit(int hashCodeUnit)
					: Base(Type::DestroyUnit)
					, m_hashCodeUnit(hashCodeUnit)
				{}

				vUc toUserData();

				int m_hashCodeUnit;/*!< unit's id*/
		};

		/*!
			\class CreateBuilding Messages.hpp Messages
			\brief to send when a building is created
		*/
		class CreateBuilding : public Base
		{
			DECLARE_MESSAGE(CreateBuilding);
			public:

				/*!
					\brief default constructor

					\param[in] codeBuilding of type Game::Enums::Buildings : building type identifier
					\param[in] x of type int : x position
					\param[in] y of type int : y position
				*/
				CreateBuilding(Game::Enums::Buildings codeBuilding, int x, int y)
					: Base(Type::CreateBuilding)
					, m_codeBuilding(codeBuilding)
					, m_x(x)
					, m_y(y)
				{}

				vUc toUserData();

				Game::Enums::Buildings m_codeBuilding;/*!< building type's id*/
				int m_x;/*!< x position*/
				int m_y;/*!< y position*/
		};

		/*!
			\class CreateOpti Messages.hpp Messages
			\brief to send when an optimisation is created
		*/
		class CreateOpti : public Base
		{
			DECLARE_MESSAGE(CreateOpti);
		public:

			/*!
				\brief default constructor

				\param[in] codeOpti of type Game::Enums::Opti : optimisation type identifier
			*/
			CreateOpti(Game::Enums::Opti codeOpti)
				: Base(Type::CreateOpti)
				, m_codeOpti(codeOpti)
			{}

			vUc toUserData();

			Game::Enums::Opti m_codeOpti;/*!< opti type's id*/
		};

		/*!
			\class QueueBuilding Messages.hpp Messages
			\brief to send when queueing a building
		*/
		class QueueBuilding : public Base
		{
			DECLARE_MESSAGE(QueueBuilding);
			public:

				/*!
					\brief default constructor

					\param[in] codeBuilding of type Game::Buildings : building to create's id
					\param[in] hashCodeBuilding of type int : identifier of the building which has to queue this building ////Maybe will it be a unit hash code////
				*/
				QueueBuilding(Game::Enums::Buildings codeBuilding, int hashCodeBuilding)
					: Base(Type::QueueBuilding)
					, m_codeBuilding(codeBuilding)
					, m_hashCodeBuilding(hashCodeBuilding)
				{}

				vUc toUserData();

				Game::Enums::Buildings m_codeBuilding;/*!< building type to queue id*/
				int m_hashCodeBuilding;/*!< source building id*/
		};

		/*!
			\class QueueOpti Messages.hpp Messages
			\brief to send when queueing an optimisation
		*/
		class QueueOpti : public Base
		{
			DECLARE_MESSAGE(QueueOpti);
		public:

			/*!
				\brief default constructor

				\param[in] codeOpti of type Game::Buildings : optimisation to create's id
				\param[in] hashCodeBuilding of type int : identifier of the building which has to queue this optimisation
			*/
			QueueOpti(Game::Enums::Opti codeOpti, int hashCodeBuilding)
				: Base(Type::QueueOpti)
				, m_codeOpti(codeOpti)
				, m_hashCodeBuilding(hashCodeBuilding)
			{}

			vUc toUserData();

			Game::Enums::Opti m_codeOpti;/*!< optimisation type to queue id*/
			int m_hashCodeBuilding;/*!< source building id*/
		};

		/*!
			\class DestroyBuilding Messages.hpp Messages
			\brief to send when a building is supposed to die
		*/
		class DestroyBuilding : public Base
		{
			DECLARE_MESSAGE(DestroyBuilding);
		public:

			/*!
				\brief default constructor

				\param[in] hashCodeBuilding of type int : building to destroy
			*/
			DestroyBuilding(int hashCodeBuilding)
				: Base(Type::DestroyBuilding)
				, m_hashCodeBuilding(hashCodeBuilding)
			{}

			vUc toUserData();

			int m_hashCodeBuilding;/*!< building id*/
		};

		/*!
			\class EndGame Messages.hpp Messages
			\brief to send the the game ends
		*/
		class EndGame : public Base
		{
			DECLARE_MESSAGE(EndGame);
		public:

			/*!
				\enum State

				\brief the state of the game at its end
			*/
			enum class State {
				Win,/*!< player win*/
				Loss,/*!< player loose*/
			};

			/*!
				\brief default constructor

				\param[in] ending of type State : the end state
			*/
			EndGame(State ending)
				: Base(Type::EndGame)
				, m_ending(ending)
			{}

			vUc toUserData();

			State m_ending;/*!< state at the end of the game*/
		};

		/*!
			\class Quit Messages.hpp Messages

			\brief to send when a player leaves the game
		*/
		class Quit : public Base
		{
			DECLARE_MESSAGE(Quit);
		public:

			/*!
				\brief default constructor
			*/
			Quit()
				: Base(Type::Quit)
			{}

			vUc toUserData();
		};

		/*!
			\class UserData Messages.hpp Messages
			\brief  to send when signing up in game
		*/
		class UserData : public Base
		{
			DECLARE_MESSAGE(UserData);
		public:
			/*!
				\brief default constructor
				\param[in] d of type vector<unsigned char>&& which is the datas to send
			*/
			UserData(vUc&& d)
				: Base(Type::UserData)
				, data(std::move(d))
			{}

			/*!
				\brief to convert userdata into original message type
				\return converted message
			*/
			Messages::Base toRealType() const;

			vUc data;/*!< datas to send*/
		};
#undef DECLARE_MESSAGE
		
		/*
			\brief to format a int to fit in a vector<unsigned char>
			it cast the int value into char* then save its size before values into the destination
			format looks like : {[some values]...,SIZE_OF_ATTR,ATTR_VALUE,....[some values]}

			\param[in] attr of type int : the member to format
			\param[out] dest of type vector<unsigned char> : the destination to save the member
		*/
		void format(vUc* dest, int attr) ;

		/*
			\brief to extract a int from a vector<unsigned char> after using format function

			\param[in] source of type vector<unsigned char> : data source
			\param[in] from of type int : start index of the int
			\param[in] size of type char : size of int to extract
		*/
		int extractInt(const vUc* source, int from, char size);
	}
}
