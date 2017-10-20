#include "HandlerThread.h"
#include "FenPrincipale.h"


HandlerThread::HandlerThread(FenPrincipale* parent)
	: mParent(parent)
	, mMutex(parent->getComMutex())
	, mClient(mParent->getClient())
{
	setParent(0);
	moveToThread(this);
}


HandlerThread::~HandlerThread()
{
	delete mParent;
	delete mClient;
	delete mMutex;
}

void HandlerThread::run() {
	while (1) {
		while (!mParent->getReceivingQueue()->isEmpty()) {
			auto msg = mParent->getReceivingQueue()->first();
			mMutex->lock();
			mParent->getReceivingQueue()->pop_front();
			mMutex->unlock();
			//gestion du message reçu
			//queue d'un nouveau message dans mParent->getReceivingQueue()
		}
	}
}
