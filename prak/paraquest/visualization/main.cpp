#include <iostream>
#include <fstream>

#include <QApplication>

#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>

#include "mainwindow.hpp"
#include "history.hpp"
#include "utils.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.resize(800, 600);
    window.show();

    // Get world size from world properties file
    uint16_t size_x;
    uint16_t size_y;
    std::ifstream log("world.properties");
    cereal::BinaryInputArchive archive(log);
    if(log.is_open())
        archive(size_x, size_y);

    History history(size_x, size_y, 72, window.graphicsScene());
    history.parseHistory(".");

    return app.exec();
}
