#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <QColor>
#include <QGraphicsItem>

class Creature : public QGraphicsItem
{
public:
    Creature(QString type, quint16 posX, quint16 posY, quint16 scale);

    void initCreature();
    void doAction();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    QString type;
    quint16 x;
    quint16 y;
    quint16 scale;
    quint16 strength;
    quint16 agility;
    quint16 intelligence;
    quint16 sociability;
    QColor color;
    QImage image;
    QVector<QPointF> stuff;
};

#endif // CREATURE_HPP
