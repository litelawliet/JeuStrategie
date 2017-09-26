/*!
	\file Client.cpp
	\brief definition of Client, ReceptionHandler, SendingHandler, ConnectionHandler and ClientImpl
	\author Friday
*/

#include "TCP/Client.hpp"

#include "Sockets.hpp"
#include "Messages.hpp"
#include "Errors.hpp"

#include <vector>
#include <list>
#include <cassert>
#include <numeric>


/*!
	\namespace Network
	\brief contains all network things
*/
namespace Network
{
	/*!
		\namespace TCP
		\brief contains all TCP things
	*/
	namespace TCP
	{

		/*!
			\class ConnectionHandler Client.cpp Client

			\brief object to handle connection
		*/
		class ConnectionHandler
		{
			public:

				/*!
					\brief default constructor
				*/
				ConnectionHandler() = default;

				/*!
					\brief to connect a socket to a server

					\param[in] sckt of type struct SOCKET : connection socket
					\param[in] address of type string& : server's ip address
					\param[in] port of type unsigned short : server's port

					\return true if connection successful, false otherwise
				*/
				bool connect(SOCKET sckt, const std::string& address, unsigned short port);

				/*!
					\brief receive confirmation about connection

					\return a Connection Message object
				*/
				std::unique_ptr<Messages::Connection> poll();

				/*!
					\brief get connection address

					\return connected address
				*/
				const sockaddr_in& connectedAddress() const { return mConnectedAddress; }

			private:
				pollfd mFd{ 0 };/*!< socket's informations*/
				sockaddr_in mConnectedAddress;/*!< connected address*/
				std::string mAddress;/*!< ip address*/
				unsigned short mPort;/*!< used port*/
		};

		bool ConnectionHandler::connect(SOCKET sckt, const std::string& address, unsigned short port)
		{
			assert(sckt != INVALID_SOCKET);//=>available socket
			mAddress = address;
			mPort = port;
			mFd.fd = sckt;
			mFd.events = POLLOUT;
			inet_pton(AF_INET, mAddress.c_str(), &mConnectedAddress.sin_addr.s_addr);
			mConnectedAddress.sin_family = AF_INET;
			mConnectedAddress.sin_port = htons(mPort);
			if (::connect(sckt, (const sockaddr*)&mConnectedAddress, sizeof(mConnectedAddress)) != 0)//=>connection error
			{
				int err = Errors::Get();
				if (err != Errors::INPROGRESS && err != Errors::WOULDBLOCK)//socket busy
					return false;
			}
			return true;
		}

		std::unique_ptr<Messages::Connection> ConnectionHandler::poll()
		{
			int res = ::poll(&mFd, 1, 0);
			if (res < 0)
				return std::make_unique<Messages::Connection>(Messages::Connection::Result::Failed);
			else if (res > 0)
			{
				if (mFd.revents & POLLOUT)//=>connection success
				{
					return std::make_unique<Messages::Connection>(Messages::Connection::Result::Success);
				}
				else if (mFd.revents & (POLLHUP | POLLNVAL))//=>connection fail
				{
					return std::make_unique<Messages::Connection>(Messages::Connection::Result::Failed);
				}
				else if(mFd.revents & POLLERR)//=>connection fail
				{
					return std::make_unique<Messages::Connection>(Messages::Connection::Result::Failed);
				}
			}
			//!< action not ended
			return nullptr;
		}
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

		/*!
			\class ReceptionHandler Client.cpp Client;
			\brief to receive messages
		*/
		class ReceptionHandler
		{

			/*!
				\enum State
				\brief reception state
			*/
			enum class State {
				Header,/*!< Time to receive message's header*/
				Data,/*!< Time to receive message's body*/
			};

			public:

				/*!
					\brief default constructor
				*/
				ReceptionHandler() = default;

				/*!
					\brief initialize ReceptionHandler

					\param[in] sckt of type struct SOCKET : target
				*/
				void init(SOCKET sckt);

				/*!
					\brief to receive messages

					\return received message
				*/
				std::unique_ptr<Messages::Base> recv();

			private:

				/*!
					\brief to know how many data we still need to receive
				*/
				inline char* missingDataStartBuffer() { return reinterpret_cast<char*>(mBuffer.data() + mReceived); }

				/*!
					\brief to know data length we still need to receive
				*/
				inline int missingDataLength() const { return static_cast<int>(mBuffer.size() - mReceived); }

				/*!
					\brief to receive message's header
				*/
				void startHeaderReception();

				/*!
					\brief to receive message's body
				*/
				void startDataReception();

