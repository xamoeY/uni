#ifndef WORLD_HPP
#define WORLD_HPP

#include <memory>
#include <vector>

#include <QGraphicsScene>

#include "creature.hpp"

class World
{
public:
    World(quint16 sizeY, quint16 sizeX, quint16 scale, QGraphicsScene *scene);
    void addCreature(QString type);
    // TODO
    // some container type getCollisions();
    void populate(quint32 count);
    void simulate(quint32 ticks);
    // TODO
    // std::pair<uint16_t> getWorldSize();

private:
    std::vector<std::unique_ptr<Creature>> creatures;
    uint16_t sizeX;
    uint16_t sizeY;
    uint16_t scale;
    QGraphicsScene *scene;
};

#endif // WORLD_HPP
