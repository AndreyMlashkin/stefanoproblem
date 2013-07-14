#ifndef MELTMODEL_H
#define MELTMODEL_H

#include <QAbstractItemModel>

class Field;

class MeltModel// : QAbstractItemModel
{
public:
    MeltModel(int _width, int _height, int _startTemperature);

private:
    Field* m_field;
};

#endif // MELTMODEL_H
