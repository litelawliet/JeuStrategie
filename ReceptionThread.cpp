#include "ReceptionThread.h"
#include "FenPrincipale.h"



ReceptionThread::ReceptionThread(FenPrincipale& parent)
	: mParent(parent)
	, mMutex(parent.getComMutex())
	, mClient(parent.getClient())
{
	setParent(0);
	moveToThread(this);
}


ReceptionThread::~ReceptionThread()
{
	delete mMutex;
}

void ReceptionThread::run() {
	while (1)
	{
		while (auto msg = mClient.poll())
		{
			if (msg->is<Network::Messages::Connection>())
			{
				auto connection = msg->as<Network::Messages::Connection>();
				if (connection->result == Network::Messages::Connection::Result::Success)
				{
					//Gestion connexion
				}
				else
				{
					break;
				}
			}
			else if (msg->is<Network::Messages::UserData>())
			{
				auto userdata = msg->as<Network::Messages::UserData>();
				mMutex->lock();
				mParent.getReceivingQueue()->push_back(*userdata);
				mMutex->unlock();
			}
			else if (msg->is<Network::Messages::Disconnection>())
			{
				auto disconnection = msg->as<Network::Messages::Disconnection>();
				//Gestion de déconnexion
			}
		}
	}
}