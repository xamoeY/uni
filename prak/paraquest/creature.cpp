#include "creature.hpp"

Creature::Creature(std::string type) :
    m_type(type)
{
    // TODO random spawning
    if (type == "goblin")
    {
        m_strength = 210;
        m_agility = 210;
        m_intelligence = 100;
        m_sociability = 80;
    }

    if (type == "hobbit")
    {
        m_strength = 120;
        m_agility = 230;
        m_intelligence = 130;
        m_sociability = 120;
    }

    if (type == "ork")
    {
        m_strength = 210;
        m_agility = 200;
        m_intelligence = 95;
        m_sociability = 95;
    }

    if (type == "elf")
    {
        m_strength = 105;
        m_agility = 150;
        m_intelligence = 235;
        m_sociability = 110;
    }

    if (type == "dwarf")
    {
        m_strength = 195;
        m_agility = 185;
        m_intelligence = 170;
        m_sociability = 50;
    }

    if (type == "human")
    {
        m_strength = 150;
        m_agility = 75;
        m_intelligence = 180;
        m_sociability = 195;
    }
}

//TODO action rules
void Creature::doAction()
{
}