				/*!
					\brief to receive datas

					\param[in] expectedDataLenght of type unsigned int : size of data to receive
					\param[in] newState of type ReceptionHandler::State : which part should be receive
				*/
				void startReception(unsigned int expectedDataLength, State newState);

			private:
				std::vector<unsigned char> mBuffer;/*!< reception buffer*/
				unsigned int mReceived;/*!< amount of received datas*/
				SOCKET mSckt{ INVALID_SOCKET };/*!< socket to use*/
				State mState;/*!< reception state*/
		};

		void ReceptionHandler::init(SOCKET sckt)
		{
			assert(sckt != INVALID_SOCKET);//=>available socket
			mSckt = sckt;
			startHeaderReception();//ready to receive a header
		}
		
		void ReceptionHandler::startHeaderReception()
		{
			startReception(HeaderSize, State::Header);
		}

		void ReceptionHandler::startDataReception()
		{
			assert(mBuffer.size() == sizeof(HeaderType));//=>buffer ready to receive
			HeaderType networkExpectedDataLength;
			memcpy(&networkExpectedDataLength, mBuffer.data(), sizeof(networkExpectedDataLength));//get header
			const auto expectedDataLength = ntohs(networkExpectedDataLength);//get data length
			startReception(expectedDataLength, State::Data);//start data reception
		}

		void ReceptionHandler::startReception(unsigned int expectedDataLength, State newState)
		{
			mReceived = 0;
			mBuffer.clear();
			mBuffer.resize(expectedDataLength, 0);
			mState = newState;
		}

		std::unique_ptr<Messages::Base> ReceptionHandler::recv()
		{
			assert(mSckt != INVALID_SOCKET);//=>socket available
			int ret = ::recv(mSckt, missingDataStartBuffer(), missingDataLength(), 0);//reception
			if (ret > 0)//=> reception successful
			{
				mReceived += ret;//amount of received datas
				if (mReceived == mBuffer.size())//=>message fully received
				{
					if (mState == State::Data)//=>if message's body
					{
						std::unique_ptr<Messages::Base> msg = std::make_unique<Messages::UserData>(std::move(mBuffer));
						startHeaderReception();
						return msg;
					}
					else//=>if message's head
					{
						startDataReception();
						//!< if already available, datas are send
						return recv();
					}
				}
				return nullptr;
			}
			else if (ret == 0)//=>nothing to receive
			{
				//!< connexion terminée correctement
				return std::make_unique<Messages::Disconnection>(Messages::Disconnection::Reason::Disconnected);
			}
			else //=> error
			{
				//!< error handling
				int error = Errors::Get();
				if (error == Errors::WOULDBLOCK || error == Errors::AGAIN)
				{
					return nullptr;
				}
				else
				{
					return std::make_unique<Messages::Disconnection>(Messages::Disconnection::Reason::Lost);
				}
			}
		}
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

		/*!
			\class SendingHandler Client.cpp Client

			\brief object to handle sending
		*/
		class SendingHandler
		{
			/*!
				\enum State
				\brief sending state
			*/
			enum class State {
				Idle,/*!< waiting*/
				Header,/*!< send header*/
				Data,/*!< send body*/
			};

			public:

				/*!
					\brief default constructor
				*/
				SendingHandler() = default;

				/*!
					\brief initialize sendingHandler

					\param[in] sckt of type struct SOCKET : used socket
				*/
				void init(SOCKET sckt);

				/*!
					\brief to send datas

					\param[in] data of type unsigned char* : datas to send
					\param[in] datalen of type unsigned int : data to send's length
					
					\return true if send successful, false otherwise
				*/
				bool send(const unsigned char* data, unsigned int datalen);

				/*!
					\brief update send state
				*/
				void update();

				/*!
					\brief get size of queued data

					\return size
				*/
				size_t queueSize() const;

			private:

				/*!
					\brief send the rest of datas

					\return true if send successful, false otherwise
				*/
				bool sendPendingBuffer();

				/*!
					\brief queue next header
				*/
				void prepareNextHeader();

				/*!
					\brief queue next body
				*/
				void prepareNextData();

			private:
				std::list<std::vector<unsigned char>> mQueueingBuffers;/*!< list of datas to send*/
				std::vector<unsigned char> mSendingBuffer;/*!< datas to send*/
				SOCKET mSocket{ INVALID_SOCKET };/*!< socket to use*/
				State mState{ State::Idle };/*!< sending state (default Idle)*/
		};

		void SendingHandler::init(SOCKET sckt)
		{
			mSocket = sckt;
			if (mState == State::Header || mState == State::Data)//=>is not waiting
			{
				mSendingBuffer.clear();
			}
			mState = State::Idle;
		}

