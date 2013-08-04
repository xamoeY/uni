#include <iostream>

#include <QApplication>
#include <QTimer>
#include <QObject>
#include <QtConcurrent/QtConcurrentRun>

#include "mainwindow.hpp"
#include "world.hpp"
#include "utils.hpp"

int main(int argc, char **argv)
{
    initRandom(0);

    QApplication app(argc, argv);

    MainWindow window;
    window.resize(800, 600);
    window.show();

    World world(100, 100, 72, window.graphicsScene());

    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &world, SLOT(updateCreatures()));
    timer.start(100);

    world.populate(100);

    // simulate() is blocking, so run it in a thread
    QFuture<void> f = QtConcurrent::run(&world, &World::simulate, 10000000);

    return app.exec();
}
