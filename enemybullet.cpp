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
    setPixmap(QPixmap(":/images/enemybullet.png"));

    QTimer* timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout,
        this, &EnemyBullet::move);
    timer->start(50);
}

void EnemyBullet::move()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();

    // destroy both the bullet and the enemy
    for (QGraphicsItem* item : colliding_items) {
        if (typeid(*(item)) == typeid(Player)) {
            // increase the score
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
