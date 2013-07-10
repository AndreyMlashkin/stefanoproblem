#include "displaymeltmodel.h"
#include "ui_displaymeltmodel.h"

#include "meltmodel.h"

DisplayMeltmodel::DisplayMeltmodel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::displaymeltmodel)
{
    ui->setupUi(this);
    new MeltModel(5, 8);
}

DisplayMeltmodel::~DisplayMeltmodel()
{
    delete ui;
}
