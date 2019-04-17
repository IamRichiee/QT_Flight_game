#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QMediaPlayer>

class Player:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=nullptr);
    void keyPressEvent(QKeyEvent * event);
public slots:
    void spawn();
private:
    QMediaPlayer *bulletsoud;
};

#endif // PLAYER_H
