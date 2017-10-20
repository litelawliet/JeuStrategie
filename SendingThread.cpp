#include "SendingThread.h"
#include "FenPrincipale.h"



SendingThread::SendingThread(FenPrincipale* parent)
	: mParent(parent)
	, mMutex(parent->getComMutex())
	, mClient(mParent->getClient())
{
	setParent(0);
	moveToThread(this);
}


SendingThread::~SendingThread()
{
	delete mParent;
	delete mClient;
	delete mMutex;
}

void SendingThread::run() {
	while (1) {
		while (!mParent->getSendingQueue()->isEmpty()) {
			auto msg = mParent->getSendingQueue()->first();
			if (!mClient->send(msg.data.data(), msg.data.size())) {
				//Gestion d'erreur d'envoi
			}
			else
			{
				mMutex->lock();
				mParent->getSendingQueue()->pop_front();
				mMutex->unlock();
			}
		}
	}
}