#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile qss("://resources/StyleSheet.qss");
    qss.open(QFile::ReadOnly);
    a.setStyleSheet(qss.readAll());
    a.topLevelWindows();

    MainWindow w;
    w.setWindowTitle("4 In A Row");
    w.show();

    return a.exec();
}
