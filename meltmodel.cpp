#include <QDebug>
#include <QString>

#include "meltmodel.h"
#include "deltavolume.h"

#include "field.h"
#include "meltlogics.h"

MeltModel::MeltModel(int _width, int _height, double _startTemperature)
    : QAbstractItemModel()
{
    m_field = new Field(_width, _height, _startTemperature);
    m_frameProcessor = new MeltLogics(m_field);
}

MeltModel::MeltModel(int _width, int _height)
    : QAbstractItemModel()
{
    m_field = new Field(_width, _height);
    m_frameProcessor = new MeltLogics(m_field);
}

MeltModel::MeltModel()
    : QAbstractItemModel(),
      m_field(NULL),
      m_frameProcessor()
{}

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

int MeltModel::columnCount(const QModelIndex&) const
{
    if(!m_field)
        return 0;

    return m_frameProcessor->realWidth();
}

QModelIndex MeltModel::index(int _row, int _column, const QModelIndex&) const
{
//    if(!m_field)
//        return QModelIndex();

    double data = (*m_field)[_row][_column].temperature();
    // QString::number(data, 'f', 2)

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

void MeltModel::processStep()
{
    beginResetModel();
    m_field = m_frameProcessor->nextFrame();
    endResetModel();
}

double MeltModel::getTemperatureInPos(int _row, int _column) const
{
    int fieldColumn;
    if(_column >= m_field->width())
        fieldColumn = _column - m_field->width() + 1;
    else
        fieldColumn = m_field->width() - 1 - _column;
    return (*m_field)[_row][fieldColumn].temperature();
}

