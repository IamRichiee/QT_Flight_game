#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QIcon>
#include <QSound>

class Button : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Button(QGraphicsItem* parent = nullptr);
    Button(QPixmap image, QPixmap hoverImage, QGraphicsItem* parent = nullptr);

    //public methods

    //events
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
signals:
    void clicked();

private:
    QPixmap* icon;
    QPixmap* hoverIcon;
};