		bool SendingHandler::send(const unsigned char* data, unsigned int datalen)
		{
			if (datalen > std::numeric_limits<HeaderType>::max())//=>amount of data too high
				return false;
			mQueueingBuffers.emplace_back(data, data + datalen);
			return true;
		}

		void SendingHandler::update()
		{
			assert(mSocket != INVALID_SOCKET);//=> socket available
			if (mState == State::Idle && !mQueueingBuffers.empty())//=>is waiting and nothing is queued
			{
				prepareNextHeader();
			}
			while (mState != State::Idle && sendPendingBuffer())//=>is not waiting and something to send
			{
				if (mState == State::Header)//=> send header
				{
					prepareNextData();
				}
				else//=> send body
				{
					if (!mQueueingBuffers.empty())//=>still something to queue
					{
						prepareNextHeader();
					}
					else//=> nothing to queue
					{
						mState = State::Idle;
					}
				}
			}
		}

		bool SendingHandler::sendPendingBuffer()
		{
			if (mSendingBuffer.empty())//=> nothing to send
				return true;
			
			int sent = ::send(mSocket, reinterpret_cast<char*>(mSendingBuffer.data()), static_cast<int>(mSendingBuffer.size()), 0);
			if (sent > 0)//=> something is sent
			{
				if (sent == mSendingBuffer.size())//=> everything is sent
				{
					mSendingBuffer.clear();
					return true;
				}
				else//=> still something to send
				{
					memmove(mSendingBuffer.data() + sent, mSendingBuffer.data(), sent);
					mSendingBuffer.erase(mSendingBuffer.cbegin() + sent, mSendingBuffer.cend());
				}
			}//=> sending error
			return false;
		}

		void SendingHandler::prepareNextHeader()
		{
			assert(!mQueueingBuffers.empty());//=> something to send
			const auto header = static_cast<HeaderType>(mQueueingBuffers.front().size());
			const auto networkHeader = htons(header);
			mSendingBuffer.clear();
			mSendingBuffer.resize(HeaderSize);
			memcpy(mSendingBuffer.data(), &networkHeader, sizeof(HeaderType));
			mState = State::Header;
		}

		void SendingHandler::prepareNextData()
		{
			assert(!mQueueingBuffers.empty());//=> something to send
			mSendingBuffer.swap(mQueueingBuffers.front());
			mQueueingBuffers.pop_front();
			mState = State::Data;
		}

		size_t SendingHandler::queueSize() const
		{
			size_t s = std::accumulate(mQueueingBuffers.cbegin()
				, mQueueingBuffers.cend()
				, static_cast<size_t>(0)
				, [](size_t n, const std::vector<unsigned char>& queuedItem) {
				return n + queuedItem.size() + HeaderSize;
			});
			if (mState == State::Data)
				s += mSendingBuffer.size();
			return s;
		}
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////

		/*!
			\class ClientImpl Client.cpp Client
			\brief implemented client
		*/
		class ClientImpl
		{

			/*!
				\enum State
				\brief connection state
			*/
			enum class State {
				Connecting,/*!< waiting for connection*/
				Connected,/*!< connection established*/
				Disconnected,/*!< connection interrupted*/
			};

			public:

				/*!
					\brief default constructor
				*/
				ClientImpl() = default;

				/*!
					\brief default destructor
				*/
				~ClientImpl();

				/*!
					\brief initalize ClientImpl

					\param[in] sckt of type struct SOCKET : socket to use
					\param[in] addr of type sockaddr_in& : socket's address

					\return true if initialize well, false otherwise
				*/
				bool init(SOCKET&& sckt, const sockaddr_in& addr);

				/*!
					\brief connect the client to the server

					\param[in] ipaddress of type string& : server's ip
					\param[in] port of type unsigned short : server's port

					\return true if connected, false otherwise
				*/
				bool connect(const std::string& ipaddress, unsigned short port);

				/*!
					\brief disconnect from the server
				*/
				void disconnect();

				/*!
					\brief send datas to server

					\param[in] data of type unsigned char* : data to send
					\param[in] len of type unsigned int : data's length

					\return true if send successful, false otherwise
				*/
				bool send(const unsigned char* data, unsigned int len);

				/*!
					\brief receive datas from server

					\return Message object
				*/
				std::unique_ptr<Messages::Base> poll();

				/*!
					\brief get client identifier

					\return identifier
				*/
				uint64_t id() const { return static_cast<uint64_t>(mSocket); }

				/*!
					\brief get destination address

					\return address
				*/
				const sockaddr_in& destinationAddress() const { return mAddress; }

			private:

				/*!
					\brief initialize handlers

					\param[in] addr of type sockaddr_in& : socket's address to use
				*/
				void onConnected(const sockaddr_in& addr);

