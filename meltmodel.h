#ifndef MELTMODEL_H
#define MELTMODEL_H

#include <QAbstractItemModel>
#include <QObject>

class Field;
class MeltLogics;
class DeltaVolume;

class MeltModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit MeltModel(int _width, int _height, double _startTemperature);
    explicit MeltModel(int _width, int _height);
    MeltModel();
    ~MeltModel();

    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    virtual int rowCount(const QModelIndex&) const;
    virtual int columnCount(const QModelIndex&) const;
    QModelIndex index(int row, int column, const QModelIndex&) const;
    QModelIndex parent(const QModelIndex& child) const;

    bool saveStep(const QString& _fileName);
    bool loadStep(const QString& _fileName);

public slots:
    void processStep();

signals:
    void updateMaxTemp(double _temp);
    void updateMinTemp(double _temp);

private:
    inline double getTemperatureInPos(int _row, int _column) const;
    inline DeltaVolume* getDeltaVolumeInPos(int _row, int _column) const;

    void updateMinAndMaxTemp();

private:
    MeltLogics* m_frameProcessor;
    Field* m_field;

    double m_maxTemp;
    double m_minTemp;
};

#endif // MELTMODEL_H
