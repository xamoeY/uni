#include "world.hpp"

#include "creature.hpp"

World::World()
{
}

void World::addCreature(std::string type)
{
    creatures.push_back(std::unique_ptr<Creature> (new Creature(type)));
}

void World::populate(uint32_t count)
{
    for(uint i = 0; i < count; ++i)
        addCreature("goblin");
}

void World::simulate(uint32_t ticks)
{
    for(uint i = 0; i < ticks; ++i)
        for(auto& creature : creatures)
            creature->doAction();
}
