#ifndef ENEMY_H
#define ENEMY_H

#include "health.h"
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>

class Enemy : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Enemy(QGraphicsItem* parent = nullptr);
    void selfDestruct();

    QTimer* timer;
public slots:
    void move();

private:
    Health m_health;
};

#endif // ENEMY_H
