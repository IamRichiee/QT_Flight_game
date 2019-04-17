#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QObject>

class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Player(QGraphicsItem* parent = nullptr);
    void keyPressEvent(QKeyEvent* event);
    void die();
    bool isDie();
    void revive();
    QGraphicsItem* handle;
    QVector<QGraphicsItem*> enemyHandle;

public slots:
    void spawn();

private:
    QMediaPlayer* bulletsoud;
    bool m_isDie;
};

#endif // PLAYER_H
