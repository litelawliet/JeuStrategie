#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

#include <QtWidgets>

class FenPrincipale : public QMainWindow
{
    public:
    /**
     * @brief Constructeur par défaut
     */
    FenPrincipale();

    public slots:
        /**
         * @brief slot qui rejoint une partie préalablement créée
         */
        void joinGame();
        /**
         * @brief slot qui créé une partie
         */
        void createGame();

};

#endif
