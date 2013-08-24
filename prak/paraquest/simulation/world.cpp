#include "world.hpp"

#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include "utils.hpp"

World::World(uint16_t size_x, uint16_t size_y, uint16_t comm_size, uint16_t comm_rank, char* processor_name) :
    sizeX(size_x), sizeY(size_y), commSize(comm_size), commRank(comm_rank), processorName(processor_name)
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
    dumpState(0, ticks);

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
        /*
        for(auto &creature : creatures)
        {
            std::cout << "    " << creature.first << " : <id " << creature.second->getId() <<
                         "> <pos " << creature.second->getPosition().first << "/" <<
                         creature.second->getPosition().second << ">" << std::endl;
        }*/

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

        dumpState(i, ticks);
    }
}

// A file is dumped after each step of the simulation with the current contents of this node's world.
void World::dumpState(uint32_t tick, uint32_t max_tick)
{
    std::ostringstream filename;
    filename << std::setfill('0')
             << this->processorName << std::setw(std::to_string(this->commSize).length()) << this->commRank
             << "_tick" << std::setw(std::to_string(max_tick).length()) << tick
             << ".log";
    std::ofstream log(filename.str(), std::ios::out);

    if(log.is_open())
    {
        /*
        // Before first tick, print general info about this node that won't change during runtime
        if(tick == 0)
        {
            log << "world_size_x:" << this->sizeX
                << " world_size_y:" << this->sizeY
                << std::endl;
        }*/

        for(auto &creature : creatures)
        {
            log << creature.second->serialize() << std::endl;
        }

        log.close();
    }
}
