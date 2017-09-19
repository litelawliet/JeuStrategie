#include "FenPrincipale.h"

FenPrincipale::FenPrincipale()
{
    setFixedSize(300, 200);
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

}

void FenPrincipale::createGame() {

}
