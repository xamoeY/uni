#include "history.hpp"

#include <iostream>
#include <fstream>

#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/string.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>

#include "utils.hpp"
#include "view.hpp"

History::History(quint16 size_x, quint16 size_y, quint32 max_tick, quint16 scale, QGraphicsScene *scene) :
    sizeX(size_x), sizeY(size_y), maxTick(max_tick), scale(scale), scene(scene)
{
    // Preload pixmaps
    std::vector<std::string> species {"goblin", "hobbit", "orc", "elf", "dwarf", "human", "rock"};
    for(auto &s : species)
    {
        images[s] = QPixmap(QString::fromStdString(":/images/" + s + ".png"));
    }

    // Make a grid
    for (int x = 0; x <= sizeX * scale; x += scale)
        scene->addLine(x, 0, x, sizeX * scale, QPen(Qt::black));
    for (int y = 0; y <= sizeY * scale; y += scale)
        scene->addLine(0, y, sizeY * scale, y, QPen(Qt::black));

    // Set slider to proper max value
    GraphicsView *view = static_cast<GraphicsView*>(this->scene->views().first());
    view->getView()->setMaximumTick(maxTick);
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

        this->history_states.emplace(tick, std::unique_ptr<HistoryState> (new HistoryState(hostname, rank, tick)));

        // Now parse the contents of the archive
        std::ifstream log(file);
        cereal::BinaryInputArchive archive(log);
        std::multimap<uint32_t, std::shared_ptr<Creature>> temp_creatures;
        archive(temp_creatures);

        for(auto c : temp_creatures)
        {
            history_states[tick]->addCreature(c.second, this->scale);
            GraphicalCreature* graphical_creature = history_states[tick]->getLastCreature();
            const std::string species = graphical_creature->getSpecies();
            graphical_creature->setPixmap(&images[species]);
            graphical_creature->setData(0, QVariant(tick)); // Store the tick of this creature in 0 so compare with later during rendering
            GraphicsView *gview = static_cast<GraphicsView*>(this->scene->views().first());
            View *view = gview->getView();
            graphical_creature->setData(1, QVariant::fromValue(view)); // Store pointer to View in 1 so we can get the slider value later
            this->scene->addItem(graphical_creature);
        }
    }
}
