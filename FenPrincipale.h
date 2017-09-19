#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

#include <QtWidgets>

class FenPrincipale : public QMainWindow
{
    public:
    FenPrincipale();

    public slots:
        void joinGame();
        void createGame();

};

#endif
