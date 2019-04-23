#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include "health.h"
#include <QGraphicsItem>
#include <QObject>
#include <qgraphicsitem.h>

class Aircraft : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Aircraft(QGraphicsItem* parent = nullptr);
    QTimer* timer;
    Health m_health;

public slots:
    virtual void move() = 0;
};

#endif // AIRCRAFT_H
