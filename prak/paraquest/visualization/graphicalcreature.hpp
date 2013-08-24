#ifndef GRAPHICALCREATURE_HPP
#define GRAPHICALCREATURE_HPP

#include "creature.hpp"

#include <QColor>
#include <QGraphicsItem>

class GraphicalCreature : public QGraphicsItem, public Creature
{
public:
    GraphicalCreature(const std::string &line, qint16 scale);

    void updateGraphics();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    quint16 scale;
    QColor color;
    QImage image;
};

#endif // GRAPHICALCREATURE_HPP
