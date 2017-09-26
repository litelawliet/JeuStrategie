#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QPoint>
#include <QCursor>
#include <QGraphicsSceneEvent>
#include <QGraphicsScene>

#include <QDebug>

class MyRect : public QGraphicsRectItem
{
public:
    MyRect();

    void keyPressEvent(QKeyEvent * event);
};

#endif // MYRECT_H
