#ifndef HEADER_SERVER_HPP
#define HEADER_SERVER_HPP

/*!
	\file Server.hpp
	\brief declaration of Server and ServerImpl
	\author Friday
*/

#include <memory>

/*!
	\namespace Network
	\brief contains all network things
*/
namespace Network
{

	/*!
		\namespace Messages
		\brief contains all network things
	*/
	namespace Messages {
		class Base;
	}

	/*!
		\namespace TCP
		\brief contains all TCP things
	*/
	namespace TCP
	{

		/*!
			\class ServerImpl Server.hpp Server
		*/
		class ServerImpl;

		/*!
			\class Server Server.hpp Server
			\brief server side's communication
		*/
		class Server
		{
			public:

				/*!
					\brief default constructor
				*/
				Server();

				/*!
					\brief copy constructor
				*/
				Server(const Server&) = delete;

				/*!
					\brief copy constructor
				*/
				Server& operator=(const Server&) = delete;

				/*!
				\brief copy constructor
				*/
				Server(Server&&);

				/*!
				\brief copy constructor
				*/
				Server& operator=(Server&&);

				/*!
					\brief default destructor
				*/
				~Server();

				/*!
					\brief start protocol
					to start the server

					\param[in] _port of type unsigned short : port to use

					\return true if it starts successful, false otherwise
				*/
				bool start(unsigned short _port);

				/*!
					\brief stop protocol
					to stop the server
				*/
				void stop();

				/*!
					\brief update protocol
					to check for new connections, disconnections or messages
				*/
				void update();

				/*!
					\brief classic send protocol
					to send to only one client

					\param[in] clientid of type uint64_t : target identifier
					\param[in] data of type const unsigned char* : data to send
					\param[in] len of type unsigned int : data length
					
					\return true uf send successful, false otherwise
				*/
				bool sendTo(uint64_t clientid, const unsigned char* data, unsigned int len);

				/*!
					\brief send protocol
					to send to all clients

					\param[in] data of type const unsigned char* : data to send
					\param[in] len of type unsigned int : data length

					\return true if send successful, false otherwise
				*/
				bool sendToAll(const unsigned char* data, unsigned int len);

				/*!
					\brief reception protocol

					\return a Message object from the reception buffer or a Disconnection Message if it fails
				*/
				std::unique_ptr<Messages::Base> poll();

			private:
				std::unique_ptr<ServerImpl> mImpl;/*!< an Implement server*/
		};
	}
}

#endif

