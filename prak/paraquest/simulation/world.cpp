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
#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>

#include "mpi.h"

#include "utils.hpp"

World::World(uint16_t size_x, uint16_t size_y, uint16_t comm_size, uint16_t comm_rank, char* processor_name) :
    sizeX(size_x), sizeY(size_y), commSize(comm_size), commRank(comm_rank), processorName(processor_name), currentId(0)
{
    // Figure out which creatures to queue for sending
    this->chunkSize = this->sizeX / this->commSize;
    this->offset = this->chunkSize * this->commRank;
}

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
    // If this is the root process, put creatures into own memory and scatter them out to other processes
    if(this->commRank == 0)
    {
        // Seed the world with obstacles
        for(size_t i = 0; i < obstacle_count; ++i)
        {
            // Yes, rocks are creatures, think pet rocks :)
            addCreature("rock");
        }

        // Seed the world with creatures
        for(size_t i = 0; i < creature_count; ++i)
        {
            std::vector<std::string> races {"goblin", "hobbit", "orc", "elf", "dwarf", "human"};
            addCreature(races[randInt(races.size() - 1)]);
        }

        // Send creatures to other processes
        if(this->commSize > 1)
        {
            // Start with process = 1 because we're 0 and we don't have to send to ourselves
            for(size_t process = 1; process < this->commSize; ++process)
            {
                // Calculate what to send
                // Keep in mind that the leftmost and the rightmost
                // processes only receive one extra column from their neighbor instead of 2
                uint16_t current_offset = this->chunkSize * process;
                std::vector<std::vector<std::unique_ptr<Creature>>::iterator> scheduled_creatures;
                for(auto it = this->creatures.begin(); it != this->creatures.end(); ++it)
                {
                    // -1 and +1 because we want to send one additional column left and right of the actual memory chunk
                    if((*it)->getPosition().first >= current_offset - 1 && (*it)->getPosition().first < current_offset + 1 + this->chunkSize)
                    {
                        scheduled_creatures.push_back(it);
                    }
                }

                // Tell the process how many creatures it's going to receive
                uint16_t count = scheduled_creatures.size();
                MPI_Send(&count, 1, MPI_UNSIGNED_SHORT, process, 0, MPI_COMM_WORLD);

                for(auto &creature : scheduled_creatures)
                {
                    (*creature)->mpiSend(process);
                }
            }

            // Clean up extra creatures out of root process memory
            std::vector<std::vector<std::unique_ptr<Creature>>::iterator> deletions;
            uint16_t chunk_size = this->sizeX / this->commSize;
            for(auto it = this->creatures.begin(); it != this->creatures.end(); ++it)
            {
                if ((*it)->getPosition().first > chunk_size + 1)
                    deletions.push_back(it);
            }
            for(auto &deletion : deletions)
                this->creatures.erase(deletion);
        }
    }
    else
    {
        // Receive number of creatures we're going to receive from root process
        uint16_t count;
        MPI_Recv(&count, 1, MPI_UNSIGNED_SHORT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        for(size_t i = 0; i < count; ++i)
        {
            this->creatures.push_back(std::unique_ptr<Creature>(Creature::mpiRecv(0)));
        }
    }
}

void World::simulate(uint32_t ticks)
{
    if(this->commRank == 0)
    {
        // Dump global world settings once
        dumpSettings(ticks);
    }

    // Dump state once at very beginning
    dumpState(0, ticks);

    // Tick loop
    for(size_t i = 1; i < ticks + 1; ++i)
    {
        // debug
        std::cout << "tick: " << i << " | creatures: " << this->creatures.size() << std::endl;

        // Make every creature do something
        move();

        // Send/receive creatures to/from neighboring processes
        sync();

        // Check for collisions
        collide();

        dumpState(i, ticks);
    }
}

void World::move()
{
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
                direction = std::make_pair(1, 0);
        }

        // move south
        else if (action == 2)
        {
            if (creature->getPosition().second + 1 < int32_t(this->sizeY))
                direction = std::make_pair(0, 1);
        }

        // move west
        else if (action == 3)
        {
            if (creature->getPosition().first - 1 >= 0)
                direction = std::make_pair(-1, 0);
        }

        // move north
        else if (action == 4)
        {
            if (creature->getPosition().second - 1 >= 0)
                direction = std::make_pair(0, -1);
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

}

