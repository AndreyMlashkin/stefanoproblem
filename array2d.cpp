#include <QDebug>
#include <QFile>
#include <QStringList>

#include "array2d.h"



/*Array2d::iterator::iterator(T* _x, Array2d<T>* _parent)
    : m_pointer(_x),
      m_parent(_parent),
      m_nextNeighbour(0)
{}

Array2d::iterator::iterator(const iterator& mit)
    : m_pointer(mit.m_pointer),
      m_parent(mit.m_parent),
      m_nextNeighbour(0)
{}

Array2d::iterator &Array2d::iterator::operator ++(int)
{
    ++m_pointer;
    return *this;
}

Array2d::iterator &Array2d::iterator::operator +(int _n)
{
    m_pointer += _n;
    return *this;
}

Array2d::iterator &Array2d::iterator::operator -(int _n)
{
    m_pointer -= _n;
    return *this;
}

bool Array2d::iterator::operator ==(const Array2d::iterator &rhs)
{
    return (m_pointer == rhs.m_pointer) && (m_parent == rhs.m_parent);
}

bool Array2d::iterator::operator !=(const Array2d::iterator &rhs)
{
    return (m_pointer != rhs.m_pointer) || (m_parent != rhs.m_parent);
}

T &Array2d::iterator::operator *()
{
    return *m_pointer;
}

T* Array2d::iterator::operator ->()
{
    return m_pointer;
}

T& Array2d::iterator::operator [](int _n)
{
    return *(m_pointer + _n);
}

T* Array2d::iterator::leftNeighbour()
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

T *Array2d::iterator::rightNeighbour()
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

T *Array2d::iterator::topNeighbour()
{
    int numInArray = numberInArray();

    if(numInArray < m_parent->width())
          return NULL;
    if(numInArray > m_parent->width() * m_parent->height())
      return NULL;

    return m_pointer - m_parent->width();
}

T *Array2d::iterator::bottomNeighbour()
{
    int numInArray = numberInArray();
    int itemsTillEnd = m_parent->width() * m_parent->height() - numInArray;

    if(itemsTillEnd <= m_parent->width())
          return NULL;
    if(numInArray < 0)
          return NULL;

    return m_pointer + m_parent->width();
}

T *Array2d::iterator::nextNeighbour()
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

    qDebug() << "Eroor! T *Array2d::iterator::nextNeighbour()";
    return NULL;
}

bool Array2d::iterator::isNextNeighbour()
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

void Array2d::iterator::resetNext()
{
    m_nextNeighbour = 0;
}

int Array2d::iterator::numberInArray()
{
    return m_pointer - m_parent->begin().m_pointer;
}
*/

// -----[--]---[--]---[--]---[--]---[--]---[--]---[--]---[--]---[--]---[--]---[--]---[--]---[--]-------------------------

//Array2d::Array2d(int _width, int _height, double _fillBy)
//    : m_width((_width+1)/2),
//      m_height(_height),
//      m_field(new T[m_height * m_width])
//{
//    fillBy(_fillBy);
//    initBehaviour();
//}

//Array2d::Array2d(int _width, int _height)
//    : m_width((_width+1)/2),
//      m_height(_height),
//      m_field(new T[m_height * m_width])
//{
//    initBehaviour();
//}

//Array2d::Array2d(const Array2d &_f)
//    : m_height(_f.m_height),
//      m_width(_f.m_width),
//      m_field(new T[m_height * m_width])
//{
//    initBehaviour();

//    for(int i = 0; i < m_height; i++)
//        for(int j = 0; j < m_width; j++)
//            m_field[i * m_width + j] = _f.m_field[i * m_width + j];
//}

//void Array2d::fillBy(double _n)
//{
//    Array2d::iterator i;
//    for(i = begin(); i != end(); i++)
//        (*i).setTemperature(_n);
//}

//Array2d::iterator Array2d::begin()
//{
//    return iterator(m_field, this);
//}

//Array2d::iterator Array2d::end()
//{
//    return iterator(m_field + (m_height * m_width), this);
//}

//Array2d::iterator Array2d::operator [](int n)
//{
//    return begin() + n * m_width;
//}

//const int Array2d::height()
//{
//    return m_height;
//}

//const int Array2d::width()
//{
//    return m_width;
//}

//void Array2d::initBehaviour()
//{
//    for(int i = 0; i < m_width * m_height; i++)
//    {
//        if(((i + 1) % m_width == 0) || (i > (m_height-1) * m_width - 1) || (i < m_width))
//            m_field[i].setBehaviour(Border);
//        else if(i % m_width == 0)
//            m_field[i].setBehaviour(Central);
//        else
//            m_field[i].setBehaviour(Normal);
//    }
//}

//void Array2d::setDrillBehaviour()
//{
//    QFile file("drill.config");
//    if (!file.open(QIODevice::ReadOnly))
//        return;

//    QTextStream stream(&file);

//    while(!stream.atEnd())
//    {
//        int x; stream >> x;
//        int y; stream >> y;

//        (*this)[y][x].setType(T::Drill);
//    }
//}

