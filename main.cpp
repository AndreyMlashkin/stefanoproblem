#include "displaymeltmodel.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    DisplayMeltmodel* w = new DisplayMeltmodel();
    w->show();
    
    return a.exec();
}
