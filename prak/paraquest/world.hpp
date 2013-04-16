#ifndef WORLD_HPP
#define WORLD_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "creature.hpp"

class World
{
public:
    World();
    void addCreature(std::string type);
    void populate(uint32_t count);
    void simulate(uint32_t ticks);

private:
    std::vector<std::unique_ptr<Creature>> creatures;
};

#endif // WORLD_HPP
