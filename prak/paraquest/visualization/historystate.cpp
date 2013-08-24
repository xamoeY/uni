#include "historystate.hpp"

HistoryState::HistoryState(const std::string &hostname, uint16_t rank, uint32_t tick) :
    hostname(hostname), rank(rank), tick(tick)
{
}

void HistoryState::addCreature(const std::string &line)
{
    this->creatures.emplace_back(std::unique_ptr<GraphicalCreature> (new GraphicalCreature(line, 72)));
}
