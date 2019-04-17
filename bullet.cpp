#include "bullet.h"
#include "enemy.h"
#include "game.h"
#include <QGraphicsScene>
#include <QList>
#include <QTimer>

extern Game* game;

Bullet::Bullet(QGraphicsItem* parent)
    : QObject()
    , QGraphicsPixmapItem(parent)
{
    setPixmap(QPixmap(":/images/bullet.png"));

    QTimer* timer = new QTimer(this);
    QObject::connect(timer, &QTimer::timeout,
        this, &Bullet::move);
    timer->start(50);
}

void Bullet::move()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();

    // destroy both the bullet and the enemy
    for (QGraphicsItem* item : colliding_items) {
        if (typeid(*(item)) == typeid(Enemy)) {
            // increase the score
            game->score->increase();

            scene()->removeItem(item);
            scene()->removeItem(this);

            delete item;
            delete this;

            return;
        }
    }

    // move the bullet forward
    setPos(x(), y() - 10);
    // destroy it
    if (pos().y() + pixmap().height() < 0) {
        scene()->removeItem(this);
        delete this;
    }
}
