#include "mainwindow.h"
#include <QApplication>
#include <QVector>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    std::reverse(temp.begin(), temp.end());
//    for (int i(0); i < temp.size(); i++) {
//        std::reverse(temp[i].begin(), temp[i].end());
//    }
//    qDebug() << temp;

    return a.exec();
}
