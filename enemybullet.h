#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>

class EnemyBullet
    : public QObject,
      public QGraphicsPixmapItem {
    Q_OBJECT
public:
    EnemyBullet(QGraphicsItem* parent = nullptr);
public slots:
    void move();
};

#endif // BULLET_H
