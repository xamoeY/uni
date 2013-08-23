#ifndef WORLD_HPP
#define WORLD_HPP

#include <memory>
#include <map>
#include <string>

#include "creature.hpp"

class World
{
public:
    World(uint16_t size_x, uint16_t sizeY, uint16_t comm_size, uint16_t comm_rank, char* processor_name);
    void addCreature(std::string type);
    void populate(uint32_t count);
    void simulate(uint32_t ticks);
    void dumpState(uint32_t tick);

private:
    std::multimap<uint32_t, std::unique_ptr<Creature>> creatures;
    uint16_t sizeX;
    uint16_t sizeY;
    uint16_t commSize;
    uint16_t commRank;
    char* processorName;
    uint32_t currentId; // ever-increasing number that uniquely identifies a creature
};

#endif // WORLD_HPP
