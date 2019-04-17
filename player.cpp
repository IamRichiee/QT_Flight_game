#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include <QGraphicsScene>
#include <QKeyEvent>

Player::Player(QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent)
    , handle(parent)
    , m_isDie(false)
{
    bulletsoud = new QMediaPlayer();
    bulletsoud->setMedia(QUrl(":/sounds/It_Devours.mp3"));

    setPixmap(QPixmap(":/images/player.png"));
}

void Player::keyPressEvent(QKeyEvent* event)
{
    // move the player left and right
    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A) {
        if (pos().x() > 0)
            setPos(x() - 10, y());
    } else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D) {
        if (pos().x() + 100 < 800)
            setPos(x() + 10, y());
    }
    // shoot with the spacebar
    else if (event->key() == Qt::Key_Space) {
        // create a bullet
        Bullet* bullet = new Bullet();
        bullet->setPos(x() + 56, y());
        bullet->setZValue(-1);

        scene()->addItem(bullet);

        // playe bullet sounds
        if (bulletsoud->state() == QMediaPlayer::PlayingState) {
            bulletsoud->setPosition(0);
        } else if (bulletsoud->state() == QMediaPlayer::StoppedState) {
            bulletsoud->play();
        }
    }
}

void Player::spawn()
{
    // create an enemy
    QGraphicsItem* parent = handle;
    Enemy* enemy = new Enemy(parent);
    enemyHandle.append(enemy);
    enemy->setZValue(-1);
    scene()->addItem(enemy);
}

void Player::die()
{
    this->setVisible(false);
    m_isDie = true;
}

bool Player::isDie()
{
    return m_isDie;
}

void Player::revive()
{
    m_isDie = false;
}
