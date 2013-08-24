#ifndef HISTORYSTATE_HPP
#define HISTORYSTATE_HPP

#include <map>
#include <memory>

#include "graphicalcreature.hpp"

class HistoryState
{
public:
    HistoryState();

private:
    std::multimap<uint32_t, std::unique_ptr<GraphicalCreature>> creatures;
};

#endif // HISTORYSTATE_HPP
