#include "world.hpp"

#include <iostream>
#include <fstream>

#include "utils.hpp"

World::World(uint16_t sizeY, uint16_t sizeX) :
    sizeX(sizeX), sizeY(sizeY)
{}

void World::addCreature(std::string type)
{
    this->currentId++;

    const uint16_t x = randInt(0, this->sizeX - 1);
    const uint16_t y = randInt(0, this->sizeY - 1);

    const uint32_t hash = this->sizeX * y + x;
    creatures.emplace(hash, std::unique_ptr<Creature> (new Creature(type, this->currentId, x, y,
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
    // Dump state once at very beginning
    dumpState(0);

    for(uint i = 1; i < ticks + 1; ++i)
    {
        // Make a new multimap after each tick and replace the old one with it after the tick.
        std::multimap<uint32_t, std::unique_ptr<Creature>> new_creatures;

//        std::cout << std::endl << "tick " << i << std::endl;

        // Make every creature do something
        for(auto &creature : creatures)
        {
            creature.second->doAction();
            const uint32_t hash = this->sizeX * creature.second->getPosition().second + creature.second->getPosition().first;
            new_creatures.emplace(hash, std::move(creature.second));
        }

        creatures = std::move(new_creatures); // TODO: Maybe memory leak here even though it's allocated on the stack?

        // debug output
        for(auto &creature : creatures)
        {
            std::cout << "    " << creature.first << " : <id " << creature.second->getId() <<
                         "> <pos " << creature.second->getPosition().first << "/" <<
                         creature.second->getPosition().second << ">" << std::endl;
        }

        // Check for collisions
        // Use a second list to store iterators to collisions
        std::map<uint32_t, std::multimap<uint32_t, std::unique_ptr<Creature>>::const_iterator> collisions;
        for(auto it = creatures.cbegin(); it != creatures.cend(); ++it)
        {
            if (creatures.count(it->first) > 1)
            {
                // Determine a random winner for now by giving it a random int that we will compare
                // with later on.
                const uint16_t winner = randInt(0, creatures.count(it->first) - 1);

                auto duplicates = creatures.equal_range(it->first);

                // We use this counter to determine which creatures to delete.
                // We don't delete the winner.
                uint16_t counter = 0;

                for(auto it_dup = duplicates.first; it_dup != duplicates.second; ++it_dup)
                {
                    if (counter != winner)
                        collisions[it->first] = it;
                    ++counter;
                }
            }
        }

        for(auto &col : collisions)
        {
//            std::cout << col.first << " " << col.second->second->getId() << std::endl;
            creatures.erase(col.second);
        }

        dumpState(i);
    }
}

// A file is dumped after each step of the simulation with the current contents of this node's world.
void World::dumpState(uint32_t tick)
{
    std::ofstream log("node1_tick" + std::to_string(tick) + ".log", std::ios::out | std::ios::app);
    if(log.is_open())
    {
        for(auto &creature : creatures)
        {
            log << creature.second->serialize() << std::endl;
        }

        log.close();
    }
}
