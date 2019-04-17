#include "player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "bullet.h"
#include "enemy.h"

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    bulletsoud = new QMediaPlayer();
    bulletsoud->setMedia(QUrl(":/sounds/It_Devours.mp3"));

    setPixmap(QPixmap(":/images/player.png"));
}

void Player::keyPressEvent(QKeyEvent *event){
    // move the player left and right
    if (event->key() == Qt::Key_Left){
        if (pos().x() > 0)
        setPos(x()-10,y());
    }
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + 100 < 800)
        setPos(x()+10,y());
    }
    // shoot with the spacebar
    else if (event->key() == Qt::Key_Space){
        // create a bullet
        Bullet * bullet = new Bullet();
        bullet->setPos(x() + 56,y());

        scene()->addItem(bullet);

        // playe bullet sounds
        if (bulletsoud->state() == QMediaPlayer::PlayingState) {
            bulletsoud->setPosition(0);
        } else if (bulletsoud->state() == QMediaPlayer::StoppedState) {
            bulletsoud->play();
        }
    }
}

void Player::spawn(){
    // create an enemy
    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);
}
