/*!
	\file Server.cpp
	\brief definition of Server and ServerImpl methods
	\author Friday
*/

#include "Server.hpp"

#include "../Sockets.hpp"
#include "../TCP/Client.hpp"
#include "../Messages.hpp"

#include <map>
#include <list>
#include <cassert>

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
			\class ServerImpl Server.hpp Server
		*/
		class ServerImpl
		{
			public:

				/*!
					\brief default constructor
				*/
				ServerImpl() = default;

				/*!
					\brief default destructor
				*/
				~ServerImpl();

				/*!
					\brief cf. class Server
				*/
				bool start(unsigned short _port);

				/*!
					\brief cf. class Server
				*/
				void stop();

				/*!
					\brief cf. class Server
				*/
				void update();

				/*!
					\brief cf. class Server
				*/
				bool sendTo(uint64_t clientid, const unsigned char* data, unsigned int len);

				/*!
					\brief cf. class Server
				*/
				bool sendToAll(const unsigned char* data, unsigned int len);

				/*!
					\brief cf. class Server
				*/
				std::unique_ptr<Messages::Base> poll();

			private:
				std::map<uint64_t, Client> mClients;/*!< contains all clients with identifier*/
				std::list<std::unique_ptr<Messages::Base>> mMessages;/*!< contains last 10 received messages*/
				SOCKET mSocket{ INVALID_SOCKET };/*< used socket*/
		};

		ServerImpl::~ServerImpl()
		{
			stop();
		}

		bool ServerImpl::start(unsigned short _port)
		{
			assert(mSocket == INVALID_SOCKET);//verify socket
			if (mSocket != INVALID_SOCKET)
				stop();//if already open : stop server
			mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//create server socket
			if (mSocket == INVALID_SOCKET)
				return false;//if error during opening socket

			if (!SetReuseAddr(mSocket) || !SetNonBlocking(mSocket))
			{
				stop();
				return false;
			}
			/////////////////////////////
			//setup server's attributes//
			/////////////////////////////
			sockaddr_in addr;
			addr.sin_addr.s_addr = INADDR_ANY;
			addr.sin_port = htons(_port);
			addr.sin_family = AF_INET;
			/////////////////////////////
			/////////////////////////////
			/////////////////////////////
			if (bind(mSocket, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) != 0)//association of a socket to an address
			{
				stop();//stop server if it fails
				return false;
			}
			if (listen(mSocket, SOMAXCONN) != 0)//start listening for connections
			{
				stop();//stop server if it fails
				return false;
			}
			return true;
		}

		void ServerImpl::stop()
		{
			for (auto& client : mClients)
				client.second.disconnect();//disconnect all clients
			mClients.clear();//clear client list
			if (mSocket != INVALID_SOCKET)
				CloseSocket(mSocket);//deallocate socket
			mSocket = INVALID_SOCKET;
		}

		void ServerImpl::update()
		{
			if (mSocket == INVALID_SOCKET)
				return;//=>server stopped

			//!< accepts 10 next connections
			for (int accepted = 0; accepted < 10; ++accepted)
			{
				sockaddr_in addr = { 0 };
				socklen_t addrlen = sizeof(addr);
				SOCKET newClientSocket = accept(mSocket, reinterpret_cast<sockaddr*>(&addr), &addrlen);//get next connection
				if (newClientSocket == INVALID_SOCKET)//=>no more connection requests
					break;
				Client newClient;
				if (newClient.init(std::move(newClientSocket), addr))
				{
					auto message = std::make_unique<Messages::Connection>(Messages::Connection::Result::Success);//Connection message creation
					message->idFrom = newClient.id();
					message->from = newClient.destinationAddress();
					mMessages.push_back(std::move(message));
					mClients[newClient.id()] = std::move(newClient);
				}
			}

			//!< updates clients' state
			//!< receives a single message from each client
			//!< delete disconnected clients
			for (auto itClient = mClients.begin(); itClient != mClients.end(); )
			{
				auto& client = itClient->second;
				auto msg = client.poll();//receives message
				if (msg)
				{
					msg->from = itClient->second.destinationAddress();
					msg->idFrom = itClient->second.id();
					if (msg->is<Messages::Disconnection>())
						itClient = mClients.erase(itClient);//=> client disconnected
					else
						++itClient;
					mMessages.push_back(std::move(msg));//=>queue message
				}
				else
					++itClient;
			}
		}

		bool ServerImpl::sendTo(uint64_t clientid, const unsigned char* data, unsigned int len)
		{
			auto itClient = mClients.find(clientid);
			return itClient != mClients.end() && itClient->second.send(data, len);
		}

		bool ServerImpl::sendToAll(const unsigned char* data, unsigned int len)
		{
			bool ret = true;
			for (auto& client : mClients)
				ret &= client.second.send(data, len);
			return ret;
		}

		std::unique_ptr<Messages::Base> ServerImpl::poll()
		{
			if (mMessages.empty())
				return nullptr;

			auto msg = std::move(mMessages.front());
			mMessages.pop_front();
			return msg;
		}
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////
		Server::Server() {}
		Server::~Server() {}
		Server::Server(Server&& other)
			: mImpl(std::move(other.mImpl))
		{}
		Server& Server::operator=(Server&& other)
		{
			mImpl = std::move(other.mImpl);
			return *this;
		}
		bool Server::start(unsigned short _port)
		{
			if (!mImpl)
				mImpl = std::make_unique<ServerImpl>();
			return mImpl && mImpl->start(_port);
		}
		void Server::stop() { if (mImpl) mImpl->stop(); }
		void Server::update() { if (mImpl) mImpl->update(); }
		bool Server::sendTo(uint64_t clientid, const unsigned char* data, unsigned int len) { return mImpl && mImpl->sendTo(clientid, data, len); }
		bool Server::sendToAll(const unsigned char* data, unsigned int len) { return mImpl && mImpl->sendToAll(data, len); }
		std::unique_ptr<Messages::Base> Server::poll() { return mImpl ? mImpl->poll() : nullptr; }
	}
}
