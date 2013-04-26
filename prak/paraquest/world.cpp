#include "world.hpp"

#include "utils.hpp"

World::World(quint16 sizeY, quint16 sizeX, quint16 scale, QGraphicsScene *scene) :
    sizeX(sizeX), sizeY(sizeY), scale(scale), scene(scene)
{
    // Make a grid
    for (int x = 0; x <= sizeX * scale; x += scale)
        scene->addLine(x, 0, x, sizeX * scale, QPen(Qt::black));
    for (int y = 0; y <= sizeY * scale; y += scale)
        scene->addLine(0, y, sizeY * scale, y, QPen(Qt::black));
}

void World::addCreature(QString type)
{
    quint16 x = randInt(0, this->sizeX);
    quint16 y = randInt(0, this->sizeY);

    creatures.push_back(std::unique_ptr<Creature> (new Creature(type, x, y, this->scale)));
    scene->addItem(creatures.back().get());
}

void World::populate(quint32 count)
{
    for(uint i = 0; i < count; ++i)
    {
        QList<QString> races {"goblin", "hobbit", "orc", "elf", "dwarf", "human"};
        addCreature(races[randInt(races.size() - 1)]);
    }
}

void World::simulate(quint32 ticks)
{
    for(uint i = 0; i < ticks; ++i)
        for(auto &creature : creatures)
            creature->doAction();
}
