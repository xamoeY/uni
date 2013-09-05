#include "creature.hpp"

#include <iostream>
#include <sstream>
#include <regex>
#include <utility>

#include "utils.hpp"

Creature::Creature(const Creature& creature)
{
    this->species = convertSpecies(creature.getSpecies());
    this->id = creature.getId();
    this->positionX = creature.getPosition().first;
    this->positionY = creature.getPosition().second;

    this->strength = creature.getStrength();
    this->agility = creature.getAgility();
    this->intelligence = creature.getIntelligence();
    this->sociability = creature.getSociability();
}

Creature::Creature(std::string species, uint32_t id, uint16_t positionX, uint16_t positionY) :
    species(convertSpecies(species)), id(id), positionX(positionX), positionY(positionY)
{
    if (this->species == 0)
    {
        this->strength = 210;
        this->agility = 210;
        this->intelligence = 100;
        this->sociability = 80;
    }

    if (this->species == 1)
    {
        this->strength = 120;
        this->agility = 230;
        this->intelligence = 130;
        this->sociability = 120;
    }

    if (this->species == 2)
    {
        this->strength = 210;
        this->agility = 200;
        this->intelligence = 95;
        this->sociability = 95;
    }

    if (this->species == 3)
    {
        this->strength = 105;
        this->agility = 150;
        this->intelligence = 235;
        this->sociability = 110;
    }

    if (this->species == 4)
    {
        this->strength = 195;
        this->agility = 185;
        this->intelligence = 170;
        this->sociability = 50;
    }

    if (this->species == 5)
    {
        this->strength = 150;
        this->agility = 75;
        this->intelligence = 180;
        this->sociability = 195;
    }

    if (this->species == 6)
    {
        this->strength = 255;
        this->agility = 255;
        this->intelligence = 255;
        this->sociability = 255;
    }
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

uint32_t Creature::getHash(uint32_t world_size_x, uint32_t creature_pos_x, uint32_t creature_pos_y)
{
    return world_size_x * creature_pos_y + creature_pos_x;
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
uint16_t Creature::getIntelligence() const
{
    return intelligence;
}

void Creature::setIntelligence(const uint16_t &value)
{
    intelligence = value;
}
uint16_t Creature::getSociability() const
{
    return sociability;
}

void Creature::setSociability(const uint16_t &value)
{
    sociability = value;
}
