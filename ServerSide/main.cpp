//#include "../CommunicationProtocols/commsock.h"
#include "../CommunicationProtocols/Sockets.hpp"
#include "../CommunicationProtocols/TCP/Server.hpp"
#include "../CommunicationProtocols/Messages.hpp"
#include "../CommunicationProtocols/Errors.hpp"
#include "../Game/Game.hpp"
#include "ServerSide\handler.h"


#include <iostream>

int main()
{
	if (!Network::Start())
	{
		std::cout << "Winsock initialisation error : " << Network::Errors::Get();
		return -1;
	}

	unsigned short port;
	std::cout << "Port ? ";
	std::cin >> port;

	Network::TCP::Server server;
	ServerSide serverside(&server);
	if (!server.start(port))
	{
		std::cout << "Server initialisation error : " << Network::Errors::Get();
		return -2;
	}
	while (1) {
		serverside.update();
		while (auto msg = server.poll())
		{
			if (msg->is<Network::Messages::Connection>())
			{
				std::cout << "[" << Network::GetAddress(msg->from) << ":" << Network::GetPort(msg->from) << "] connected\n";
			}
			else if (msg->is<Network::Messages::Disconnection>())
			{
				std::cout << "[" << Network::GetAddress(msg->from) << ":" << Network::GetPort(msg->from) << "] disconnected\n";
			}
			else if (msg->is<Network::Messages::UserData>())
			{
				Network::Messages::UserData userdata(*msg->as<Network::Messages::UserData>());
				std::cout << "Reception of [" << Network::GetAddress(userdata.from) << ":" << Network::GetPort(userdata.from) << "] with id[" << userdata.idFrom << "] of type[" << userdata.data[0] << "]\n";
				Network::Messages::Base realmsg = userdata.toRealType();

				Network::Messages::Base resendmsg = handle(&serverside, realmsg);

				Network::Messages::UserData datas = resendmsg.toUserData();

				server.sendToAll(datas.data.data(), static_cast<unsigned int>(datas.data.size()));
			}
		}
	}
	server.stop();
	Network::Release();
	return 0;
}