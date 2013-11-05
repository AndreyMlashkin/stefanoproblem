#include <QApplication>
#include <QTextCodec>
#include "displaymeltmodel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    model::DisplayMeltmodel* w = new model::DisplayMeltmodel();
    w->show();
    
    return a.exec();
}
