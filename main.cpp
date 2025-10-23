#include "MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo;
    Service serv(repo);

    for (auto c : serv.getchefs()) {
        MainWindow* w = new MainWindow(serv, c);
        w->show();
    }

   
    return a.exec();
}
