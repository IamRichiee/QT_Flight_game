#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>

class Explosion : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Explosion(QObject* parent = nullptr);
    Explosion(QPoint pos, QObject* parent = nullptr);
    void start();

    QPixmap explosionPixmap;
    QPixmap* currentPixmap;
    int count;
    QTimer* timer;

public slots:
    void changePixmap();
};

constexpr static QRect rec[] = {
    QRect(0, 0, 64, 64),
    QRect(64, 0, 64, 64),
    QRect(128, 0, 64, 64),
    QRect(192, 0, 64, 64),

    QRect(0, 64, 64, 64),
    QRect(64, 64, 64, 64),
    QRect(128, 64, 64, 64),
    QRect(192, 64, 64, 64),

    QRect(0, 128, 64, 64),
    QRect(64, 128, 64, 64),
    QRect(128, 128, 64, 64),
    QRect(192, 128, 64, 64),

    QRect(0, 192, 64, 64),
    QRect(64, 192, 64, 64),
    QRect(128, 192, 64, 64),
    QRect(192, 192, 64, 64),
};

#endif // EXPLOSION_H
