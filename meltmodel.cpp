#include <QDebug>
#include <QString>

#include "meltmodel.h"
#include "deltavolume.h"
#include "field.h"

MeltModel::MeltModel(int _width, int _height, int _startTemperature)
    : QAbstractItemModel(),
      m_field(new Field(_width, _height, _startTemperature))
{
    Field::iterator i;

    for(i = m_field->begin(); i != m_field->end(); i++)
        qDebug() << i->temperature(); //(*i).temperature();
}

QVariant MeltModel::data(const QModelIndex &index, int role) const
{
    int i = index.column();
    int j = index.row();
    return (*m_field)[i][j].temperature();
}

int MeltModel::rowCount(const QModelIndex&) const
{
    return m_field->height();
}

int MeltModel::columnCount(const QModelIndex &parent) const
{
    return m_field->width();
}

QModelIndex MeltModel::index(int _row, int _column, const QModelIndex& _parent) const
{
    int data = (*m_field)[_row][_column].temperature();
    return createIndex(_row, _column, data);
}

QModelIndex MeltModel::parent(const QModelIndex &child) const
{
    return QModelIndex();
}

