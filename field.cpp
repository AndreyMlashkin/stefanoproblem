#include <QDebug>
#include <QFile>
#include <QStringList>

#include "field.h"
#include "deltavolume.h"

Field::iterator::iterator(DeltaVolume* _x, Field* _parent)
    : m_pointer(_x),
      m_parent(_parent),
      m_nextNeighbour(0)
{}

Field::iterator::iterator(const iterator& mit)
    : m_pointer(mit.m_pointer),
      m_parent(mit.m_parent),
      m_nextNeighbour(0)
{}

Field::iterator &Field::iterator::operator ++(int)
{
    ++m_pointer;
    return *this;
}

Field::iterator &Field::iterator::operator +(int _n)
{
    m_pointer += _n;
    return *this;
}

Field::iterator &Field::iterator::operator -(int _n)
{
    m_pointer -= _n;
    return *this;
}

bool Field::iterator::operator ==(const Field::iterator &rhs)
{
    return (m_pointer == rhs.m_pointer) && (m_parent == rhs.m_parent);
}

bool Field::iterator::operator !=(const Field::iterator &rhs)
{
    return (m_pointer != rhs.m_pointer) || (m_parent != rhs.m_parent);
}

DeltaVolume &Field::iterator::operator *()
{
    return *m_pointer;
}

DeltaVolume* Field::iterator::operator ->()
{
    return m_pointer;
}

DeltaVolume& Field::iterator::operator [](int _n)
{
    return *(m_pointer + _n);
}

DeltaVolume* Field::iterator::leftNeighbour()
{
    int numInArray = numberInArray();

    if((numInArray % m_parent->width()) == 0)
      return NULL;
    if(numInArray > m_parent->width() * m_parent->height())
        return NULL;
    if(numInArray < 0)
        return NULL;

    return m_pointer-1;
}

DeltaVolume *Field::iterator::rightNeighbour()
{
    int nextInArray = numberInArray() + 1;

    if((nextInArray % m_parent->width()) == 0)
      return NULL;
    if(nextInArray < 0)
      return NULL;
    if(nextInArray >= m_parent->width() * m_parent->height())
        return NULL;

    return m_pointer + 1;
}

DeltaVolume *Field::iterator::topNeighbour()
{
    int numInArray = numberInArray();

    if(numInArray < m_parent->width())
          return NULL;
    if(numInArray > m_parent->width() * m_parent->height())
      return NULL;

    return m_pointer - m_parent->width();
}

DeltaVolume *Field::iterator::bottomNeighbour()
{
    int numInArray = numberInArray();
    int itemsTillEnd = m_parent->width() * m_parent->height() - numInArray;

    if(itemsTillEnd <= m_parent->width())
          return NULL;
    if(numInArray < 0)
          return NULL;

    return m_pointer + m_parent->width();
}

DeltaVolume *Field::iterator::nextNeighbour()
{
    if(!isNextNeighbour())
        return NULL;

    if(m_nextNeighbour == 0)
    {
        m_nextNeighbour++;
        return rightNeighbour();
    }
    if(m_nextNeighbour == 1)
    {
        m_nextNeighbour++;
        return topNeighbour();
    }
    if(m_nextNeighbour == 2)
    {
        m_nextNeighbour++;
        return leftNeighbour();
    }
    if(m_nextNeighbour == 3)
    {
        m_nextNeighbour++;
        return bottomNeighbour();
    }

    qDebug() << "Eroor! DeltaVolume *Field::iterator::nextNeighbour()";
    return NULL;
}

bool Field::iterator::isNextNeighbour()
{
    if((m_nextNeighbour == 0) && (rightNeighbour() == NULL))
        m_nextNeighbour++;
    if((m_nextNeighbour == 1) && (topNeighbour() == NULL))
        m_nextNeighbour++;
    if((m_nextNeighbour == 2) && (leftNeighbour() == NULL))
        m_nextNeighbour++;
    if(((m_nextNeighbour == 3) && (bottomNeighbour() == NULL)) || m_nextNeighbour == 4)
    {
        m_nextNeighbour = 0;
        return false;
    }
    return true;
}

void Field::iterator::resetNext()
{
    m_nextNeighbour = 0;
}

int Field::iterator::numberInArray()
{
    return m_pointer - m_parent->begin().m_pointer;

}

// -----[--]---[--]---[--]---[--]---[--]---[--]---[--]---[--]---[--]---[--]---[--]---[--]---[--]-------------------------

Field::Field(int _width, int _height, double _startTemperature)
    : m_width((_width+1)/2),
      m_height(_height),
      m_field(new DeltaVolume[m_height * m_width])
{
    fillBy(_startTemperature);
    initBehaviour();
}

Field::Field(int _width, int _height)
    : m_width((_width+1)/2),
      m_height(_height),
      m_field(new DeltaVolume[m_height * m_width])
{
    initBehaviour();
}

Field::Field(const Field &_f)
    : m_height(_f.m_height),
      m_width(_f.m_width),
      m_field(new DeltaVolume[m_height * m_width])
{
    initBehaviour();

//    memcpy(m_field, _f.m_field, m_height * m_width);

    for(int i = 0; i < m_height; i++)
        for(int j = 0; j < m_width; j++)
            m_field[i * m_width + j] = _f.m_field[i * m_width + j];
}

void Field::fillBy(double _n)
{
    Field::iterator i;
    for(i = begin(); i != end(); i++)
        (*i).setTemperature(_n);
}

Field::iterator Field::begin()
{
    return iterator(m_field, this);
}

Field::iterator Field::end()
{
    return iterator(m_field + (m_height * m_width), this);
}

Field::iterator Field::operator [](int n)
{
    return begin() + n * m_width;
}

const int Field::height()
{
    return m_height;
}

const int Field::width()
{
    return m_width;
}

void Field::initBehaviour()
{
    for(int i = 0; i < m_width * m_height; i++)
    {
        if(((i + 1) % m_width == 0) || (i > (m_height-1) * m_width - 1) || (i < m_width))
            m_field[i].setBehaviour(Border);
//        else if(i % m_width == 0)
//            m_field[i].setBehaviour(Drill);
        else
            m_field[i].setBehaviour(Normal);
    }
    setDrillBehaviour();
}

void Field::setDrillBehaviour()
{
    QFile file("drill.config");
    if (!file.open(QIODevice::ReadOnly))
        return;

    QTextStream stream(&file);

    while(!stream.atEnd())
    {
        int x; stream >> x;
        int y; stream >> y;

        (*this)[y][x].setBehaviour(Drill);
    }
}

