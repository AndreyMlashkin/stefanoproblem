#ifndef MELTMODEL_H
#define MELTMODEL_H

#include <QAbstractItemModel>
#include <QObject>

namespace model
{

class ModelField;
class MeltLogics;
class DeltaVolume;
class StepsSaver;

class MeltModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit MeltModel(int _width, int _height, double _startTemperature);
    explicit MeltModel(int _width, int _height);
    inline void initModel();
    MeltModel();
    ~MeltModel();

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex& _index = QModelIndex()) const;
    int columnCount(const QModelIndex& _index = QModelIndex()) const;
    QModelIndex index(int row, int column, const QModelIndex&  = QModelIndex()) const;
    QModelIndex parent(const QModelIndex& child) const;
    Qt::ItemFlags flags(const QModelIndex&) const;

    bool saveStep(const QString& _fileName) const;
    bool loadStep(const QString& _fileName);

    void updateMinAndMaxTemp();

    void beginSaveSteps(bool _shouldSave = true);

    ModelField* field() const;
    void resetToDefault();

public slots:
    void processStep();
    void updateBehaviour();

signals:
    void updateMaxTemp(double _temp);
    void updateMinTemp(double _temp);

    void step();

private:
    inline double getTemperatureInPos(int _row, int _column) const;
    inline DeltaVolume* getDeltaVolumeInPos(int _row, int _column) const;

private:
    ModelField* m_field;
    MeltLogics* m_frameProcessor;
    StepsSaver* m_stepsSaver;

    bool m_saveSteps;
};
}

#endif // MELTMODEL_H
