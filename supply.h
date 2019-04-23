#ifndef SUPPLY_H
#define SUPPLY_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QObject>

class Supply
    : public QObject,
      public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Supply(QGraphicsItem* parent = nullptr);
public slots:
    void move();
};

#endif // SUPPLY_H
