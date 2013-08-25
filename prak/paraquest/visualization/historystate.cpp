#include "historystate.hpp"

HistoryState::HistoryState(const std::string &hostname, uint16_t rank, uint32_t tick) :
    hostname(hostname), rank(rank), tick(tick)
{
}

void HistoryState::addCreature(const std::shared_ptr<Creature>& creature, qint16 scale)
{
    this->creatures.emplace_back(std::unique_ptr<GraphicalCreature> (new GraphicalCreature(creature, scale)));
}

GraphicalCreature *HistoryState::getLastCreature() const
{
    return this->creatures.back().get();
}
