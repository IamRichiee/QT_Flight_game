#include "enemybullet.h"
#include "game.h"
#include "player.h"
#include <QGraphicsScene>
#include <QList>
#include <QTimer>

extern Game* game;

EnemyBullet::EnemyBullet(QGraphicsItem* parent)
    : QObject()
    , QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/enemybullt.png"));
    setTransformOriginPoint(boundingRect().width() / 2, boundingRect().height() / 2);
    setRotation(180);

    QTimer* timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout,
        this, &EnemyBullet::move);
    timer->start(50);
}

void EnemyBullet::move()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();

    // destroy the bullet and decrease the health
    for (QGraphicsItem* item : colliding_items) {
        if (typeid(*(item)) == typeid(Player)) {
            // decrease the health
            game->health->decrease();

            scene()->removeItem(this);

            delete this;

            return;
        }
    }

    // move the bullet forward
    setPos(x(), y() + 10);
    // destroy it
    if (pos().y() + pixmap().height() < 0) {
        scene()->removeItem(this);
        delete this;
    }
}