			private:
				ConnectionHandler mConnectionHandler;/*!< own connection handler*/
				SendingHandler mSendingHandler;/*!< own sending handler*/
				ReceptionHandler mReceivingHandler;/*!< own reception handler*/
				sockaddr_in mAddress{ 0 };/*!< socket address*/
				SOCKET mSocket{ INVALID_SOCKET };/*!< socket to use*/
				State mState{ State::Disconnected };/*!< client state*/
		};

		ClientImpl::~ClientImpl()
		{
			disconnect();
		}

		bool ClientImpl::init(SOCKET&& sckt, const sockaddr_in& addr)
		{
			assert(sckt != INVALID_SOCKET);//=> socket available
			if (sckt == INVALID_SOCKET)//=> unavailable socket
				return false;

			assert(mState == State::Disconnected);//=> client not connected
			assert(mSocket == INVALID_SOCKET);//=> closed socket
			if (mSocket != INVALID_SOCKET)//=> socket already used
				disconnect();

			mSocket = sckt;
			if (!SetNonBlocking(mSocket))//=> blocking socket
			{
				disconnect();
				return false;
			}
			onConnected(addr);
			return true;
		}

		bool ClientImpl::connect(const std::string& ipaddress, unsigned short port)
		{
			assert(mState == State::Disconnected);//=> client not connected yet
			assert(mSocket == INVALID_SOCKET);//=> socket not used yet
			if (mSocket != INVALID_SOCKET)//=> unavailable socket
				disconnect();
			mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (mSocket == INVALID_SOCKET)//=> socket still unavailable
			{
				return false;
			}
			else if (!SetNonBlocking(mSocket))//=> blocking socket
			{
				disconnect();
				return false;
			}
			if (mConnectionHandler.connect(mSocket, ipaddress, port))//=>connection successful
			{
				mState = State::Connecting;
				return true;
			}//=> connection not established
			return false;
		}

		void ClientImpl::disconnect()
		{
			if (mSocket != INVALID_SOCKET)//=> connected
			{
				CloseSocket(mSocket);
			}
			mSocket = INVALID_SOCKET;
			mState = State::Disconnected;
		}

		bool ClientImpl::send(const unsigned char* data, unsigned int len)
		{
			return mSendingHandler.send(data, len);
		}

		std::unique_ptr<Messages::Base> ClientImpl::poll()
		{
			switch (mState)
			{
				case State::Connecting:
				{
					auto msg = mConnectionHandler.poll();
					if (msg)//=> connection message received
					{
						if (msg->result == Messages::Connection::Result::Success)//=> connection successful
						{
							onConnected(mConnectionHandler.connectedAddress());
						}
						else//=> connection fail
						{
							disconnect();
						}
					}
					return msg;
				} break;
				case State::Connected:
				{
					mSendingHandler.update();
					auto msg = mReceivingHandler.recv();
					if (msg)//=> message received
					{
						if (msg->is<Messages::Disconnection>())
						{
							disconnect();
						}
					}
					return msg;
				} break;
				case State::Disconnected:
				{
				} break;
			}
			return nullptr;
		}

		void ClientImpl::onConnected(const sockaddr_in& addr)
		{
			mAddress = addr;
			mSendingHandler.init(mSocket);
			mReceivingHandler.init(mSocket);
			mState = State::Connected;
		}
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		Client::Client() {}
		Client::~Client() {}
		Client::Client(Client&& other)
			: mImpl(std::move(other.mImpl))
		{}

		Client& Client::operator=(Client&& other)
		{
			mImpl = std::move(other.mImpl);
			return *this;
		}
		bool Client::init(SOCKET&& sckt, const sockaddr_in& addr)
		{
			if (!mImpl)//=> not linked yet
				mImpl = std::make_unique<ClientImpl>();//linking
			return mImpl && mImpl->init(std::move(sckt), addr);
		}
		bool Client::connect(const std::string& ipaddress, unsigned short port)
		{
			if (!mImpl)//=> not linked yet
				mImpl = std::make_unique<ClientImpl>();//linking
			return mImpl && mImpl->connect(ipaddress, port);
		}
		void Client::disconnect() { if (mImpl) mImpl->disconnect(); mImpl = nullptr; }
		bool Client::send(const unsigned char* data, unsigned int len) { return mImpl && mImpl->send(data, len); }
		std::unique_ptr<Messages::Base> Client::poll() { return mImpl ? mImpl->poll() : nullptr; }
		uint64_t Client::id() const { return mImpl ? mImpl->id() : -1; }
		const sockaddr_in& Client::destinationAddress() const { static sockaddr_in empty{ 0 }; return mImpl ? mImpl->destinationAddress() : empty; }
	}
}