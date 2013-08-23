#include "creature.hpp"

#include <iostream>
#include <sstream>
#include <regex>

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
    const uint16_t action = randInt(0, 4);

    if (action == 0) {
        // wait
        return;
    } else if (action == 1) {
        // move east
        if (this->positionX + 1 < this->worldSizeX)
            this->positionX += 1;
    } else if (action == 2) {
        // move south
        if (this->positionY + 1 < this->worldSizeY)
            this->positionY += 1;
    } else if (action == 3) {
        // move west
        if (this->positionX - 1 >= 0)
            this->positionX -= 1;
    } else if (action == 4) {
        // move north
        if (this->positionY - 1 >= 0)
            this->positionY -= 1;
    }
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

std::string Creature::serialize() const
{
    std::stringstream string;
    string << "id:" << this->id
           << " type:" << this->type
           << " posx:" << this->positionX
           << " posy:" << this->positionY
           << " str:" << this->strength
           << " agi:" << this->agility
           << " int:" << this->intelligence
           << " soc:" << this->sociability;
    return string.str();
}

void Creature::deserialize(const std::string &line)
{
    std::vector<std::string> tokens;
    uint16_t current = 0;
    bool done = false;
    while(!done)
    {
        auto pos = line.find_first_of(' ');
        if(pos != line.npos)
        {
            std::string token = line.substr(current, pos);
            tokens.push_back(token);
            current = pos + 1;
        }
        else
        {
            done = true;
        }
    }

    for(auto token : tokens)
    {
        auto token_pos = token.find_first_of(':');
        std::string key = token.substr(0, token_pos);
        auto value = std::stoi(token.substr(token_pos + 1));
        if(key == "id")
            this->id = value;
        if(key == "type")
            this->type = value;
        if(key == "posx")
            this->positionX = value;
        if(key == "posy")
            this->positionY = value;
        if(key == "str")
            this->strength = value;
        if(key == "agi")
            this->agility = value;
        if(key == "int")
            this->intelligence = value;
        if(key == "soc")
            this->sociability = value;
    }

}
