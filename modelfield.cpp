#include "modelfield.h"

ModelField::ModelField(int _width, int _height, double _fillBy)
    : Array2d(_width, _height)
{
    initBehaviour();
    fillBy(_fillBy);
}

ModelField::ModelField(int _width, int _height)
    : Array2d(_width, _height)
 {
    initBehaviour();
}

void ModelField::fillBy(double _n)
{
    Array2d::iterator i;
    for(i = begin(); i != end(); i++)
        (*i).setTemperature(_n);
}

void ModelField::initBehaviour()
{
    for(int i = 0; i < m_width * m_height; i++)
        {
            if(((i + 1) % m_width == 0) || (i > (m_height-1) * m_width - 1) || (i < m_width))
                m_array[i].setBehaviour(Border);
            else if(i % m_width == 0)
                m_array[i].setBehaviour(Central);
            else
                m_array[i].setBehaviour(Normal);
    }
}

void ModelField::readDrillConfig()
{
    QFile file("drill.config");
    if (!file.open(QIODevice::ReadOnly))
        return;

    QTextStream stream(&file);

    while(!stream.atEnd())
    {
        int x; stream >> x;
        int y; stream >> y;

        (*this)[y][x].setType(DeltaVolume::Drill);
    }
}

