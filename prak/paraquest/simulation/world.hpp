#ifndef WORLD_HPP
#define WORLD_HPP

#include <memory>
#include <map>
#include <string>

#include "creature.hpp"

class World
{
public:
    World(uint16_t sizeY, uint16_t sizeX);
    void addCreature(std::string type);
    // TODO
    // some container type getCollisions();
    void populate(uint32_t count);
    void simulate(uint32_t ticks);

private:
    std::multimap<uint32_t, std::unique_ptr<Creature>> creatures;
    uint16_t sizeX;
    uint16_t sizeY;
    uint32_t currentId; // ever-increasing number that uniquely identifies a creature
};

#endif // WORLD_HPP
