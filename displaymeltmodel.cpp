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

int inline max(int a, int b)
{
    return (a > b)? a : b;
}

int inline min(int a, int b)
{
    return (a < b)? a : b;
}

DisplayMeltmodel::DisplayMeltmodel(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::displaymeltmodel),
    m_meltmodel(NULL),
    m_delegate(new MeltDelegate)
{
    ui->setupUi(this);

    readConfigFile();

    connect(ui->start, SIGNAL(clicked()), this, SLOT(initModel()));

    QValidator* intValidator = new QDoubleValidator(this);

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
    writeConfigFile();
    delete ui;
    delete m_delegate;
    delete m_meltmodel;
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
}

void DisplayMeltmodel::writeConfigFile()
{
    QSettings settings("modelSettings", QSettings::IniFormat);
    settings.beginGroup("GUI settings");
        settings.setValue("geometry", geometry());
        settings.setValue("showTable", ui->showTable->isChecked());
        settings.setValue("showGraphics", ui->showGraphics->isChecked());
    settings.endGroup();

    settings.beginGroup("input");
        settings.setValue("height", ui->y->text());
        settings.setValue("width",  ui->x->text());
        settings.setValue("startTemperature", ui->startTemp->text());
    settings.endGroup();
}

void DisplayMeltmodel::readConfigFile()
{
    QSettings settings("modelSettings", QSettings::IniFormat);
    settings.beginGroup("GUI settings");
        setGeometry(settings.value("geometry").toRect());
        ui->showTable->setChecked(settings.value("showTable", true).toBool());
        ui->showGraphics->setChecked(settings.value("showGraphics", true).toBool());
    settings.endGroup();

    settings.beginGroup("input");
        ui->y->setText(settings.value("height", 5).toString());
        ui->x->setText(settings.value("width", 5).toString());
        ui->startTemp->setText(settings.value("startTemperature", 0).toString());
    settings.endGroup();

    updateViewsVisibility();
}

void DisplayMeltmodel::updateMinTemp(double _newTemp)
{
    ui->minTemp->setText(QString::number(_newTemp));
    m_delegate->updateMinTemp(_newTemp);
}

void DisplayMeltmodel::updateMaxTemp(double _newTemp)
{
    ui->maxTemp->setText(QString::number(_newTemp));
    m_delegate->updateMaxTemp(_newTemp);
}

void DisplayMeltmodel::startNewModel(int _width, int _height, double _startTemperature)
{
    delete m_meltmodel;
    m_meltmodel = new MeltModel(_width, _height, _startTemperature);

    setupModel();

    resizeEvent(NULL);
}

void DisplayMeltmodel::setupModel()
{
    connect(ui->step, SIGNAL(clicked()), m_meltmodel, SLOT(processStep()));
    ui->view->setModel(m_meltmodel);
    ui->graphicsView->setModel(m_meltmodel);

//    MeltDelegate* delegate = new MeltDelegate;
    connect(m_meltmodel, SIGNAL(updateMaxTemp(double)), SLOT(updateMaxTemp(double)));
    connect(m_meltmodel, SIGNAL(updateMinTemp(double)), SLOT(updateMinTemp(double)));

    ui->graphicsView->setItemDelegate(m_delegate);
}

void DisplayMeltmodel::resizeEvent(QResizeEvent*)
{
    if(!m_meltmodel)
        return;

    ui->graphicsView->resizeRowsToContents();
    ui->graphicsView->resizeColumnsToContents();


    int width  = ui->graphicsView->width();
    int height = ui->graphicsView->height();

    int cellWidth  = height / m_meltmodel->rowCount();
    int cellHeight = width  / m_meltmodel->columnCount();

    int cellSize = min(cellWidth, cellHeight);


    QHeaderView* header = ui->graphicsView->horizontalHeader();
    header->setDefaultSectionSize(cellSize);

    header =  ui->graphicsView->verticalHeader();
    header->setDefaultSectionSize(cellSize);

//    header.adjustSize();
}
