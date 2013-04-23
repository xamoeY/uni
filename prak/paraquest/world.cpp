#include "world.hpp"

#include "creature.hpp"

World::World(uint16_t sizex, uint16_t sizey) :
    m_sizex(sizex), m_sizey(sizey)
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
        addCreature("hobbit");
        addCreature("ork");
        addCreature("elf");
        addCreature("dwarf");
        addCreature("human");
}

void World::simulate(uint32_t ticks)
{
    for(uint i = 0; i < ticks; ++i)
        for(auto& creature : creatures)
            creature->doAction();
}
