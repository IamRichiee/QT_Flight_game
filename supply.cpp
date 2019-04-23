#include "supply.h"
#include "bullet.h"
#include "enemy.h"
#include "game.h"
#include <QGraphicsScene>
#include <QList>
#include <QTimer>

extern Game* game;

Supply::Supply(QGraphicsItem* parent)
    : QObject()
    , QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/supply.png"));

    QTimer* timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout,
        this, &Supply::move);
    timer->start(50);
}

void Supply::move()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();

    for (QGraphicsItem* item : colliding_items) {
        if (typeid(*(item)) == typeid(Player)) {
            // supply
            game->addSupply(this);

            scene()->removeItem(this);

            delete this;

            return;
        }
    }

    // move the supply forward
    setPos(x(), y() + 1);
    // destroy it
    if (pos().y() + pixmap().height() < 0) {
        scene()->removeItem(this);
        game->supplies.removeOne(this);
        delete this;
    }
}
