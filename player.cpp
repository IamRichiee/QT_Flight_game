#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "game.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include <qtimer.h>
extern Game* game;
Player::Player(QGraphicsItem* parent)
    : QGraphicsPixmapItem(parent)
    , handle(parent)
    , m_isDie(false)
{
    bulletsoud = new QMediaPlayer();
    dir = QPoint(0, 0);
    bulletsoud->setMedia(QUrl(":/sounds/It_Devours.mp3"));

    setPixmap(QPixmap(":/images/player.png"));

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Player::move);
    timer->start(50);
}

Player::~Player()
{
    disconnect(timer, &QTimer::timeout, this, &Player::move);
}

void Player::keyPressEvent(QKeyEvent* event)
{
    if (!event->isAutoRepeat()) {
        // move the player left and right
        if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A) {
            if (pos().x() > 0)
                setDir(QPoint(-10, 0));
        } else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D) {
            if (pos().x() + 100 < 800)
                setDir(QPoint(10, 0));
        } else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W) {
            setDir(QPoint(0, -10));
        } else if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S) {
            setDir(QPoint(0, 10));
        }
        // shoot with the spacebar
        else if (event->key() == Qt::Key_Space) {
            // create a bullet
            Bullet* bullet = new Bullet(handle);
            bullet->setOffset(-bullet->boundingRect().width() / 2, 0);
            bullet->setPos(x(), y());
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
}

void Player::keyReleaseEvent(QKeyEvent* event)
{
    if (!event->isAutoRepeat()) {
        if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A) {
            setDir(QPoint(10, 0));
        } else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D) {
            setDir(QPoint(-10, 0));
        } else if (event->key() == Qt::Key_Up || event->key() == Qt::Key_W) {
            setDir(QPoint(0, 10));
        } else if (event->key() == Qt::Key_Down || event->key() == Qt::Key_S) {
            setDir(QPoint(0, -10));
        }
    }
}

void Player::setDir(QPoint direction)
{
    dir += direction;
}

void Player::move()
{
    auto xPos = x() + dir.x();
    auto yPos = y() + dir.y();
    if (xPos < 0 || xPos > game->gameSceneWidth
        || yPos < 0 || yPos > game->gameSceneWidth)
        return;
    setPos(xPos, yPos);
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
