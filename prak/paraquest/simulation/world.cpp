#include "world.hpp"

#include <iostream>

#include "utils.hpp"

World::World(uint16_t sizeY, uint16_t sizeX) :
    sizeX(sizeX), sizeY(sizeY)
{}

void World::addCreature(std::string type)
{
    this->currentId++;

    uint16_t x = randInt(0, this->sizeX);
    uint16_t y = randInt(0, this->sizeY);

    uint32_t hash = this->sizeX * y + x;
    creatures.emplace(hash, std::unique_ptr<Creature> (new Creature(type, this->currentId,
                                                                    x, y,
                                                                    this->sizeX, this->sizeY)));
}

void World::populate(uint32_t count)
{
    for(uint i = 0; i < count; ++i)
    {
        std::vector<std::string> races {"goblin", "hobbit", "orc", "elf", "dwarf", "human"};
        addCreature(races[randInt(races.size() - 1)]);
    }
}

void World::simulate(uint32_t ticks)
{
    for(uint i = 0; i < ticks; ++i)
    {
        std::cout << "tick " << i << std::endl;
        for(auto &creature : creatures)
        {
            std::cout << "  creature " << creature.first << std::endl;
            creature.second->doAction();
        }
    }
}
