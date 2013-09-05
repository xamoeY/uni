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
    void addCreature(std::string species);
    void populate(uint32_t creature_count, uint32_t obstacle_count);
    void simulate(uint32_t ticks);
    void dumpSettings(uint32_t max_tick);
    void dumpState(uint32_t tick, uint32_t max_tick);

private:
    std::multimap<uint32_t, std::shared_ptr<Creature>> creatures; // TODO: Use unique_ptr again here once cereal is fixed
    uint16_t sizeX;
    uint16_t sizeY;
    uint16_t commSize;
    uint16_t commRank;
    char* processorName;
    uint32_t currentId; // ever-increasing number that uniquely identifies a creature
};

#endif // WORLD_HPP
