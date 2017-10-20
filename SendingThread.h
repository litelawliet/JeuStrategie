#pragma once

#include "CommunicationProtocols/Sockets.hpp"
#include "CommunicationProtocols/TCP/Server.hpp"
#include "CommunicationProtocols/Messages.hpp"
#include "CommunicationProtocols/Errors.hpp"
#include "CommunicationProtocols/TCP/Client.hpp"

#include <QThread>
#include <QMutex>

class FenPrincipale;
class SendingThread : public QThread
{
public:
	SendingThread(FenPrincipale* parent);
	~SendingThread();
protected:
	void run();
private:
	QMutex* mMutex;
	Network::TCP::Client* mClient;/*!< client to use*/
	FenPrincipale* mParent;/*!< thread's parent*/
};

