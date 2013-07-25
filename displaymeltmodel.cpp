#include <QDebug>
#include "displaymeltmodel.h"
#include "ui_displaymeltmodel.h"
#include "meltmodel.h"

DisplayMeltmodel::DisplayMeltmodel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::displaymeltmodel),
    m_meltmodel(NULL)
{
    ui->setupUi(this);
    //connect(ui->start, SI)
    connect(ui->start, SIGNAL(clicked()), this, SLOT(initModel()));
}

DisplayMeltmodel::~DisplayMeltmodel()
{
    delete ui;
}

void DisplayMeltmodel::initModel()
{
    startNewModel(ui->x->text().toInt(), ui->y->text().toInt(), ui->temperature->text().toInt());
}

void DisplayMeltmodel::step()
{
    m_meltmodel->processStep();
}

void DisplayMeltmodel::startNewModel(int _width, int _height, int _startTemperature)
{
    delete m_meltmodel;
    m_meltmodel = new MeltModel(_width, _height, _startTemperature);

    connect(ui->step, SIGNAL(clicked()), m_meltmodel, SLOT(processStep()));
    ui->view->setModel(m_meltmodel);
}
