#include "history.hpp"

#include <iostream>
#include <fstream>

#include "utils.hpp"

History::History(quint16 sizeY, quint16 sizeX, quint16 scale, QGraphicsScene *scene) :
    sizeX(sizeX), sizeY(sizeY), scale(scale), scene(scene)
{
    // Make a grid
    for (int x = 0; x <= sizeX * scale; x += scale)
        scene->addLine(x, 0, x, sizeX * scale, QPen(Qt::black));
    for (int y = 0; y <= sizeY * scale; y += scale)
        scene->addLine(0, y, sizeY * scale, y, QPen(Qt::black));
}

void History::parseHistory(const std::string &directory)
{
    std::vector<std::string> log_files = getLogFiles(directory);
    for(auto file : log_files)
    {
        // First of all, we need to parse the file name itself

        // Extract hostname
        auto hostname_pos = file.find_first_of('-');
        std::string hostname = file.substr(0, hostname_pos);

        // Extract rank
        auto rank_pos = file.find_first_of('_') - 1;
        uint16_t rank  = std::stoi(file.substr(hostname_pos + 1, rank_pos));

        // Extract tick
        auto tick_pos = file.find_first_of('-', rank_pos) + 1;
        uint32_t tick = std::stoi(file.substr(tick_pos));

        this->history_states.emplace_back(std::unique_ptr<HistoryState> (new HistoryState(hostname, rank, tick)));

        // Now parse the contents of the archive
        std::ifstream infile(file);
        std::string line;
        while(std::getline(infile, line))
        {
            history_states.back()->addCreature(line);
        }
    }
}

void History::addCreature(QString type)
{
//    creatures.push_back(std::unique_ptr<GraphicalCreature> (new GraphicalCreature(type, this->scale,
//                                                                this->sizeX, this->sizeY)));
//    scene->addItem(creatures.back().get());
}
