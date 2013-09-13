#include "graphicalcreature.hpp"

#include <QtWidgets>

#include "utils.hpp"
#include "view.hpp"

GraphicalCreature::GraphicalCreature(const std::unique_ptr<Creature> &creature, qint16 scale) :
    Creature(*(creature.get())), scale(scale)
{
    setZValue((this->positionX + this->positionY) % 2);
    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
    setPos(this->positionX * scale, this->positionY * scale);

    if (this->species == 0)
        this->color = Qt::darkGreen;
    else if (this->species == 1)
        this->color = Qt::darkYellow;
    else if (this->species == 2)
        this->color = Qt::yellow;
    else if (this->species == 3)
        this->color = Qt::blue;
    else if (this->species == 4)
        this->color = Qt::gray;
    else if (this->species == 5)
        this->color = Qt::red;
    else if (this->species == 6)
        this->color = Qt::black;
}

QRectF GraphicalCreature::boundingRect() const
{
    return QRectF(0, 0, this->scale, this->scale);
}

#include <QDebug>
void GraphicalCreature::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Only draw at all if we're on the correct tick value.
    if (this->data(0).toUInt() == this->data(1).value<View*>()->getTickSliderValue())
    {
        const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
        if (lod > 0.35) {
            painter->save();
            painter->setOpacity(0.4);
            painter->setBrush(this->color);
            painter->drawRect(boundingRect());
            painter->restore();
            painter->drawPixmap(0, 0, *(this->pixmap));
        } else {
            painter->save();
            painter->setBrush(this->color);
            painter->drawEllipse(0, 0, this->scale, this->scale);
            painter->restore();
        }
    }
}

void GraphicalCreature::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void GraphicalCreature::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void GraphicalCreature::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}

QPixmap *GraphicalCreature::getPixmap() const
{
    return pixmap;
}

void GraphicalCreature::setPixmap(QPixmap *value)
{
    pixmap = value;
}
