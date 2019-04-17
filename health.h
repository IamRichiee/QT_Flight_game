#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>
#include <QObject>

class Health : public QGraphicsTextItem {
    //    Q_OBJECT

public:
    Health(QGraphicsItem* parent = nullptr);
    void increase();
    void decrease();
    int getHealth();
    void setHealth(int initHealth);
    void display();
    void visivle(bool);

signals:
    void returnToZero();

public slots:
    void die();

private:
    int health;
    bool m_visible;
};

#endif // HEALTH_H
