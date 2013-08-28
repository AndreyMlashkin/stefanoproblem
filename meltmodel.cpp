#include <QDebug>
#include <QString>

#include "meltmodel.h"
#include "deltavolume.h"

#include "field.h"
#include "meltlogics.h"

MeltModel::MeltModel(int _width, int _height, double _startTemperature)
    : QAbstractItemModel(),
      m_maxTemp(-300),
      m_minTemp(5000)
{
    m_field = new Field(_width, _height, _startTemperature);
    m_frameProcessor = new MeltLogics(m_field);

    //updateMinAndMaxTemp();
}

MeltModel::MeltModel(int _width, int _height)
    : QAbstractItemModel(),
      m_maxTemp(-300),
      m_minTemp(5000)
{
    m_field = new Field(_width, _height);
    m_frameProcessor = new MeltLogics(m_field);

   // updateMinAndMaxTemp();
}

MeltModel::MeltModel()
    : QAbstractItemModel(),
      m_field(NULL),
      m_frameProcessor()
{
 //   updateMinAndMaxTemp();
}

MeltModel::~MeltModel()
{
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

    return QString::number(temp, 'f', 2);
}

int MeltModel::rowCount(const QModelIndex&) const
{
    if(!m_field)
        return 0;

    return m_frameProcessor->realHeight();
}

int MeltModel::columnCount(const QModelIndex&_index) const
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

QModelIndex MeltModel::parent(const QModelIndex& child) const
{
    return QModelIndex();
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
    double oldMax = m_maxTemp;
    double oldMin = m_minTemp;
    for(Field::iterator i = m_field->begin(); i != m_field->end(); i++)
    {
        if(m_maxTemp < (*i).temperature())
            m_maxTemp = ((*i).temperature());

        if(m_minTemp > (*i).temperature())
            m_minTemp = ((*i).temperature());
    }

    if(oldMax != m_maxTemp)
        emit updateMaxTemp(m_maxTemp);

    if(oldMin != m_minTemp)
        emit updateMinTemp(m_minTemp);
}

void MeltModel::processStep()
{
    beginResetModel();
    m_field = m_frameProcessor->nextFrame();
    updateMinAndMaxTemp();

    endResetModel();
}

double MeltModel::getTemperatureInPos(int _row, int _column) const
{
    return getDeltaVolumeInPos(_row, _column)->temperature();
}

DeltaVolume *MeltModel::getDeltaVolumeInPos(int _row, int _column) const
{
    int fieldColumn;
    if(_column >= m_field->width())
        fieldColumn = _column - m_field->width() + 1;
    else
        fieldColumn = m_field->width() - 1 - _column;
    return &(*m_field)[_row][fieldColumn];
}


