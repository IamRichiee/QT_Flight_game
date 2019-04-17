#include "health.h"
#include <QFont>

Health::Health(QGraphicsItem* parent)
    : QGraphicsTextItem(parent)
    , health(3)
    , m_visible(false)
{
    display();
    setDefaultTextColor(Qt::red);
    setFont(QFont("Roboto", 18));
}

void Health::increase()
{
    ++health;
    display();
}

void Health::decrease()
{
    health--;
    display();
}

int Health::getHealth()
{
    return health;
}

void Health::setHealth(int initHealth)
{
    health = initHealth;
    display();
}

void Health::display()
{
    if (m_visible) {
        setPlainText(QString("Health: ") + QString::number(health));
    }
}

void Health::visivle(bool vis)
{
    m_visible = vis;
}

void Health::die()
{
    return;
}
