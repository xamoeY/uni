#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <string>

#include <cereal/cereal.hpp>

class Creature
{
public:
    Creature() = default;
    Creature(const Creature &creature);
    Creature(std::string species, uint32_t id, uint16_t positionX, uint16_t positionY);

    void doAction(uint32_t world_size_x, uint32_t world_size_y);

    static std::string convertSpecies(uint16_t species);
    static int16_t convertSpecies(std::string species);

    std::string getSpecies() const;

    uint32_t getId() const;
    void setId(const uint32_t &value);

    std::pair<uint16_t, uint16_t> getPosition() const;
    void setPosition(const std::pair<uint16_t, uint16_t> &value);

    uint16_t getStrength() const;
    void setStrength(const uint16_t &value);

    uint16_t getAgility() const;
    void setAgility(const uint16_t &value);

    uint16_t getIntelligence() const;
    void setIntelligence(const uint16_t &value);

    uint16_t getSociability() const;
    void setSociability(const uint16_t &value);

    template<class Archive>
    void serialize(Archive &archive)
    {
        archive(this->id, this->species, this->positionX, this->positionY,
                this->strength, this->agility, this->intelligence, this->sociability);
    }

protected:
    uint16_t species;
    uint32_t id;
    uint16_t positionX;
    uint16_t positionY;

    uint16_t strength;
    uint16_t agility;
    uint16_t intelligence;
    uint16_t sociability;
};

#endif // CREATURE_HPP
