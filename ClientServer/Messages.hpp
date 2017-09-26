#ifndef HEADER_MESSAGES_HPP
#define HEADER_MESSAGES_HPP

/*!
	\file Messages.hpp
	\brief Messages' class definition
	\author Friday
*/

#include <vector>
#include <stdint.h>
#include "Enums.hpp"

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
				*/
				Messages::Base toRealType() {
					switch (data[0]) {

						//Casting of CreateGame
					case (uc)Type::CreateGame:
						return CreateGame((data[1] == (uc)Result::Success ? Result::Success : Result::Fail));

						//Casting of JoinGame
					case (unsigned char)Type::JoinGame:
						return JoinGame((data[1] == (uc)Result::Success ? Result::Success : Result::Fail));

						//Casting of StartGame
					case (uc)Type::StartGame:
						return StartGame((data[1] == (uc)Result::Success ? Result::Success : Result::Fail));
					
						//Casting of SelectRace
					case (uc)Type::SelectRace:
						return SelectRace((Game::Enums::Races)data[1]);

						//Casting of SelectColor
					case (uc)Type::SelectColor:
						return SelectColor((Game::Enums::Colors)data[1]);

						//Casting of MoveUnit
					case (uc)Type::MoveUnit:
						return MoveUnit(extractInt(&data, 2, data[1])
							, extractInt(&data, data[1] + 2 + 1, data[data[1] + 2])
							, extractInt(&data, data[data[1] + 2] + data[1] + 2 + 1, data[data[data[1] + 2] + data[1] + 2]));
						
						//Casting of CreateUnit
					case (uc)Type::CreateUnit:
						return CreateUnit((Game::Enums::Units)data[1]
							, extractInt(&data, 3, data[2])
							, extractInt(&data, data[2] + 3 + 1, data[data[2] + 3]));

						//Casting of CreateOpti
					case (uc)Type::CreateOpti:
						return CreateOpti((Game::Enums::Opti)data[1]);

						//Casting of CreateBuilding
					case (uc)Type::CreateBuilding:
						return CreateBuilding((Game::Enums::Buildings)data[1]
							, extractInt(&data, 3, data[2])
							, extractInt(&data, data[2] + 3 + 1, data[data[2] + 3]));

						//Casting of QueueBuilding
					case (uc)Type::QueueBuilding:
						return QueueBuilding((Game::Enums::Buildings)data[1], extractInt(&data, 3, data[2]));

						//Casting of QueueUnit
					case (uc)Type::QueueUnit:
						return QueueUnit((Game::Enums::Units)data[1], extractInt(&data, 3, data[2]));

						//Casting of QueueOpti
					case (uc)Type::QueueOpti:
						return QueueOpti((Game::Enums::Opti)data[1], extractInt(&data, 3, data[2]));

						//Casting of Attack
					case (uc)Type::Attack:
						return Attack(extractInt(&data, 2, data[1])
							, extractInt(&data, data[1] + 2 + 1, data[data[1] + 2]));

						//Casting of DestroyUnit
					case (uc)Type::DestroyUnit:
						return DestroyUnit(extractInt(&data, 2, data[1]));

						//Casting of DestroyBuilding
					case (uc)Type::DestroyBuilding:
						return DestroyBuilding(extractInt(&data, 2, data[1]));

						//Casting of EndGame
					case (uc)Type::EndGame:
						return EndGame((data[1] == (uc)Messages::EndGame::State::Win ? Messages::EndGame::State::Win : Messages::EndGame::State::Loss));

						//Casting of Quit
					case (uc)Type::Quit:
                        return Quit();
					}
				}

				vUc data;/*!< datas to send*/
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

				vUc toUserData() {
					vUc data = { 
						(uc)Type::CreateGame
						, result == Result::Success ? (uc)Result::Success : (uc)Result::Fail 
					};
					return data;
				}

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

				vUc toUserData() {
					vUc data = { 
						(uc)Type::JoinGame
						, result == Result::Success ? (uc)Result::Success : (uc)Result::Fail
					};
					return data;
				}

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

				vUc toUserData() {
					vUc data = {
						(uc)Type::StartGame
						, result == Result::Success ? (uc)Result::Success : (uc)Result::Fail
					};
					return data;
				}

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

				vUc toUserData() {
					vUc data = {
						(uc)Type::SelectRace
						, (uc)m_codeRace
					};
					return data;
				}

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

				vUc toUserData() {
					vUc data = {
						(uc)Type::SelectColor
						, (uc)m_codeColor
					};
					return data;
				}

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

				vUc toUserData() {
					vUc data = {
						(uc)Type::MoveUnit
					};
					format(&data, m_hashCodeUnit);
					format(&data, m_x);
					format(&data, m_y);
					return data;
				}

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

				vUc toUserData() {
					vUc data = {
						(uc)Type::CreateUnit
						, (uc)m_codeUnit
					};
					format(&data, m_x);
					format(&data, m_y);
					return data;
				}

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

				vUc toUserData() {
					vUc data = {
						(uc)Type::QueueUnit
						, (uc)m_codeUnit
					};
					format(&data, m_hashCodeBuilding);
					return data;
				}

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

				vUc toUserData() {
					vUc data = {
						(uc)Type::Attack
					};
					format(&data, m_hashCodeAttacker);
					format(&data, m_hashCodeTarget);
					return data;
				};

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

				vUc toUserData() {
					vUc data = {
						(uc)Type::DestroyUnit
					};
					format(&data, m_hashCodeUnit);
					return data;
				}

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

				vUc toUserData() {
					vUc data = {
						(uc)Type::CreateBuilding
						, (uc)m_codeBuilding
					};
					format(&data, m_x);
					format(&data, m_y);
					return data;
				}

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

			vUc toUserData() {
				vUc data = {
					(uc)Type::CreateBuilding
					, (uc)m_codeOpti
				};
				return data;
			}

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

				vUc toUserData() {
					vUc data = {
						(uc)Type::QueueBuilding
						, (uc)m_codeBuilding
					};
					format(&data, m_hashCodeBuilding);
					return data;
				}

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

			vUc toUserData() {
				vUc data = {
					(uc)Type::QueueOpti
					, (uc)m_codeOpti
				};
				format(&data, m_hashCodeBuilding);
				return data;
			}

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

			vUc toUserData() {
				vUc data = {
					(uc)Type::DestroyBuilding
				};
				format(&data, m_hashCodeBuilding);
			}

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

			vUc toUserData() {
				vUc data = {
					(uc)Type::EndGame,
					m_ending == State::Win ? (uc)State::Win : (uc)State::Loss
				};
				return data;
			}

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

			vUc toUserData(){
				return vUc{ (uc)Type::Quit };
			}
		};
#undef DECLARE_MESSAGE
		
		/*
			\brief to format a int to fit in a vector<unsigned char>
			it cast the int value into char* then save its size before values into the destination
			format looks like : {[some values]...,SIZE_OF_ATTR,ATTR_VALUE,....[some values]}

			\param[in] attr of type int : the member to format
			\param[out] dest of type vector<unsigned char> : the destination to save the member
		*/
		void format(vUc* dest,int attr) {
			char* n_attr = (char*)attr;
			dest->push_back(strlen(n_attr));
            for (unsigned int i = 0; i < strlen(n_attr); i++) {
				dest->push_back(n_attr[i]);
			}
		}

		/*
			\brief to extract a int from a vector<unsigned char> after using format function

			\param[in] source of type vector<unsigned char> : data source
			\param[in] from of type int : start index of the int
			\param[in] size of type char : size of int to extract
		*/
		int extractInt(vUc* source, int from, char size) {
			char* preExtract = new char[size];
			for (int i = 0; i < size; i++) {
				preExtract[i] = source->at(i+1+from);
			}
			return atoi(preExtract);
		}
	}
}

#endif
