#include "FenPrincipale.h"
#include <iostream>

FenPrincipale::FenPrincipale()
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
}

void FenPrincipale::joinGame() {
    if ( !Network::Start() )
        {
            std::cout << "Error starting sockets : " << Network::Errors::Get() << std::endl;
            qApp->quit();
        }

        Network::TCP::Client client;
        int port;
        std::cout << "Port du serveur ? ";
        std::cin >> port;
        if (!client.connect("127.0.0.1", port))
        {
            std::cout << "Impossible de se connecter au serveur [127.0.0.1:" << port << "] : " << Network::Errors::Get() << std::endl;
        }
        else
        {
            while (1)
            {
                while (auto msg = client.poll())
                {
                    if (msg->is<Network::Messages::Connection>())
                    {
                        auto connection = msg->as<Network::Messages::Connection>();
                        if (connection->result == Network::Messages::Connection::Result::Success)
                        {
                            std::cin.ignore();
                            std::cout << "Connecte!" << std::endl;
                            std::cout << "Entrez une phrase >";
                            std::string phrase;
                            std::getline(std::cin, phrase);
                            if (!client.send(reinterpret_cast<const unsigned char*>(phrase.c_str()), static_cast<unsigned int>(phrase.length())))
                            {
                                std::cout << "Erreur envoi : " << Network::Errors::Get() << std::endl;
                                break;
                            }
                        }
                        else
                        {
                            std::cout << "Connexion echoue : " << static_cast<int>(connection->result) << std::endl;
                            break;
                        }
                    }
                    else if (msg->is<Network::Messages::UserData>())
                    {
                        auto userdata = msg->as<Network::Messages::UserData>();
                        std::string reply(reinterpret_cast<const char*>(userdata->data.data()), userdata->data.size());
                        std::cout << "Reponse du serveur : " << reply << std::endl;
                        std::cout << ">";
                        std::string phrase;
                        std::getline(std::cin, phrase);
                        if (!client.send(reinterpret_cast<const unsigned char*>(phrase.c_str()), static_cast<unsigned int>(phrase.length())))
                        {
                            std::cout << "Erreur envoi : " << Network::Errors::Get() << std::endl;
                            break;
                        }
                    }
                    else if (msg->is<Network::Messages::Disconnection>())
                    {
                        auto disconnection = msg->as<Network::Messages::Disconnection>();
                        std::cout << "Deconnecte : " << static_cast<int>(disconnection->reason) << std::endl;
                        break;
                    }
                }
            }
        }
        Network::Release();
}

void FenPrincipale::createGame() {

}
