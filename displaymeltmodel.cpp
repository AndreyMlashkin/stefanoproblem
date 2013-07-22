#include "displaymeltmodel.h"
#include "ui_displaymeltmodel.h"

#include "meltmodel.h"

DisplayMeltmodel::DisplayMeltmodel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::displaymeltmodel),
    m_meltmodel(NULL)
{
    ui->setupUi(this);
    startNewModel(10, 15, -100);
}

DisplayMeltmodel::~DisplayMeltmodel()
{
    delete ui;
}

void DisplayMeltmodel::startNewModel(int _width, int _height, int _startTemperature)
{
    delete m_meltmodel;
    m_meltmodel = new MeltModel(_width, _height, _startTemperature);
    QAbstractItemModel* tmp = m_meltmodel;
    ui->tableView->setModel(tmp);
}
