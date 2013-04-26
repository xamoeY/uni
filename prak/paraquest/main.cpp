#include <iostream>

#include <QApplication>

#include "mainwindow.hpp"
#include "world.hpp"
#include "utils.hpp"

int main(int argc, char **argv)
{
    initRandom(20);

    QApplication app(argc, argv);

    MainWindow window;
    window.resize(800, 600);
    window.show();

    World world(100, 100, 72, window.graphicsScene());
    world.populate(100);
    world.simulate(100);

    return app.exec();
}
