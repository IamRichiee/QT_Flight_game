#include "button.h"
#include <QBrush>
#include <QDebug>
#include <QFont>
#include <QGraphicsTextItem>

Button::Button(QPixmap image, QPixmap hoverImage, QGraphicsItem* parent)
{
    Q_UNUSED(parent)
    icon = new QPixmap(image);
    hoverIcon = new QPixmap(hoverImage);
    // draw the rect
    QBrush brush(*icon);
    qDebug() << "draw rect";

    setPixmap(image);

    // responde hover
    setAcceptHoverEvents(true);
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (event)
        emit clicked();
}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
    if (event) {
        setPixmap(*hoverIcon);
    }
}

void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
    if (event) {
        setPixmap(*icon);
    }
}
