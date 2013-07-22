#ifndef MELTMODEL_H
#define MELTMODEL_H

#include <QAbstractItemModel>

class Field;

class MeltModel : public QAbstractItemModel
{
public:
    MeltModel(int _width, int _height, int _startTemperature);
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    virtual int rowCount(const QModelIndex&) const;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

private:
    Field* m_field;
};

#endif // MELTMODEL_H
