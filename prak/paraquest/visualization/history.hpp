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
    History(quint16 sizeY, quint16 sizeX, quint16 scale, QGraphicsScene *scene);
    void parseHistory(const std::string& directory);
    void addCreature(QString type);

private:
    std::vector<std::unique_ptr<HistoryState>> creatures;
    quint16 sizeX;
    quint16 sizeY;
    quint16 scale;
    QGraphicsScene *scene;
};

#endif // WORLD_HPP
