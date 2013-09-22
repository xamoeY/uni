#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <map>
#include <string>

#include <cereal/cereal.hpp>

class Creature
{
public:
    Creature() = default;
    Creature(const Creature &creature);
    Creature(std::string species, uint32_t id, uint16_t positionX, uint16_t positionY);
    ~Creature() = default;

    static std::string convertSpecies(uint16_t species);
    static int16_t convertSpecies(std::string species);

    std::string getSpecies() const;

    void mixTraits();

    uint32_t getId() const;
    void setId(const uint32_t &value);

    std::pair<uint16_t, uint16_t> getPosition() const;
    void setPosition(const std::pair<uint16_t, uint16_t> &value);

    uint16_t getStrength() const;
    void setStrength(const uint16_t &value);

    uint16_t getAgility() const;
    void setAgility(const uint16_t &value);

    int16_t getHitpoints() const;
    void setHitpoints(const int16_t &value);

    std::string debug() const;

    template<class Archive>
    void serialize(Archive &archive)
    {
        archive(this->id, this->species, this->positionX, this->positionY,
                this->strength, this->agility, this->hitpoints);
    }

protected:
    uint16_t species;
    uint32_t id;
    uint16_t positionX;
    uint16_t positionY;

    uint16_t strength;
    uint16_t agility;
    int16_t hitpoints;
};

#endif // CREATURE_HPP
