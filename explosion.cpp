#include "explosion.h"
#include <QObject>
#include <QTimer>

Explosion::Explosion(QObject* parent)
    : explosionPixmap(QPixmap(":/images/explo.png"))
    , count(0)
{
    Q_UNUSED(parent)
    timer = new QTimer();
    QObject::connect(timer, &QTimer::timeout,
        this, &Explosion::changePixmap);
}

Explosion::Explosion(QPoint pos, QObject* parent)
{
    Q_UNUSED(parent)
    Explosion();
    setPos(pos.x(), pos.y());
}

void Explosion::start()
{
    changePixmap();
    timer->start(31);
}

void Explosion::changePixmap()
{
    currentPixmap = new QPixmap(explosionPixmap.copy(rec[count++]));

    if (count > 15) {
        QObject::disconnect(timer, &QTimer::timeout,
            this, &Explosion::changePixmap);
        delete this;
    }
    setPixmap(*currentPixmap);
}
