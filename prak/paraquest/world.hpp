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
    World(uint16_t sizex, uint16_t sizey);
    void addCreature(std::string type);
    void populate(uint32_t count);
    void simulate(uint32_t ticks);

private:
    std::vector<std::unique_ptr<Creature>> creatures;
    uint16_t m_sizex;
    uint16_t m_sizey;
};

#endif // WORLD_HPP
