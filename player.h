#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QObject>
#include <QSound>

class Player : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Player(QGraphicsItem* parent = nullptr);
    ~Player();
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
    void move();
    void setDir(QPoint direction);
    void die();
    bool isDie();
    void revive();
    QGraphicsItem* handle;
    QVector<QGraphicsItem*> enemyHandle;

public slots:
    void spawn();

private:
    QSound* bulletSound;
    bool m_isDie;
    QPoint dir;
    QTimer* timer;
};

#endif // PLAYER_H
