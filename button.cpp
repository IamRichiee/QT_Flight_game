#include "button.h"
#include <QBrush>
#include <QFont>
#include <QGraphicsTextItem>

Button::Button(QString name, QGraphicsItem* parent)
    : QGraphicsRectItem(parent)
{
    //draw the rect
    setRect(0, 0, 200, 50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkRed);
    setBrush(brush);

    //draw Text
    text = new QGraphicsTextItem(name, this);
    text->setFont(QFont("Roboto", 25));
    int xPos = static_cast<int>(
        rect().width() / 2 - text->boundingRect().width() / 2);
    int yPos = static_cast<int>(
        rect().height() / 2 - text->boundingRect().height() / 2);
    text->setPos(xPos, yPos);
    text->setDefaultTextColor(Qt::white);

    //responde hover
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event)
        emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    // change color
    if (event) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::red);
        setBrush(brush);
    }
}
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    // change color
    if (event) {
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::darkRed);
        setBrush(brush);
    }
}
