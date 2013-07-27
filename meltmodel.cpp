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

MeltModel::~MeltModel()
{
    delete m_frameProcessor;
    delete m_field;
}

QVariant MeltModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    int i = index.row();
    int j = index.column();
    return QString::number((*m_field)[i][j].temperature(), 'f', 2);
}

int MeltModel::rowCount(const QModelIndex&) const
{
    return m_field->height();
}

int MeltModel::columnCount(const QModelIndex&) const
{
    return m_field->width();
}

QModelIndex MeltModel::index(int _row, int _column, const QModelIndex&) const
{
    double data = (*m_field)[_row][_column].temperature();
    // QString::number(data, 'f', 2)

    return createIndex(_row, _column, 1);

}

QModelIndex MeltModel::parent(const QModelIndex& child) const
{
    return QModelIndex();
}

void MeltModel::processStep()
{
    beginResetModel();
    m_field = m_frameProcessor->nextFrame();
    m_frameProcessor->saveStep();
    endResetModel();
}

