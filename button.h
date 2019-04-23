#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QIcon>

class Button : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Button(QString name, QGraphicsItem* parent = nullptr);
    Button(QPixmap image, QPixmap hoverImage, QGraphicsItem* parent = nullptr);

    //public methods

    //events
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
signals:
    void clicked();

private:
    bool isText;
    QGraphicsTextItem* text;
    QPixmap icon;
    QPixmap hoverIcon;
};

#endif // BUTTON_H
