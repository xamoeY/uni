#include "history.hpp"

#include "utils.hpp"

History::History(quint16 sizeY, quint16 sizeX, quint16 scale, QGraphicsScene *scene) :
    sizeX(sizeX), sizeY(sizeY), scale(scale), scene(scene)
{
    // Make a grid
    for (int x = 0; x <= sizeX * scale; x += scale)
        scene->addLine(x, 0, x, sizeX * scale, QPen(Qt::black));
    for (int y = 0; y <= sizeY * scale; y += scale)
        scene->addLine(0, y, sizeY * scale, y, QPen(Qt::black));
}

void History::parseHistory(const std::string &path)
{

}

void History::addCreature(QString type)
{
    creatures.push_back(std::unique_ptr<Creature> (new Creature(type, this->scale,
                                                                this->sizeX, this->sizeY)));
    scene->addItem(creatures.back().get());
}