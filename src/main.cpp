#include "mainwindow.h"
#include "gradientdescent.h"
#include <QApplication>






int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Gradient Descent optimization");
    w.show();

    return a.exec();
}
