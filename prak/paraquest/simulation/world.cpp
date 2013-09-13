#include "world.hpp"

#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>

#include "utils.hpp"

World::World(uint16_t size_x, uint16_t size_y, uint16_t comm_size, uint16_t comm_rank, char* processor_name) :
    sizeX(size_x), sizeY(size_y), commSize(comm_size), commRank(comm_rank), processorName(processor_name), currentId(0)
{}

std::vector<Creature*> World::getCreaturesAt(uint16_t x, uint16_t y)
{
    std::vector<Creature*> results;
    for(const auto &creature : this->creatures)
    {
        if (creature->getPosition().first == x && creature->getPosition().second == y)
            results.push_back(creature.get());
    }

    return results;
}

void World::addCreature(std::string species)
{
    this->currentId++;

    // Generate random starting position
    const uint16_t x = randInt(0, this->sizeX - 1);
    const uint16_t y = randInt(0, this->sizeY - 1);

    // Add this new creature only if it doesn't collide with another creature already.
    // This also means that we'll likely be below our max creatures right from the start already.
    if (getCreaturesAt(x, y).empty())
        this->creatures.emplace_back(std::unique_ptr<Creature> (new Creature(species, this->currentId, x, y)));
}

void World::populate(uint32_t creature_count, uint32_t obstacle_count)
{
    // Seed the world with obstacles
    for(uint i = 0; i < obstacle_count; ++i)
    {
        // Yes, rocks are creatures, think pet rocks :)
        addCreature("rock");
    }

    // Seed the world with creatures
    for(uint i = 0; i < creature_count; ++i)
    {
        std::vector<std::string> races {"goblin", "hobbit", "orc", "elf", "dwarf", "human"};
        addCreature(races[randInt(races.size() - 1)]);
    }
}

void World::simulate(uint32_t ticks)
{
    // Dump global world settings once
    dumpSettings(ticks);

    // Dump state once at very beginning
    dumpState(0, ticks);

    // Tick loop
    for(uint i = 1; i < ticks + 1; ++i)
    {
        // Make every creature do something
        for(auto &creature : this->creatures)
        {
            const uint16_t action = randInt(0, 4);

            std::pair<int16_t, int16_t> direction(0, 0);

            // wait             rocks don't move
            if (action == 0 || creature->getSpecies() == "rock")
            {
            }

            // move east
            else if (action == 1)
            {
                if (creature->getPosition().first + 1 < int32_t(this->sizeX))
                {
                    direction = std::make_pair(1, 0);
                }
            }

            // move south
            else if (action == 2)
            {
                if (creature->getPosition().second + 1 < int32_t(this->sizeY))
                {
                    direction = std::make_pair(0, 1);
                }
            }

            // move west
            else if (action == 3)
            {
                if (creature->getPosition().first - 1 >= 0)
                {
                    direction = std::make_pair(-1, 0);
                }
            }

            // move north
            else if (action == 4)
            {
                if (creature->getPosition().second - 1 >= 0)
                {
                    direction = std::make_pair(0, -1);
                }
            }

            // Check whether our new position would lead to a collision with a rock
            auto new_position = std::make_pair(creature->getPosition().first + direction.first, creature->getPosition().second + direction.second);

            // Only check if we have actually moved
            if (!(creature->getPosition().first == new_position.first && creature->getPosition().second == new_position.second))
            {
                // There is some kind of collision, check what type
                auto colliding = getCreaturesAt(new_position.first, new_position.second);
                if (colliding.size() > 0)
                {
                    for (auto c : colliding)
                    {
                        if (c->getSpecies() == "rock")
                            direction = std::make_pair(0, 0);
                    }
                }
            }

            // Calculate final new_position
            new_position = std::make_pair(creature->getPosition().first + direction.first, creature->getPosition().second + direction.second);
            creature->setPosition(new_position);
        }

        // Check for collisions
        // Use a second list to store iterators to scheduled deletions
//        std::vector<std::vector<std::unique_ptr<Creature>>::const_iterator> deletions;

        /*
        // Since we're using multimap that uses spacial hashes for the key, we can iterate
        // over all keys to check which keys have duplicate values. If that is the case, we take
        // a closer look and run the actual battle resolution.
        for(auto it = creatures.begin(); it != creatures.end(); ++it)
        {
            uint32_t position = it->first;

            // Check whether we have multiple creatures standing on this position
            if (creatures.count(position) > 1)
            {
                // This variable is getting filled with a range that contains all creatures on this
                // spatial position
                auto duplicates = creatures.equal_range(position);

                // Transfer range of collisions into a list of iterators for easier handling
                //std::vector<std::multimap<uint32_t, std::unique_ptr<Creature>>::const_iterator> collisions;
                for(auto it_dup = duplicates.first; it_dup != duplicates.second; ++it_dup)
                {
                    //creatures.erase(it_dup);

                    //deletions.push_back(it);
                    // Lock 2 creatures into a fight with each other

                    // TODO add hp fighting system somewhere here
                    //if (counter != winner)
                    //    deletions.push_back(it_dup);
                    //++counter;
                }
            }
        }
        */

        // Delete all creatures that are scheduled for deletion
//        for(auto &creature : deletions)
//        {
//            creatures.erase(creature);
//        }

        dumpState(i, ticks);
    }
}

// Dumps the world properties to a file.
void World::dumpSettings(uint32_t max_tick)
{
    // Create a specially named file name in the following syntax:
    // world.log
    std::ostringstream filename;
    filename << "world.properties";
    std::ofstream log(filename.str());

    // Dump world settings.
    if(log.is_open())
    {
        cereal::BinaryOutputArchive archive(log);
        archive(this->sizeX, this->sizeY, max_tick);
        log.close();
    }
}

// A file is dumped after each step of the simulation with the current contents of this node's world.
void World::dumpState(uint32_t tick, uint32_t max_tick)
{
    // Create a specially named file name in the following syntax:
    // <node_name>-<node_rank>_tick-<tick_number>.log
    // The setw commands are used to pad the number with leading zeroes for easier parsing.
    std::ostringstream filename;
    filename << std::setfill('0')
             << this->processorName << "-"
             << std::setw(std::to_string(this->commSize).length()) << this->commRank
             << "_tick" << "-" << std::setw(std::to_string(max_tick).length()) << tick
             << ".log";
    std::ofstream log(filename.str());

    // Dump all of the current creatures into the log.
    if(log.is_open())
    {
        cereal::BinaryOutputArchive archive(log);
        archive(this->creatures);
        log.close();
    }
}
