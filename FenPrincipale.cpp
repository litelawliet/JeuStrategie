#include "FenPrincipale.h"
#include "ReceptionThread.h"
#include "SendingThread.h"
#include "HandlerThread.h"
#include <iostream>

FenPrincipale::FenPrincipale(std::string addr, int port)
{
    setFixedSize(300, 200);
    this->move(QApplication::desktop()->screen()->rect().center() - this->rect().center());
    QMenu* partie = menuBar()->addMenu("&Partie");

    QAction* actionCreerPartie = new QAction("&Créer partie", this);
    QAction* actionJoindrePartie = new QAction("Re&joindre partie", this);
    QAction* actionQuitter = new QAction("&Quitter", this);
    partie->addAction(actionJoindrePartie);
    partie->addAction(actionCreerPartie);
    partie->addAction(actionQuitter);

    actionJoindrePartie->setShortcut(QKeySequence("Ctrl+J"));
    actionCreerPartie->setShortcut(QKeySequence("Ctrl+C"));
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));

    connect(actionCreerPartie, &QAction::triggered, this, &FenPrincipale::createGame);
    connect(actionJoindrePartie, &QAction::triggered, this, &FenPrincipale::joinGame);
    connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

	if (!Network::Start())
	{
		std::cout << "Error starting sockets : " << Network::Errors::Get() << std::endl;
		qApp->quit();
	}

	if (!mClient.connect(addr, port))
	{
		std::cout << "Impossible de se connecter au serveur [" << addr << ":" << port << "] : " << Network::Errors::Get() << std::endl;
		qApp->quit();
	}
	comMutex=new QMutex(QMutex::RecursionMode::NonRecursive);
	rt = new ReceptionThread(*this);
	rt->start();
	st = new SendingThread(*this);
	st->start();
	ht = new HandlerThread(*this);
	ht->start();

}

FenPrincipale::~FenPrincipale() {
	rt->disconnect();
	st->disconnect();
	ht->disconnect();
	delete rt;
	delete st;
	delete ht;
	delete comMutex;
	Network::Release();
}

void FenPrincipale::joinGame() {
	//implémenter la vérification suivante : si on est déjà en création de partie ou qu'on a déjà rejoint alors rien ne se passe
	Network::Messages::JoinGame msg(Network::Messages::UserData::Result::Success);
	comMutex->lock();
	sendingQueue.push_back(msg.toUserData());
	comMutex->unlock();
}

void FenPrincipale::createGame() {
	//implémenter la vérification suivante : si on est déjà en création de partie ou qu'on a déjà rejoint alors rien ne se passe
	Network::Messages::CreateGame msg(Network::Messages::UserData::Result::Success);
	comMutex->lock();
	sendingQueue.push_back(msg.toUserData());
	comMutex->unlock();
}
