#include "mainwindow.hpp"

#include <QHBoxLayout>

#include "creature.hpp"
#include "view.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    scene = new QGraphicsScene;

    View* view = new View("Simulation view");
    view->view()->setScene(scene);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);
    setLayout(layout);

    setWindowTitle(tr("ParaQuest"));
}

QGraphicsScene *MainWindow::graphicsScene()
{
    return scene;
}
