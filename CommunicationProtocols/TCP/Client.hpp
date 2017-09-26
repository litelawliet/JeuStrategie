#pragma once

/*!
	\file Client.hpp
	\brief declaration of Client and ClientImpl
	\author Friday
*/

#include "Sockets.hpp"

#include <string>
#include <memory>

/*!
	\namespace Network
	\brief contains all network things
*/
namespace Network
{
	/*!
		\namespace Messages
		\brief contains all network messages things
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

		using HeaderType = uint16_t;/*!< type of message's header*/
		static const unsigned int HeaderSize = sizeof(HeaderType);/*!< size of message's header*/

		/*!
			\class ClientImpl Client.hpp Client
		*/
		class ClientImpl;

		/*!
			\Class Client Client.hpp Client
			\brief Client side's communication functions
		*/
		class Client
		{
			public:

				/*!
					\brief default constructor
				*/
				Client();

				/*!
					\brief copy constructor
				*/
				Client(const Client&) = delete;

				/*!
					\brief copy constructor
				*/
				Client& operator=(const Client&) = delete;

				/*!
					\brief copy constructor
				*/
				Client(Client&&);

				/*!
					\brief copy constructor
				*/
				Client& operator=(Client&&);

				/*!
					\brief default destructor
				*/
				~Client();

				/*!
					\brief client's initialisation protocol

					\param[in] sckt of type struct SOCKET&& : client's connection socket
					\param[in] addr of type sockaddr_in& : client's IP address

					\return true if initiation successful, false otherwise
				*/
				bool init(SOCKET&& sckt, const sockaddr_in& addr);

				/*!
					\brief client's connection protocol

					\param[in] ipaddress of type string& : server's address
					\param[in] port of type unsigned short : server's port

					\return true if connection established, false otherwise
				*/
				bool connect(const std::string& ipaddress, unsigned short port);

				/*!
					\brief client's disconnection protocol
				*/
				void disconnect();

				/*!
					\brief client's sending protocol
					
					\param[in] data of type unsigned char* : data to send
					\param[in] len of type unsigned int : data length

					\return true if send successful, false otherwise
				*/
				bool send(const unsigned char* data, unsigned int len);

				/*!
					\brief client's reception protocol

					\return Message object from reception buffer or a Disconnection Message object if it fails
				*/
				std::unique_ptr<Messages::Base> poll();

				/*!
					\brief to get client's id

					\return client's id
				*/
				uint64_t id() const;

				/*!
					\brief to get server's address

					\return address
				*/
				const sockaddr_in& destinationAddress() const;

			private:
				std::unique_ptr<ClientImpl> mImpl;
		};
	}
}