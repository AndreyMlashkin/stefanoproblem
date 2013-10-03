#include <QDebug>
#include <QString>
#include <QFile>
#include <QDataStream>

#include "meltmodel.h"
#include "deltavolume.h"
#include "modelconstants.h"

#include "array2d.h"
#include "meltlogics.h"

#include "stepssaver.h"

namespace model
{

MeltModel::MeltModel(int _width, int _height, double _startTemperature)
    : QAbstractItemModel(),
      m_field(new ModelField(_width, _height, _startTemperature))
{
    initModel();
}

MeltModel::MeltModel(int _width, int _height)
    : QAbstractItemModel(),
      m_field(new ModelField(_width, _height))
{
    initModel();
}

void MeltModel::initModel()
{
    m_saveSteps = false;

    m_field->readDrillConfig();

    m_frameProcessor = new MeltLogics(m_field);
    m_stepsSaver = new StepsSaver(QString("stepdump.txt"));
}

MeltModel::MeltModel()
    : QAbstractItemModel(),
      m_field(NULL),
      m_frameProcessor()
{}

MeltModel::~MeltModel()
{
    m_field->writeDrillConfig();
    delete m_stepsSaver;
    delete m_frameProcessor;
    delete m_field;
}

QVariant MeltModel::data(const QModelIndex &index, int role) const
{
    if(!m_field)
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();
    int i = index.row();
    int j = index.column();
    double temp = getTemperatureInPos(i, j);

    return QString::number(toCelsius(temp), 'f', 5);
}

int MeltModel::rowCount(const QModelIndex&) const
{
    if(!m_field)
        return 0;

    return m_frameProcessor->realHeight();
}

int MeltModel::columnCount(const QModelIndex&) const
{
    if(!m_field)
        return 0;

    return m_frameProcessor->realWidth();
}

QModelIndex MeltModel::index(int _row, int _column, const QModelIndex&) const
{
    if(!m_field)
        return QModelIndex();

    DeltaVolume* d = getDeltaVolumeInPos(_row, _column);

    void* data = reinterpret_cast<void*> (d);

    return createIndex(_row, _column, data);
}

QModelIndex MeltModel::parent(const QModelIndex& /*child*/) const
{
    return QModelIndex();
}

Qt::ItemFlags MeltModel::flags(const QModelIndex&) const
{
    return 0;
}

bool MeltModel::saveStep(const QString& _fileName)
{
    return m_frameProcessor->saveStep(_fileName);
}

bool MeltModel::loadStep(const QString& _fileName)
{
    beginResetModel();

    delete m_frameProcessor;
    delete m_field;

    m_frameProcessor = new MeltLogics();
    m_field = m_frameProcessor->loadStep(_fileName);

    endResetModel();

    return true;
}

void MeltModel::updateMinAndMaxTemp()
{
    double maxT = -5000;
    double minT =  5000;
    for(ModelField::iterator i = m_field->begin(); i != m_field->end(); i++)
    {
        if((*i).type() == Drill)
            continue;

        if(maxT < (*i).temperature())
            maxT = ((*i).temperature());

        if(minT > (*i).temperature())
            minT = ((*i).temperature());
    }

    emit updateMaxTemp(maxT);
    emit updateMinTemp(minT);
}

void MeltModel::beginSaveSteps(bool _shouldSave)
{
    m_saveSteps = _shouldSave;
}

ModelField *MeltModel::field()
{
    return m_field;
}

void MeltModel::processStep()
{
    if(m_saveSteps)
        m_stepsSaver->saveStep(m_field);

    beginResetModel();
    m_field = m_frameProcessor->nextFrame();
    updateMinAndMaxTemp();

    emit step();
    endResetModel();
}

void MeltModel::updateBehaviour()
{
    m_frameProcessor->updateBehaviour();
}

double MeltModel::getTemperatureInPos(int _row, int _column) const
{
    return getDeltaVolumeInPos(_row, _column)->temperature();
}

DeltaVolume *MeltModel::getDeltaVolumeInPos(int _row, int _column) const
{
    int fieldColumn;
    if(_column >= m_field->width())
        fieldColumn = _column - m_field->width();
    else
        fieldColumn = m_field->width() - 1 - _column;
    return &(*m_field)[_row][fieldColumn];
}

}
