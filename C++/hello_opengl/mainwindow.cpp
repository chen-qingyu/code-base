#include "mainwindow.h"

#include "hellogl.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    this->setCentralWidget(new HelloGL);
    this->resize(800, 600);
}
