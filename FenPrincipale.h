#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

#include <QtWidgets>

#include "CommunicationProtocols/Sockets.hpp"
#include "CommunicationProtocols/TCP/Server.hpp"
#include "CommunicationProtocols/Messages.hpp"
#include "CommunicationProtocols/Errors.hpp"
#include "CommunicationProtocols/TCP/Client.hpp"

#include <QQueue>
#include <QThread>
#include <QMutex>

class ReceptionThread;
class SendingThread;
class HandlerThread;

class FenPrincipale : public QMainWindow
{
    public:
    /**
     * @brief Constructeur par défaut
     */
    FenPrincipale(std::string add, int port);

	~FenPrincipale();

    public slots:
        /**
         * @brief slot qui rejoint une partie préalablement créée
         */
        void joinGame();
        /**
         * @brief slot qui créé une partie
         */
        void createGame();

		Network::TCP::Client& getClient() { return mClient; }

		QMutex* getComMutex() { return comMutex; }

		QQueue<Network::Messages::UserData>* getSendingQueue() { return &sendingQueue; }

		QQueue<Network::Messages::UserData>* getReceivingQueue() { return &receivingQueue; }

	private:

		Network::TCP::Client mClient;/*!< client to communicate with the server*/
		QQueue<Network::Messages::UserData> sendingQueue;/*!< Messages to send queue*/
		QQueue<Network::Messages::UserData> receivingQueue;/*!< Received messages queue*/
		QMutex* comMutex;/*!< global mutex*/
		HandlerThread* ht;
		ReceptionThread rt;
		SendingThread st;
};

#endif
