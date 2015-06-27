#include <QApplication>

#include "displaymeltmodel.h"
#include "languagechooser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    model::LanguageChooser* chooser = new model::LanguageChooser();
    chooser->setModal(true);
    chooser->exec();

    model::DisplayMeltmodel* w = new model::DisplayMeltmodel();
    w->show();
    
    return a.exec();
}
