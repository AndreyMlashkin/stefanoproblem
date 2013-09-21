#include <QDebug>
#include <QValidator>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QVariant>
#include <QTableView>

#include "displaymeltmodel.h"
#include "ui_displaymeltmodel.h"
#include "meltmodel.h"
#include "meltdelegate.h"

#include "modelconstants.h"
#include "graphicswidget.h"

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
    m_autoRepeat(false),
    m_closed(false),
    ui(new Ui::displaymeltmodel),
    m_meltmodel(NULL),
    m_delegate(new MeltDelegate),
    m_table(new QTableView),
    m_graphics(new GraphicsWidget())
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);


    readConfigFile();
    initConstants();

    connect(ui->start,  SIGNAL(clicked()), this, SLOT(initModel()));
    connect(ui->repeat, SIGNAL(clicked()), this, SLOT(autoRepeatOn()));
    connect(ui->pause,  SIGNAL(clicked()), this, SLOT(autoRepeatOff()));

    QValidator* intValidator = new QDoubleValidator(this);

    ui->x->setValidator(intValidator);
    ui->y->setValidator(intValidator);
    ui->startTemp->setValidator(intValidator);

    connect(ui->save, SIGNAL(triggered()), this, SLOT(callSaveDialog()));
    connect(ui->open, SIGNAL(triggered()), this, SLOT(callOpenDialog()));

    connect(ui->showGraphics, SIGNAL(stateChanged(int)), this, SLOT(updateViewsVisibility()));
    connect(ui->showTable,    SIGNAL(stateChanged(int)), this, SLOT(updateViewsVisibility()));

    connect(m_graphics, SIGNAL(closing()), this, SLOT(graphicsClosed()));
}

DisplayMeltmodel::~DisplayMeltmodel()
{
    m_autoRepeat = false;

    writeConfigFile();
    delete m_graphics;
    delete m_delegate;
    delete m_meltmodel;
    delete ui;
}

void DisplayMeltmodel::initModel()
{
    m_modelTime = 0;
    ui->time->setText(QString::number(m_modelTime));

    startNewModel(ui->x->text().toInt(), ui->y->text().toInt(), ui->startTemp->text().toDouble());
}

void DisplayMeltmodel::step()
{
    m_modelTime += ModelConstants::dt;
    ui->time->setText(QString::number(m_modelTime));

    m_meltmodel->processStep();
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
        m_graphics->show();
    else
        m_graphics->hide();

    if(ui->showTable->isChecked())
        m_table->show();
    else
        m_table->hide();
}

void DisplayMeltmodel::graphicsClosed()
{
    ui->showGraphics->setChecked(false);
}

void DisplayMeltmodel::autoRepeatOn()
{
    if(!m_meltmodel)
        initModel();

    m_autoRepeat = true;

    while(m_autoRepeat)
    {
        QApplication::processEvents();
        if(m_closed)
            return;
        step();
    }

}

void DisplayMeltmodel::autoRepeatOff()
{
    m_autoRepeat = false;
}

void DisplayMeltmodel::writeConfigFile()
{
    QSettings settings("modelSettings", QSettings::IniFormat);
    settings.beginGroup("GUI settings");
        settings.setValue("geometry", geometry());
        settings.setValue("viewGeometry", m_graphics->geometry());
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
        setGeometry(settings.value("geometry", QRect(100, 100, 100, 100)).toRect());
        m_graphics->setGeometry(settings.value("viewGeometry", QRect(100, 100, 100, 300)).toRect());
        ui->showTable->setChecked(settings.value("showTable", false).toBool());
        ui->showGraphics->setChecked(settings.value("showGraphics", false).toBool());
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

void DisplayMeltmodel::initConstants()
{
    ModelConstants::dx = ui->dx->text().toDouble();
    ModelConstants::dy = ui->dy->text().toDouble();
    ModelConstants::dt = ui->dt->text().toDouble();

    double iceC      = ui->iceC->text().toDouble();
    double icelambda = ui->iceLambda->text().toDouble();
    double iceR      = ui->iceR->text().toDouble();

    ModelConstants::setEnvironmentConstants(ICE, iceC, icelambda, iceR);

    double waterC      = ui->waterC->text().toDouble();
    double waterlambda = ui->iceLambda->text().toDouble();
    double waterR      = ui->waterR->text().toDouble();

    ModelConstants::setEnvironmentConstants(WATER, waterC, waterlambda, waterR);
}

void DisplayMeltmodel::startNewModel(int _width, int _height, double _startTemperature)
{
    delete m_meltmodel;
    m_meltmodel = new MeltModel(_width, _height, _startTemperature);
    connect(m_meltmodel, SIGNAL(step()), m_graphics, SLOT(modelStep()));

    setupModel();
}

void DisplayMeltmodel::setupModel()
{
    connect(ui->step, SIGNAL(clicked()), this, SLOT(step()));
    m_table->setModel(m_meltmodel);
    m_graphics->setModel(m_meltmodel);

    connect(m_meltmodel, SIGNAL(updateMaxTemp(double)), SLOT(updateMaxTemp(double)));
    connect(m_meltmodel, SIGNAL(updateMinTemp(double)), SLOT(updateMinTemp(double)));
    m_meltmodel->updateMinAndMaxTemp();

    m_graphics->setDelegate(m_delegate);
    m_meltmodel->beginSaveSteps();
}

void DisplayMeltmodel::closeEvent(QCloseEvent*)
{
    if(m_autoRepeat)
        m_closed = true;
    else
        deleteLater();
}
