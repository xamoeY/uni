#include "creature.hpp"

#include <QtWidgets>

#include "utils.hpp"

Creature::Creature(QString type, quint16 posX, quint16 posY, quint16 scale) :
    type(type), x(posX), y(posY), scale(scale)
{
    setZValue((this->x + this->y) % 2);

    setFlags(ItemIsSelectable | ItemIsMovable);
    setAcceptHoverEvents(true);
    setPos(this->x * scale, this->y * scale);

    initCreature();
}

void Creature::initCreature()
{
    if (this->type == "goblin")
    {
        this->strength = 210;
        this->agility = 210;
        this->intelligence = 100;
        this->sociability = 80;
        this->color = Qt::darkGreen;
    }

    if (this->type == "hobbit")
    {
        this->strength = 120;
        this->agility = 230;
        this->intelligence = 130;
        this->sociability = 120;
        this->color = Qt::darkYellow;
    }

    if (this->type == "orc")
    {
        this->strength = 210;
        this->agility = 200;
        this->intelligence = 95;
        this->sociability = 95;
        this->color = Qt::yellow;
    }

    if (this->type == "elf")
    {
        this->strength = 105;
        this->agility = 150;
        this->intelligence = 235;
        this->sociability = 110;
        this->color = Qt::blue;
    }

    if (this->type == "dwarf")
    {
        this->strength = 195;
        this->agility = 185;
        this->intelligence = 170;
        this->sociability = 50;
        this->color = Qt::gray;
    }

    if (this->type == "human")
    {
        this->strength = 150;
        this->agility = 75;
        this->intelligence = 180;
        this->sociability = 195;
        this->color = Qt::red;
    }

    this->image.load(type + ".png");
}

//TODO action rules
void Creature::doAction()
{
    // TODO
    // random actions: wait, walk, fight
}

QRectF Creature::boundingRect() const
{
    //return QRectF(0, 0, 72, 72);
    return QRectF(0, 0, this->scale, this->scale);
}

#include <QDebug>
void Creature::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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
        painter->drawImage(0, 0, QImage(":/images/" + this->type + ".png"));
    } else {
        painter->save();
        painter->setBrush(this->color);
        painter->drawEllipse(0, 0, this->scale, this->scale);
        painter->restore();
    }
}

void Creature::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
    update();
}

void Creature::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->modifiers() & Qt::ShiftModifier) {
        stuff << event->pos();
        update();
        return;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void Creature::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseReleaseEvent(event);
    update();
}
