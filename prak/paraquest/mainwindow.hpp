#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QGraphicsScene>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    QGraphicsScene *graphicsScene();
    
private:
    void setupMatrix();
    
    QGraphicsScene *scene;
};

#endif // MAINWINDOW_H
