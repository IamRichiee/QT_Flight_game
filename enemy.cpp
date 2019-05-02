
#include "enemy.h"
#include "game.h"
#include <QGraphicsScene>
#include <QList>
#include <QRandomGenerator>
#include <QTimer>

extern Game* game;

Enemy::Enemy(QGraphicsItem* parent)
{
    Q_UNUSED(parent)

    // set health
    m_health.setHealth(1);

    setPixmap(QPixmap(":/images/enemy.png"));
    setOffset(-boundingRect().width(), 0);

    // set random x position
    auto randomNumber = qrand() % (game->gameSceneWidth - 128);
    setPos(randomNumber - 128, -boundingRect().height());

    // drew the rect
    setTransformOriginPoint(boundingRect().width() / 2, boundingRect().height() / 2);
    setRotation(180);

    // make/connect a timer to move() the enemy every so often
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Enemy::move);

    // start the timer
    timer->start(50);

    bulletTimer = new QTimer(this);
    connect(bulletTimer, &QTimer::timeout, this, &Enemy::shot);
    bulletTimer->start(1000);
}

void Enemy::move()
{
    if (game->player->isDie()) {
        selfDestruct();
    }
    QList<QGraphicsItem*> colliding_items = collidingItems();

    // destroy both the enemy and the player
    for (QGraphicsItem* item : colliding_items) {
        if (typeid(*(item)) == typeid(Player)) {

            scene()->removeItem(this);
            game->ex->setPos(game->player->x(), game->player->y());
            game->ex->start();
            game->gameOver();

            selfDestruct();
            return;
        }
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

void Enemy::shot()
{
    // create a bullet
    EnemyBullet* enemyBullet = new EnemyBullet();
    enemyBullet->setPos(x() + 1.5 * this->boundingRect().width(), y() + this->boundingRect().height());
    enemyBullet->setZValue(-1);

    scene()->addItem(enemyBullet);

    // playe EnemyBullet sounds
}
