#ifndef WORLD_HPP
#define WORLD_HPP

#include <memory>
#include <vector>

#include <QGraphicsScene>
#include <QObject>

#include "graphicalcreature.hpp"
#include "historystate.hpp"

class History : public QObject
{
    Q_OBJECT
public:
    History(quint16 size_x, quint16 size_y, quint32 max_tick, quint16 scale, QGraphicsScene *scene);
    void parseHistory(const std::string& directory);

private:
    std::map<uint32_t, std::unique_ptr<HistoryState>> history_states;
    std::map<std::string, QPixmap> images;
    quint16 sizeX;
    quint16 sizeY;
    quint32 maxTick;
    quint16 scale;
    QGraphicsScene *scene;
};

#endif // WORLD_HPP
