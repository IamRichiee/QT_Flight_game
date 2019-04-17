#include "enemy.h"
#include "game.h"
#include <QGraphicsScene>
#include <QList>
#include <QRandomGenerator>
#include <QTimer>

extern Game* game;

Enemy::Enemy(QGraphicsItem* parent)
    : QObject()
    , QGraphicsPixmapItem(parent)
{
    // set health
    m_health.setHealth(1);

    // set random x position
    int random_number = qrand() % game->gameSceneWidth - 100;
    setPos(random_number, 0);

    // drew the rect
    setPixmap(QPixmap(":/images/enemy.png"));
    setTransformOriginPoint(50, 50);
    setRotation(180);

    // make/connect a timer to move() the enemy every so often
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemy::move);

    // start the timer
    timer->start(50);
}

void Enemy::move()
{
    if (game->player->isDie()) {
        selfDestruct();
    }
    // move enemy down
    setPos(x(), y() + 5);

    // destroy enemy when it goes out of the screen
    if (pos().y() > game->gameSceneHeight) {
        // decrease the health
        game->health->decrease();

        scene()->removeItem(this);
        delete this;
        if (game->health->getHealth() <= 0) {
            game->gameOver();
        }
    }
}

void Enemy::selfDestruct()
{
    disconnect(timer, &QTimer::timeout, this, &Enemy::move);
    delete this;
}
