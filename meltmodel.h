#ifndef MELTMODEL_H
#define MELTMODEL_H

class Field;

class MeltModel
{
public:
    MeltModel(int _width, int _height, int _startTemperature);

private:
    Field* m_field;
};

#endif // MELTMODEL_H
