#include "creature.hpp"

#include <iostream>

#include "utils.hpp"

Creature::Creature(std::string type, uint32_t id, uint16_t positionX, uint16_t positionY,
                   uint16_t worldSizeX, uint16_t worldSizeY) :
    id(id), positionX(positionX), positionY(positionY), worldSizeX(worldSizeX), worldSizeY(worldSizeY)
{
    this->type = stringToType(type);

    if (this->type == 0)
    {
        this->strength = 210;
        this->agility = 210;
        this->intelligence = 100;
        this->sociability = 80;
    }

    if (this->type == 1)
    {
        this->strength = 120;
        this->agility = 230;
        this->intelligence = 130;
        this->sociability = 120;
    }

    if (this->type == 2)
    {
        this->strength = 210;
        this->agility = 200;
        this->intelligence = 95;
        this->sociability = 95;
    }

    if (this->type == 3)
    {
        this->strength = 105;
        this->agility = 150;
        this->intelligence = 235;
        this->sociability = 110;
    }

    if (this->type == 4)
    {
        this->strength = 195;
        this->agility = 185;
        this->intelligence = 170;
        this->sociability = 50;
    }

    if (this->type == 5)
    {
        this->strength = 150;
        this->agility = 75;
        this->intelligence = 180;
        this->sociability = 195;
    }
}

void Creature::doAction()
{
    // random actions: wait, walk, fight

    this->positionX = randInt(0, this->worldSizeX);
    this->positionY = randInt(0, this->worldSizeY);
}

std::string Creature::typeToString(uint16_t type)
{
    if (type == 0)
        return "goblin";
    else if (type == 1)
        return "hobbit";
    else if (type == 2)
        return "orc";
    else if (type == 3)
        return "elf";
    else if (type == 4)
        return "dwarf";
    else if (type == 5)
        return "human";
    else
        return "invalid";
}

int16_t Creature::stringToType(std::string type)
{
    if (type == "golbin")
        return 0;
    else if (type == "hobbit")
        return 1;
    else if (type == "orc")
        return 2;
    else if (type == "elf")
        return 3;
    else if (type == "dwarf")
        return 4;
    else if (type == "human")
        return 5;
    else
        return -1;
}
