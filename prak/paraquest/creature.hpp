#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <cstdint>
#include <string>

class Creature
{
public:
    Creature(std::string type);
    void doAction();

private:
    std::string m_type;
    uint16_t m_strength;
    uint16_t m_agility;
    uint16_t m_intelligence;
    uint16_t m_sociability;
};

#endif // CREATURE_HPP
