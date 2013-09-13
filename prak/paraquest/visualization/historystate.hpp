#ifndef HISTORYSTATE_HPP
#define HISTORYSTATE_HPP

#include <map>
#include <memory>

#include "graphicalcreature.hpp"

class HistoryState
{
public:
    HistoryState(const std::string &hostname, uint16_t rank, uint32_t tick);
    void addCreature(const std::unique_ptr<Creature> &creature, qint16 scale);

    // We need this raw pointer for the QGraphicsScene, sadly :(
    GraphicalCreature* getLastCreature() const;

private:
    std::string hostname;
    uint16_t rank;
    uint32_t tick;

    std::vector<std::unique_ptr<GraphicalCreature>> creatures;
};

#endif // HISTORYSTATE_HPP
