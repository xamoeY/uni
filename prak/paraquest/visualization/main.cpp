#include <iostream>

#include <QApplication>
#include <QTimer>
#include <QObject>
#include <QtConcurrent/QtConcurrentRun>

#include "mainwindow.hpp"
#include "history.hpp"
#include "utils.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow window;
    window.resize(800, 600);
    window.show();

    History history(100, 100, 72, window.graphicsScene());

    return app.exec();
}
