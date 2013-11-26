#include <QFile>
#include <QStringList>
#include <qmath.h>

#include "modelfield.h"
#include "modelconstants.h"

namespace model
{

ModelField::ModelField(int _width, int _height, double _fillBy)
    : Array2d(_width, _height)
{
    initBehaviour();
    initVolumes();
    initSideAreas();

    fillBy(toKelvin(_fillBy));
}

ModelField::ModelField(int _width, int _height)
    : Array2d(_width, _height)
 {
    initBehaviour();
    initVolumes();
    initSideAreas();
}

ModelField::ModelField(const ModelField &_f)
    :Array2d(_f)
{
    initVolumes();
    initSideAreas();
}

ModelField::~ModelField()
{
    delete[] m_volume;
    delete[] m_sideArea;
}

void ModelField::readDrillConfig()
{
    QFile file("drill.config");
    if (!file.open(QIODevice::ReadOnly))
        return;

    QTextStream stream(&file);

    int height, width;
    stream >> height >> width;

    if((height == m_height) && (m_width == width))
    {
        while(!stream.atEnd())
        {
            int x;    stream >> x;
            int y;    stream >> y;
            int type; stream >> type;

            at(y, x)->setType(Type(type));
//            (*this)[y][x].setType(Type(type));
        }
    }
    file.close();
}

void ModelField::writeDrillConfig() const
{
    QFile file("drill.config");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;

    QTextStream stream(&file);

    stream << m_height << ' ' << m_width << '\n';
    for(int i = 0; i < m_height; i++)
        for(int j = 0; j < m_width; j++)
            stream << j << ' ' << i << ' ' << at(i, j) << '\n';
    file.close();
}

void ModelField::fillBy(double _n)
{
    Array2d::iterator i, last = end();
    for(i = begin(); i != last; i++)
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

void ModelField::initVolumes()
{
    m_volume = new double[m_width];

    int dx = ModelConstants::dx;
    int dy = ModelConstants::dy;

    for(int i = 0; i < m_width; i++)
        m_volume[i] = M_PI * dx * dy * (2*i * dx + dx);
}

void ModelField::initSideAreas()
{
    m_sideArea = new double[m_width];

    int dx = ModelConstants::dx;
    int dy = ModelConstants::dy;

    for(int i = 0; i < m_width; i++)
        m_sideArea[i] = 2 * M_PI * dy * (i*dx + dx);
}

}
