#ifndef HISTORYSTATE_HPP
#define HISTORYSTATE_HPP

#include <map>
#include <memory>

#include "graphicalcreature.hpp"

class HistoryState
{
public:
    HistoryState(const std::string &hostname, uint16_t rank, uint32_t tick);
    void addCreature(const std::string &line);

private:
    std::string hostname;
    uint16_t rank;
    uint32_t tick;

    std::vector<std::unique_ptr<GraphicalCreature>> creatures;
};

#endif // HISTORYSTATE_HPP
