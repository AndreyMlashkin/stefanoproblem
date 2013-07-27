#ifndef MELTMODEL_H
#define MELTMODEL_H

#include <QAbstractItemModel>
#include <QObject>

class Field;
class MeltLogics;

class MeltModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    MeltModel(int _width, int _height, double _startTemperature);
    ~MeltModel();
    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    virtual int rowCount(const QModelIndex&) const;
    virtual int columnCount(const QModelIndex&) const;
    QModelIndex index(int row, int column, const QModelIndex&) const;
    QModelIndex parent(const QModelIndex& child) const;

public slots:
    void processStep();

private:
    MeltLogics* m_frameProcessor;
    Field* m_field;
};

#endif // MELTMODEL_H
