#ifndef DISPLAYMELTMODEL_H
#define DISPLAYMELTMODEL_H

#include <QMainWindow>

namespace Ui
{
    class displaymeltmodel;
}

class DisplayMeltmodel : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit DisplayMeltmodel(QWidget *parent = 0);
    ~DisplayMeltmodel();
    
private:
    Ui::displaymeltmodel *ui;
};

#endif // DISPLAYMELTMODEL_H
