#ifndef GRAPHICALCREATURE_HPP
#define GRAPHICALCREATURE_HPP

#include "creature.hpp"

#include <QColor>
#include <QGraphicsItem>

class GraphicalCreature : public QGraphicsItem, public Creature
{
public:
    GraphicalCreature(const std::shared_ptr<Creature>& creature, qint16 scale=72);

    void updateGraphics();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget);

    QPixmap *getPixmap() const;
    void setPixmap(QPixmap *value);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    quint16 scale;
    QColor color;
    QPixmap *pixmap;
};

#endif // GRAPHICALCREATURE_HPP
