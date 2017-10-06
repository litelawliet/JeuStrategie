#include "Messages.hpp"

/*!
	\file Messages.hpp
	\brief Messages' class definition
	\author Friday
*/

namespace Network {
	namespace Messages {

		vUc UserInfo::toUserData(){
			vUc data = {
				(uc)Type::Accept
				, mPseudo.data()
				, '#'
				, mPasswd.data()
			};

			return data;
		}

		vUc Accept::toUserData() {
			vUc data = {
				(uc)Type::Accept
				, (uc)result
			};
			return data;
		}

		vUc CreateGame::toUserData() {
			vUc data = {
				(uc)Type::CreateGame
				, (uc)result
			};

			return data;
		}

		vUc JoinGame::toUserData() {
			vUc data = {
				(uc)Type::JoinGame
				, (uc)result
			};
			return data;
		}

		vUc StartGame::toUserData() {
			vUc data = {
				(uc)Type::StartGame
				, (uc)result
			};
			return data;
		}

		vUc SelectRace::toUserData() {
			vUc data = {
				(uc)Type::SelectRace
				, (uc)m_codeRace
			};
			return data;
		}

		vUc SelectColor::toUserData() {
			vUc data = {
				(uc)Type::SelectColor
				, (uc)m_codeColor
			};
			return data;
		}

		vUc MoveUnit::toUserData() {
			vUc data = {
				(uc)Type::MoveUnit
			};
			format(&data, m_hashCodeUnit);
			format(&data, m_x);
			format(&data, m_y);
			return data;
		}

		vUc CreateUnit::toUserData() {
			vUc data = {
				(uc)Type::CreateUnit
				, (uc)m_codeUnit
			};
			format(&data, m_x);
			format(&data, m_y);
			return data;
		}

		vUc QueueUnit::toUserData() {
			vUc data = {
				(uc)Type::QueueUnit
				, (uc)m_codeUnit
			};
			format(&data, m_hashCodeBuilding);
			return data;
		}

		vUc Attack::toUserData() {
			vUc data = {
				(uc)Type::Attack
			};
			format(&data, m_hashCodeAttacker);
			format(&data, m_hashCodeTarget);
			return data;
		};

		vUc DestroyUnit::toUserData() {
			vUc data = {
				(uc)Type::DestroyUnit
			};
			format(&data, m_hashCodeUnit);
			return data;
		}

		vUc CreateBuilding::toUserData() {
			vUc data = {
				(uc)Type::CreateBuilding
				, (uc)m_codeBuilding
			};
			format(&data, m_x);
			format(&data, m_y);
			return data;
		}

		vUc CreateOpti::toUserData() {
			vUc data = {
				(uc)Type::CreateBuilding
				, (uc)m_codeOpti
			};
			return data;
		}

		vUc QueueBuilding::toUserData() {
			vUc data = {
				(uc)Type::QueueBuilding
				, (uc)m_codeBuilding
			};
			format(&data, m_hashCodeBuilding);
			return data;
		}

		vUc QueueOpti::toUserData() {
			vUc data = {
				(uc)Type::QueueOpti
				, (uc)m_codeOpti
			};
			format(&data, m_hashCodeBuilding);
			return data;
		}

		vUc DestroyBuilding::toUserData() {
			vUc data = {
				(uc)Type::DestroyBuilding
			};
			format(&data, m_hashCodeBuilding);
			return data;
		}

		vUc EndGame::toUserData() {
			vUc data = {
				(uc)Type::EndGame,
				(uc)m_ending
			};
			return data;
		}

		vUc Quit::toUserData() {
			return vUc{
				(uc)Type::Quit,

			};
		}

		Base UserData::toRealType() const {
			switch (data[0]) {

				//Casting of UserInfo
				case (uc)Type::UserInfo:
					int lim = 0;
					int i = 0;
					for(i = 0; i < strlen(data); i++){
						if(data[i]=='#') break;
					}
					char[] pseudo = new char[i];
					for(int j = 0; j < i; j++){
						pseudo[j] = data[j];
					}

					char[] pwd = new char[strlen(data)-i+1];
					for(int j = 0; j < strlen(data)-i+1; j++){
						pwd[j]=data[j+i+1];
					}

					std::string spseudo(pseudo);
					std::string spwd(pwd);
					return UserInfo(spseudo,spwd);

				//Casting of Accept
				case (uc)Type::Accept:
					return Accept((data[1] == (uc)Result::Success ? Result::Success : Result::Fail));

				//Casting of CreateGame
				case (uc)Type::CreateGame:
					return CreateGame((data[1] == (uc)Result::Success ? Result::Success : Result::Fail));

				//Casting of JoinGame
				case (uc)Type::JoinGame:
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
					return Quit((data[1] == (uc)Quit::Status::Ended ? Quit::Status::Ended : Quit::Status::NotEnded));
			}
		}
        void format(vUc* dest, int attr){
			std::string n_attr = std::to_string(attr);
			dest->push_back(strlen(n_attr));
			for (unsigned int i = 0; i < strlen(n_attr); i++) {
				dest->push_back((n_attr.data())[i]);
			}
		}

        int extractInt(const vUc* source, int from, char size) {
			const char* preExtract = new char[size];
			for (int i = 0; i < size; i++) {
				preExtract[i] = source->at(i + 1 + from);
			}

			return atoi(preExtract);
		}
	}
}
