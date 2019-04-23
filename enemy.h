#ifndef ENEMY_H
#define ENEMY_H

#include "aircraft.h"
#include "enemybullet.h"

class Enemy : public Aircraft {
    Q_OBJECT
public:
    Enemy(QGraphicsItem* parent = nullptr);
    void selfDestruct();
    void shot();
    QTimer* bulletTimer;

public slots:
    void move();
};

#endif // ENEMY_H
