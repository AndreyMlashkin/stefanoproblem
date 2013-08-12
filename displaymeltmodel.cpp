#include <QDebug>
#include <QValidator>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QVariant>

#include "displaymeltmodel.h"
#include "ui_displaymeltmodel.h"
#include "meltmodel.h"

#include "meltdelegate.h"


DisplayMeltmodel::DisplayMeltmodel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::displaymeltmodel),
    m_meltmodel(NULL)
{
    ui->setupUi(this);

    readConfigFile();

    connect(ui->start, SIGNAL(clicked()), this, SLOT(initModel()));
    connect(this, SIGNAL(destroyed()),    this, SLOT(writeConfigFile()));
    connect(this, SIGNAL(destroyed()),    this, SLOT(writeConfigFile()));


    QValidator* intValidator = new QIntValidator(this);

    ui->x->setValidator(intValidator);
    ui->y->setValidator(intValidator);
    ui->startTemp->setValidator(intValidator);

    connect(ui->save, SIGNAL(triggered()), this, SLOT(callSaveDialog()));
    connect(ui->open, SIGNAL(triggered()), this, SLOT(callOpenDialog()));

    connect(ui->showGraphics, SIGNAL(stateChanged(int)), this, SLOT(updateViewsVisibility()));
    connect(ui->showTable,    SIGNAL(stateChanged(int)), this, SLOT(updateViewsVisibility()));
}

DisplayMeltmodel::~DisplayMeltmodel()
{
    delete ui;
}

void DisplayMeltmodel::initModel()
{
    startNewModel(ui->x->text().toInt(), ui->y->text().toInt(), ui->startTemp->text().toDouble());
}

void DisplayMeltmodel::step()
{
    m_meltmodel->processStep();
    ui->graphicsView->adjustSize();
}

void DisplayMeltmodel::callSaveDialog()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save File", "", "");
    if(fileName.isNull())
        return;

    if(!m_meltmodel)
        return;
    m_meltmodel->saveStep(fileName);
}

void DisplayMeltmodel::callOpenDialog()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", "", "");
    if(fileName.isNull())
        return;

    if(!m_meltmodel)
        m_meltmodel = new MeltModel();

    m_meltmodel->loadStep(fileName);

    setupModel();
}

void DisplayMeltmodel::updateViewsVisibility()
{
    if(ui->showGraphics->isChecked())
        ui->graphicsView->show();
    else
        ui->graphicsView->hide();

    if(ui->showTable->isChecked())
        ui->view->show();
    else
        ui->view->hide();

    writeConfigFile();
}

void DisplayMeltmodel::writeConfigFile()
{
    QSettings settings("modelSettings", QSettings::IniFormat);
    settings.beginGroup("GUI settings");
        settings.setValue("geometry", geometry());
        settings.setValue("showTable", ui->showTable->isChecked());
        settings.setValue("showGraphics", ui->showGraphics->isChecked());
    settings.endGroup();
}

void DisplayMeltmodel::readConfigFile()
{
    qDebug() << "readConfigFile";
    QSettings settings("modelSettings", QSettings::IniFormat);
    settings.beginGroup("GUI settings");
        setGeometry(settings.value("geometry").toRect());
        ui->showTable->setChecked(settings.value("showTable", true).toBool());
        ui->showGraphics->setChecked(settings.value("showGraphics", true).toBool());
    settings.endGroup();

    updateViewsVisibility();
}

void DisplayMeltmodel::startNewModel(int _width, int _height, double _startTemperature)
{
    delete m_meltmodel;
    m_meltmodel = new MeltModel(_width, _height, _startTemperature);

    setupModel();
}

void DisplayMeltmodel::setupModel()
{
    connect(ui->step, SIGNAL(clicked()), m_meltmodel, SLOT(processStep()));
    ui->view->setModel(m_meltmodel);
    ui->graphicsView->setModel(m_meltmodel);
    ui->graphicsView->setItemDelegate(new MeltDelegate);
}

void DisplayMeltmodel::resizeEvent(QResizeEvent*)
{
    writeConfigFile();
}

void DisplayMeltmodel::moveEvent(QMoveEvent *_event)
{
    writeConfigFile();
}
