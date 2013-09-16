#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <iterator>

template<typename T>
class Array2d
{
public:
    class iterator : public std::iterator<std::input_iterator_tag, T>
    {
    public:
      iterator() {}

      explicit iterator(T* _x, Array2d<T>* _parent)
      : m_pointer(_x),
        m_parent(_parent),
        m_nextNeighbour(0)
      {}

      iterator(const iterator& mit)
      : m_pointer(mit.m_pointer),
        m_parent(mit.m_parent),
        m_nextNeighbour(0)
      {}

      iterator& operator++(int)
      {
            ++m_pointer;
            return *this;
      }

      iterator& operator+(int _n)
      {
          m_pointer += _n;
          return *this;
      }


      iterator& operator-(int _n)
      {
          m_pointer -= _n;
          return *this;
      }

      bool operator==(const iterator& rhs)
      {
          return (m_pointer == rhs.m_pointer) && (m_parent == rhs.m_parent);
      }

      bool operator!=(const iterator& rhs)
      {
          return (m_pointer != rhs.m_pointer) || (m_parent != rhs.m_parent);
      }

      T& operator*()
      {
          return *m_pointer;
      }

      T* operator->()
      {
          return m_pointer;
      }

      T& operator[](int _n)
      {
          return *(m_pointer + _n);
      }

      T* leftNeighbour()
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
      T* rightNeighbour()
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

      T* topNeighbour()
      {
          int numInArray = numberInArray();

          if(numInArray < m_parent->width())
                return NULL;
          if(numInArray > m_parent->width() * m_parent->height())
            return NULL;

          return m_pointer - m_parent->width();
      }

      T* bottomNeighbour()
      {
          int numInArray = numberInArray();
          int itemsTillEnd = m_parent->width() * m_parent->height() - numInArray;

          if(itemsTillEnd <= m_parent->width())
                return NULL;
          if(numInArray < 0)
                return NULL;

          return m_pointer + m_parent->width();
      }

      T* nextNeighbour()
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


      bool isNextNeighbour()
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

      void resetNext()
      {
          m_nextNeighbour = 0;
      }
    private:
      inline int numberInArray()
      {
          return m_pointer - m_parent->begin().m_pointer;
      }

    private:
      Array2d* m_parent;
      T* m_pointer;
      char m_nextNeighbour; // перечисление соседей 0-3 - против часовой стрелки с самого правого

    }; // END ITERATOR

    explicit Array2d(int _width, int _height, double _fillBy)
        : m_width((_width+1)/2),
          m_height(_height),
          m_array(new T[m_height * m_width])
    {
        fillBy(_fillBy);
        initBehaviour();
    }

    explicit Array2d(int _width, int _height)
        : m_width((_width+1)/2),
          m_height(_height),
          m_array(new T[m_height * m_width])
    {
        initBehaviour();
    }

    explicit Array2d(const Array2d& _f)
        : m_height(_f.m_height),
          m_width(_f.m_width),
          m_array(new T[m_height * m_width])
    {
        initBehaviour();

        for(int i = 0; i < m_height; i++)
            for(int j = 0; j < m_width; j++)
                m_array[i * m_width + j] = _f.m_array[i * m_width + j];
    }

    void fillBy(double _n)
    {
        Array2d::iterator i;
        for(i = begin(); i != end(); i++)
            (*i).setTemperature(_n);
    }


    iterator begin()
    {
        return iterator(m_array, this);
    }

    iterator end()
    {
        return iterator(m_array + (m_height * m_width), this);
    }

    iterator operator[](int n)
    {
        return begin() + n * m_width;
    }

    const int height()
    {
        return m_height;
    }

    const int width()
    {
        return m_width;
    }

private:
    void initBehaviour()
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
    void setDrillBehaviour()
    {
        QFile file("drill.config");
        if (!file.open(QIODevice::ReadOnly))
            return;

        QTextStream stream(&file);

        while(!stream.atEnd())
        {
            int x; stream >> x;
            int y; stream >> y;

            (*this)[y][x].setType(T::Drill);
        }
    }

private:
    int m_width, m_height;
    T* m_array;

    friend class Array2d;
};



#endif // ARRAY2D_H

