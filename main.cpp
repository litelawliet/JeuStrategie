#include <QApplication>
#include <QtWidgets>
#include "FenPrincipale.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include "myrect.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //FenPrincipale fenetre;
    //fenetre.show();


    // Create a scene
    QGraphicsScene* scene = new QGraphicsScene();

    // Create an item to put in the scene
    MyRect* rect = new MyRect();
    rect->setRect(0, 0, 100, 100);


    // add the item to the scene
    scene->addItem(rect);

    // make rect focusable
    rect->setFlag(QGraphicsItem::ItemIsFocusable);
    rect->setFocus();

    // add a view
    QGraphicsView* view = new QGraphicsView(scene);

    view->show();

    return app.exec();
}
