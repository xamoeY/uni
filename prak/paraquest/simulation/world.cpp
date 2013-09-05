#include "world.hpp"

#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>

#include "utils.hpp"

World::World(uint16_t size_x, uint16_t size_y, uint16_t comm_size, uint16_t comm_rank, char* processor_name) :
    sizeX(size_x), sizeY(size_y), commSize(comm_size), commRank(comm_rank), processorName(processor_name), currentId(0)
{}

void World::addCreature(std::string species)
{
    this->currentId++;

    // Generate random starting position
    const uint16_t x = randInt(0, this->sizeX - 1);
    const uint16_t y = randInt(0, this->sizeY - 1);

    // Generate spatial hash to use as map key
    const uint32_t hash = this->sizeX * y + x;

    // Add this new creature only if it doesn't collide with another creature already.
    // This also means that we'll likely be below our max creatures right from the start already.
    if (this->creatures.count(hash) == 0)
        this->creatures.emplace(hash, std::unique_ptr<Creature> (new Creature(species, this->currentId, x, y)));
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

    for(uint i = 1; i < ticks + 1; ++i)
    {
        // Make a new multimap after each tick and replace the old one with it after the tick.
        std::multimap<uint32_t, std::shared_ptr<Creature>> new_creatures;

        // Make every creature do something
        //for(auto &creature : this->creatures)
        for(auto it = creatures.cbegin(); it != creatures.cend(); ++it)
        {
            const uint16_t action = randInt(0, 4);

            std::pair<int8_t, int8_t> direction(0, 0);

            // wait             rocks don't move
            if (action == 0 || it->second->getSpecies() == "rock");

            // move east
            else if (action == 1) {
                if (it->second->getPosition().first + 1 < int32_t(this->sizeX))
                    direction = std::make_pair(1, 0);
            }

            // move south
            else if (action == 2) {
                if (it->second->getPosition().second + 1 < int32_t(this->sizeY))
                    direction = std::make_pair(0, 1);
            }

            // move west
            else if (action == 3) {
                if (it->second->getPosition().first - 1 >= 0)
                    direction = std::make_pair(-1, 0);
            }

            // move north
            else if (action == 4) {
                if (it->second->getPosition().second - 1 >= 0)
                    direction = std::make_pair(0, -1);
            }

            // Check whether our new position would lead to a collision with a rock
            uint32_t current_hash = Creature::getHash(this->sizeX, it->second->getPosition().first, it->second->getPosition().second);
            uint32_t new_hash = Creature::getHash(this->sizeX, it->second->getPosition().first + direction.first, it->second->getPosition().second + direction.second);

            // Only check if we have actually moved
            if (current_hash != new_hash)
            {
                // There is some kind of collision, check what type
                if (this->creatures.count(new_hash) > 0)
                {
                    auto c = this->creatures.find(new_hash)->second;
                    if (c->getSpecies() == "rock")
                    {
                        direction = std::make_pair(0, 0);
                        new_hash = current_hash;
                    }
                }
            }

            auto new_position = std::make_pair(it->second->getPosition().first + direction.first, it->second->getPosition().second + direction.second);
            it->second->setPosition(new_position);
            new_creatures.emplace(new_hash, std::move(it->second));
        }

        creatures = std::move(new_creatures);

        // Check for collisions
        // Use a second list to store iterators to collisions
        std::map<uint32_t, std::multimap<uint32_t, std::shared_ptr<Creature>>::const_iterator> collisions;
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
            creatures.erase(col.second);
        }

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
        archive(creatures);
        log.close();
    }
}
