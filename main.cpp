#include <QApplication>
#include <QtWidgets>
#include "FenPrincipale.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //FenPrincipale fenetre;
    //fenetre.show();


    // Create a scene
    QGraphicsScene* scene = new QGraphicsScene();

    // Create an item to put in the scene
    QGraphicsRectItem* rect = new QGraphicsRectItem();
    rect->setRect(0, 0, 100, 100);


    // add the item to the scene
    scene->addItem(rect);

    // add a view
    QGraphicsView* view = new QGraphicsView(scene);

    view->show();

    return app.exec();
}