void World::sync()
{
    // Our state works in a tick tock principle:
    // 0: tick down
    // 1: tock down
    // 2: tick up
    // 3: tock up
    // 4: finished transmission
    // tick means first set of processes send while the other wait while tock swaps the roles
    // of sender/receiver
    // down/up provide the direction of the transfer
    int state = 0;
    while(state < 4)
    {
        int partner = -1; // partner == -1 means invalid partner
        bool send = false;
        bool recv = false;

        // first process
        if(this->commRank == 0)
        {
            if(state == 0)
            {
                partner = 1;
                send = true;
            }
            else if(state == 1)
            {
                // We don't do anything here
            }
            else if(state == 2)
            {
                partner = 1;
                recv = true;
            }
            else if(state == 3)
            {
                // We don't do anything here
            }
        }

        // last process
        else if(this->commRank == this->commSize - 1)
        {
            if(state == 0)
            {
                if(this->commSize % 2 == 0)
                {
                    partner = this->commRank - 1;
                    recv = true;
                }
            }
            else if(state == 1)
            {
                if(this->commSize % 2 != 0)
                {
                    partner = this->commRank - 1;
                    recv = true;
                }
            }
            else if(state == 2)
            {
                if(this->commSize % 2 == 0)
                {
                    partner = this->commRank - 1;
                    send = true;
                }
            }
            else if(state == 3)
            {
                if(this->commSize % 2 != 0)
                {
                    partner = this->commRank - 1;
                    send = true;
                }
            }
        }

        // even processes
        else if(this->commRank % 2 == 0)
        {
            if(state == 0)
            {
                partner = this->commRank + 1;
                send = true;
            }
            else if(state == 1)
            {
                partner = this->commRank - 1;
                recv = true;
            }
            else if(state == 2)
            {
                partner = this->commRank + 1;
                recv = true;
            }
            else if(state == 3)
            {
                partner = this->commRank - 1;
                send = true;
            }
        }

        // odd processes
        else if(this->commRank % 2 != 0)
        {
            if(state == 0)
            {
                partner = this->commRank - 1;
                recv = true;
            }
            else if(state == 1)
            {
                partner = this->commRank + 1;
                send = true;
            }
            else if(state == 2)
            {
                partner = this->commRank - 1;
                send = true;
            }
            else if(state == 3)
            {
                partner = this->commRank + 1;
                recv = true;
            }
        }

        std::vector<std::vector<std::unique_ptr<Creature>>::iterator> scheduled_creatures;
        for(auto it = this->creatures.begin(); it != this->creatures.end(); ++it)
        {
            // If this is true, we want to get the creatures left of us
            if(partner < this->commRank)
            {
                // Creatures left of us
                if((*it)->getPosition().first == this->offset - 1)
                    scheduled_creatures.push_back(it);
            }
            // If this is true, we want to get the creatures right of us
            else if(partner > this->commRank)
            {
                // Creatures right of us
                if((*it)->getPosition().first == this->offset + 1 + this->chunkSize)
                    scheduled_creatures.push_back(it);
            }
        }

        // Do the actual sending/receiving
        if(send)
        {
            assert(partner != -1);

            // Tell the other process how many creatures it's going to receive
            uint16_t count = scheduled_creatures.size();
            MPI_Send(&count, 1, MPI_UNSIGNED_SHORT, partner, 0, MPI_COMM_WORLD);

            for(auto &creature : scheduled_creatures)
                (*creature)->mpiSend(partner);
        }

        if(recv)
        {
            assert(partner != -1);

            // Receive number of creatures we're going to receive from root process
            uint16_t count;
            MPI_Recv(&count, 1, MPI_UNSIGNED_SHORT, partner, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            for(size_t i = 0; i < count; ++i)
                this->creatures.push_back(std::unique_ptr<Creature>(Creature::mpiRecv(partner)));
        }

        ++state;
    }

    // Clean up creatures that went outside our memory
    std::vector<std::vector<std::unique_ptr<Creature>>::iterator> deletions;
    uint16_t chunk_size = this->sizeX / this->commSize;
    for(auto it = this->creatures.begin(); it != this->creatures.end(); ++it)
    {
        if((*it)->getPosition().first < offset - 1 || (*it)->getPosition().first > offset + chunk_size + 1)
            deletions.push_back(it);
    }
    for(auto &deletion : deletions)
        this->creatures.erase(deletion);
}

void World::collide()
{
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
