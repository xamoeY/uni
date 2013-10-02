#include "creature.hpp"

#include <iostream>
#include <sstream>
#include <regex>
#include <utility>

#include "mpi.h"

#include "utils.hpp"

Creature::Creature(const Creature& creature)
{
    this->species = convertSpecies(creature.getSpecies());
    this->id = creature.getId();
    this->positionX = creature.getPosition().first;
    this->positionY = creature.getPosition().second;

    this->strength = creature.getStrength();
    this->agility = creature.getAgility();
    this->hitpoints = creature.getHitpoints();
}

Creature::Creature(std::string species, uint32_t id, uint16_t positionX, uint16_t positionY) :
    species(convertSpecies(species)), id(id), positionX(positionX), positionY(positionY)
{
    if (this->species == 0)
    {
        this->strength = 210;
        this->agility = 210;
        mixTraits();
    }

    if (this->species == 1)
    {
        this->strength = 120;
        this->agility = 230;
        mixTraits();
    }

    if (this->species == 2)
    {
        this->strength = 210;
        this->agility = 200;
        mixTraits();
    }

    if (this->species == 3)
    {
        this->strength = 105;
        this->agility = 150;
        mixTraits();
    }

    if (this->species == 4)
    {
        this->strength = 195;
        this->agility = 185;
        mixTraits();
    }

    if (this->species == 5)
    {
        this->strength = 150;
        this->agility = 75;
        mixTraits();
    }

    if (this->species == 6)
    {
        this->strength = 255;
        this->agility = 255;
    }

    this->hitpoints = this->strength * 100;
}

std::string Creature::convertSpecies(uint16_t species)
{
    if (species == 0)
        return "goblin";
    else if (species == 1)
        return "hobbit";
    else if (species == 2)
        return "orc";
    else if (species == 3)
        return "elf";
    else if (species == 4)
        return "dwarf";
    else if (species == 5)
        return "human";
    else if (species == 6)
        return "rock";
    else
        return "invalid";
}

int16_t Creature::convertSpecies(std::string species)
{
    if (species == "goblin")
        return 0;
    else if (species == "hobbit")
        return 1;
    else if (species == "orc")
        return 2;
    else if (species == "elf")
        return 3;
    else if (species == "dwarf")
        return 4;
    else if (species == "human")
        return 5;
    else if (species == "rock")
        return 6;
    else
        return -1;
}

uint32_t Creature::getId() const
{
    return id;
}

void Creature::setId(const uint32_t &value)
{
    id = value;
}

std::pair<uint16_t, uint16_t> Creature::getPosition() const
{
    return std::make_pair(this->positionX, this->positionY);
}

void Creature::setPosition(const std::pair<uint16_t, uint16_t> &value)
{
    this->positionX = value.first;
    this->positionY = value.second;
}

std::string Creature::getSpecies() const
{
    return convertSpecies(this->species);
}

void Creature::mixTraits()
{
    this->strength += randInt(-25, 25);
    this->agility += randInt(-25, 25);
}

uint16_t Creature::getStrength() const
{
    return strength;
}

void Creature::setStrength(const uint16_t &value)
{
    strength = value;
}
uint16_t Creature::getAgility() const
{
    return agility;
}

void Creature::setAgility(const uint16_t &value)
{
    agility = value;
}

int16_t Creature::getHitpoints() const
{
    return hitpoints;
}

void Creature::setHitpoints(const int16_t &value)
{
    hitpoints = value;
}

std::string Creature::debug() const
{
    std::stringstream ss;
    ss << "id: " << this->id << " | species: " << this->getSpecies() << " | pos: " << this->positionX << "/" << this->positionY;
    return ss.str();
}

Creature *Creature::mpiRecv(uint16_t from)
{
    Creature *creature = new Creature();
    MPI_Recv(&creature->species, 1, MPI_UNSIGNED_SHORT, from, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&creature->id, 1, MPI_UNSIGNED, from, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&creature->positionX, 1, MPI_UNSIGNED_SHORT, from, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&creature->positionY, 1, MPI_UNSIGNED_SHORT, from, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&creature->strength, 1, MPI_UNSIGNED_SHORT, from, 5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&creature->agility, 1, MPI_UNSIGNED_SHORT, from, 6, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&creature->hitpoints, 1, MPI_SHORT, from, 7, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    return creature;
}

void Creature::mpiSend(uint16_t to)
{
    MPI_Send(&this->species, 1, MPI_UNSIGNED_SHORT, to, 1, MPI_COMM_WORLD);
    MPI_Send(&this->id, 1, MPI_UNSIGNED, to, 2, MPI_COMM_WORLD);
    MPI_Send(&this->positionX, 1, MPI_UNSIGNED_SHORT, to, 3, MPI_COMM_WORLD);
    MPI_Send(&this->positionY, 1, MPI_UNSIGNED_SHORT, to, 4, MPI_COMM_WORLD);
    MPI_Send(&this->strength, 1, MPI_UNSIGNED_SHORT, to, 5, MPI_COMM_WORLD);
    MPI_Send(&this->agility, 1, MPI_UNSIGNED_SHORT, to, 6, MPI_COMM_WORLD);
    MPI_Send(&this->hitpoints, 1, MPI_SHORT, to, 7, MPI_COMM_WORLD);
}
