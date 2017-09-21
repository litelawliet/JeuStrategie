#ifndef MYRECT_H
#define MYRECT_H

#include <QGraphicsRectItem>
#include <QKeyEvent>

class MyRect : public QGraphicsRectItem
{
public:
    MyRect();

    void keyPressEvent(QKeyEvent * event);
};

#endif // MYRECT_H
