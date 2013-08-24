#include "graphicalcreature.hpp"

#include <QtWidgets>

#include "utils.hpp"

GraphicalCreature::GraphicalCreature(const std::string &line, qint16 scale) :
    Creature(line), scale(scale)
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

    std::string image_name(convertSpecies(this->species) + ".png");
    this->image.load(image_name.c_str());
}

// This is not thread safe. Run in main thread.
void GraphicalCreature::updateGraphics()
{
    setPos(this->positionX * scale, this->positionY * scale);
}

QRectF GraphicalCreature::boundingRect() const
{
    //return QRectF(0, 0, 72, 72);
    return QRectF(0, 0, this->scale, this->scale);
}

#include <QDebug>
void GraphicalCreature::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    Q_UNUSED(option);

    /*
    QColor fillColor = (option->state & QStyle::State_Selected) ? color.dark(150) : color;
    if (option->state & QStyle::State_MouseOver)
        fillColor = fillColor.light(125);

    if (lod < 0.35) {
        if (lod < 0.125) {
            painter->fillRect(QRectF(0, 0, 110, 70), fillColor);
            return;
        }

        QBrush b = painter->brush();
        painter->setBrush(fillColor);
        painter->drawRect(13, 13, 97, 57);
        painter->setBrush(b);
        return;
    }

    QPen oldPen = painter->pen();
    QPen pen = oldPen;
    int width = 0;
    if (option->state & QStyle::State_Selected)
        width += 2;

    pen.setWidth(width);
    QBrush b = painter->brush();
    painter->setBrush(QBrush(fillColor.dark(option->state & QStyle::State_Sunken ? 120 : 100)));

    painter->drawRect(QRect(14, 14, 79, 39));
    painter->setBrush(b);
    */

    const qreal lod = option->levelOfDetailFromTransform(painter->worldTransform());
    if (lod > 0.35) {
        painter->save();
        painter->setOpacity(0.4);
        painter->setBrush(this->color);
        painter->drawRect(boundingRect());
        painter->restore();
        painter->drawImage(0, 0, QImage(std::string(":/images/" + convertSpecies(this->species) + ".png").c_str()));
    } else {
        painter->save();
        painter->setBrush(this->color);
        painter->drawEllipse(0, 0, this->scale, this->scale);
        painter->restore();
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
        //stuff << event->pos();
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
