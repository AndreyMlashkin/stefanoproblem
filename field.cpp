#include <QDebug>

#include "field.h"
#include "deltavolume.h"

Field::iterator::iterator(DeltaVolume* _x, Field* _parent)
    : m_pointer(_x),
      m_parent(_parent)
{}

Field::iterator::iterator(const iterator& mit)
    : m_pointer(mit.m_pointer),
      m_parent(mit.m_parent)
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

    if(itemsTillEnd < m_parent->width())
          return NULL;
    if(numInArray < 0)
          return NULL;

    return m_pointer + m_parent->width();
}

int Field::iterator::numberInArray()
{
    return m_pointer - m_parent->begin().m_pointer;

}

// --------------------------------------------------------------------

Field::Field(int _width, int _height, int _startTemperature)
    : m_width((_width+1)/2),
      m_height(_height),
      m_field(new DeltaVolume[m_height * m_width])
{
    setStartTemperature(_startTemperature);
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
{}

void Field::setStartTemperature(int _startTemp)
{
    Field::iterator i;
    for(i = begin(); i != end(); i++, _startTemp++)
        (*i).setTemperature(_startTemp);
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
        else if(i % m_width == 0)
            m_field[i].setBehaviour(Central);
        else
            m_field[i].setBehaviour(Normal);
    }
}

