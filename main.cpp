#include <QApplication>
#include <QtWidgets>
#include "FenPrincipale.h"

#include <QGraphicsView>
#include <QGraphicsScene>
//#include "myrect.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    FenPrincipale fenetre;
    fenetre.show();


    // Create a scene
    /*QGraphicsScene* scene = new QGraphicsScene();

    // Create an item to put in the scene
    MyRect* player = new MyRect();
    player->setRect(0, 0, 100, 100);


    // add the item to the scene
    scene->addItem(player);

    // make rect focusable
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // add a view
    QGraphicsView* view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    view->show();

     view->setFixedSize(800, 600);
    scene->setSceneRect(0, 0, 800, 600);

    player->setPos(view->width()/2, view->height()-player->rect().height());*/

    return app.exec();
}
