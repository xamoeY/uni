#include "world.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <set>

#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>

#include "utils.hpp"

World::World(uint16_t size_x, uint16_t size_y, uint16_t comm_size, uint16_t comm_rank, char* processor_name) :
    sizeX(size_x), sizeY(size_y), commSize(comm_size), commRank(comm_rank), processorName(processor_name), currentId(0)
{}

std::vector<std::vector<std::unique_ptr<Creature>>::iterator> World::getCreaturesAt(uint16_t x, uint16_t y)
{
    std::vector<std::vector<std::unique_ptr<Creature>>::iterator> results;

    for(auto it = this->creatures.begin(); it != this->creatures.end(); ++it)
    {
        if ((*it)->getPosition().first == x && (*it)->getPosition().second == y)
            results.push_back(it);
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
        // debug
        std::cout << "tick: " << i << " | creatures: " << this->creatures.size() << std::endl;

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
            // or to more than 2 creatures on the same tile
            auto new_position = std::make_pair(creature->getPosition().first + direction.first, creature->getPosition().second + direction.second);

            // Only check if we have actually moved
            if (!(creature->getPosition().first == new_position.first && creature->getPosition().second == new_position.second))
            {
                // There is some kind of collision, check what type
                auto colliding = getCreaturesAt(new_position.first, new_position.second);

                // Avoid rock collision
                if (colliding.size() > 0)
                {
                    for (auto c : colliding)
                    {
                        if ((*c)->getSpecies() == "rock")
                            direction = std::make_pair(0, 0);
                    }
                }

                // Avoid more than 2 creatures on the same tile
                if (colliding.size() >= 2)
                    direction = std::make_pair(0, 0);
            }

            // Calculate final new_position
            new_position = std::make_pair(creature->getPosition().first + direction.first, creature->getPosition().second + direction.second);
            creature->setPosition(new_position);
        }

        // Check for collisions

        // Use a set to store a list of places where creatures are at
        std::set<std::pair<uint16_t, uint16_t>> coordinates;
        for(auto &creature : this->creatures)
            coordinates.insert(creature->getPosition());

        // Use a second list to store iterators to scheduled deletions
        std::vector<std::vector<std::unique_ptr<Creature>>::iterator> deletions;

        for(auto coordinate : coordinates)
        {
            auto colliding = getCreaturesAt(coordinate.first, coordinate.second);
            // Check whether we have multiple creatures standing on this position
            if (colliding.size() > 1)
            {
                // It better be exaclty 2 creatures or something is fucked up
                assert(colliding.size() == 2);

                // Each fight has exactly 2 fighters so we might as well create them statically here
                auto attacker = colliding[0];
                auto defender = colliding[1];

                // Fight goes on only if current attacker is not dead
                while ((*attacker)->getHitpoints() > 0)
                {
                    uint16_t attack_damage = (*attacker)->getStrength() + randInt(100);

                    // Determine whether the attack was dodged
                    int16_t dodge_chance = randInt(200) + (*defender)->getAgility() - 300;
                    bool attack_was_dodged = dodge_chance > 0 ? true : false;

                    if (!attack_was_dodged)
                        (*defender)->setHitpoints((*defender)->getHitpoints() - attack_damage);

                    // Remove dead creatures
                    if ((*defender)->getHitpoints() <= 0)
                        deletions.push_back(defender);

                    // Exchange attacker and defender
                    std::swap(attacker, defender);
                }
            }
        }

        // Delete all creatures that are scheduled for deletion
        for(auto &deletion : deletions)
            this->creatures.erase(deletion);

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
