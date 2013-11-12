#ifndef ARRAYITERATOR_H
#define ARRAYITERATOR_H

#include <iterator>

class iterator : public std::iterator<std::input_iterator_tag, T>
{
public:
  iterator()
  : m_parent(NULL),
    m_pointer(NULL),
    m_nextNeighbour(0)
  {}

  explicit iterator(T* _data, Array2d<T>* _parent)
  : m_parent(_parent),
    m_pointer(_data),
    m_nextNeighbour(0)
  {}

  iterator(const iterator& mit)
  : m_parent(mit.m_parent),
    m_pointer(mit.m_pointer),
    m_nextNeighbour(0)
  {}

  void operator=(T* _data) // this is not copy constructor
  {
       m_pointer = _data;
  }

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

  bool operator==(const iterator& rhs) const
  {
      return (m_pointer == rhs.m_pointer) && (m_parent == rhs.m_parent);
  }

  bool operator!=(const iterator& rhs) const
  {
      return (m_pointer != rhs.m_pointer) || (m_parent != rhs.m_parent);
  }

  T& operator*() const
  {
      return *m_pointer;
  }

  T* operator->() const
  {
      return m_pointer;
  }

  T& operator[](int _n) const
  {
      return *(m_pointer + _n);
  }

// ----------------------------------------------------------
  inline bool isValid() const
  {
      if(checkIfExist(numberInArray()))
          return m_parent;
      return false;
  }

  inline bool checkIfExist(const int& _numInArray) const
  {
     if(isRightBorder(_numInArray) || isOutOfLimit(_numInArray))
         return false;
     else
         return true;
  }

  inline bool isRightBorder(const int& _numInArray) const
  {
      return !(_numInArray % m_parent->width());
  }

  inline bool isOutOfLimit(const int& _numInArray) const
  {
      return (_numInArray > (m_parent->width() * m_parent->height())) && (_numInArray <= 0);
  }

  const iterator left() const
  {
      int numInArray = numberInArray();

      if(checkIfExist(numInArray))
          return iterator(m_pointer-1, m_parent);

      return iterator();
  }

  const iterator right() const
  {
      int numInArray = numberInArray() + 1;

      if(checkIfExist(numInArray))
          return iterator(m_pointer+1, m_parent);

      return iterator();
  }

  const iterator top() const
  {
      int numInArray = numberInArray() - m_parent->width();

      if(!isOutOfLimit(numInArray))
          return iterator(m_pointer - m_parent->width(), m_parent);

      return iterator();
  }

  const iterator bottom() const
  {
      int numInArray = numberInArray() + m_parent->width();

      if(!isOutOfLimit(numInArray))
          return iterator(m_pointer + m_parent->width(), m_parent);

      return iterator();
  }

  iterator next()
  {
      if(!isNextNeighbour())
          return iterator();

      if(m_nextNeighbour == 0)
      {
          m_nextNeighbour++;
          return right();
      }
      if(m_nextNeighbour == 1)
      {
          m_nextNeighbour++;
          return top();
      }
      if(m_nextNeighbour == 2)
      {
          m_nextNeighbour++;
          return left();
      }
      if(m_nextNeighbour == 3)
      {
          m_nextNeighbour++;
          return bottom();
      }

      qDebug() << "Eroor! T *Array2d::iterator::next()";
      return iterator();
  }

  bool isNextNeighbour()  // no const!
  {    
      skipInvalidNeighbours();
      if(m_nextNeighbour == 4)
      {
          m_nextNeighbour = 0;
          return false;
      }
      return true;
  }

/*  void resetNext()
  {
      m_nextNeighbour = 0;
  }
*/
  inline int numberInArray() const
  {
      return m_pointer - m_parent->begin().m_pointer;
  }

private:
  inline void skipInvalidNeighbours()
  {
      if((m_nextNeighbour == 0) && (!right().isValid()))
          m_nextNeighbour++;
      if((m_nextNeighbour == 1) && (!top().isValid()))
          m_nextNeighbour++;
      if((m_nextNeighbour == 2) && (!left().isValid()))
          m_nextNeighbour++;
      if((m_nextNeighbour == 3) && (!bottom().isValid()))
          m_nextNeighbour++;
  }

private:
  Array2d* m_parent;
  T* m_pointer;
  int m_nextNeighbour; // Перечисление соседей 0-3 - против часовой стрелки с самого правого вкючительно.

};

#endif //ARRAYITERATOR
