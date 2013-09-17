#include "displaymeltmodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DisplayMeltmodel* w = new DisplayMeltmodel();
    w->show();
    
    return a.exec();
}
