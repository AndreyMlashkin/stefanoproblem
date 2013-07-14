#include <QDebug>
#include <QString>

#include "meltmodel.h"
#include "deltavolume.h"
#include "field.h"

MeltModel::MeltModel(int _width, int _height, int _startTemperature)
    : m_field(new Field(_width, _height, _startTemperature))
{
    Field::iterator i;

    for(i = m_field->begin(); i != m_field->end(); i++)
        qDebug() << i->temperature(); //(*i).temperature();
}
