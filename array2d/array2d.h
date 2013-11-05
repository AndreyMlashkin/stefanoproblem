// ---------------------------
// Это шаблонный класс, в духе контейнеров stl, создает квадратную матрицу из элементов типа аргумента шаблона.
// При этом, память не фрагментируется, доступ к элементу - O(1).
// ---------------------------

#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <QDebug>

template<typename T>
class Array2d
{
public:
#include "arrayiterator.h"

    explicit Array2d(int _width, int _height)
        : m_height(_height),
          m_width((_width+1)/2),
          m_array(new T[m_height * m_width])
    {}

    explicit Array2d(const Array2d& _f)
        : m_height(_f.m_height),
          m_width(_f.m_width),
          m_array(new T[m_height * m_width])
    {
        for(int i = 0; i < m_height; i++)
            for(int j = 0; j < m_width; j++)
                m_array[i * m_width + j] = _f.m_array[i * m_width + j];
    }

    virtual ~Array2d()
    {
        delete m_array;
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

    int height() const
    {
        return m_height;
    }

    int width() const
    {
        return m_width;
    }

protected:
    int m_height;
    int m_width;
    T* m_array;
};

#endif // ARRAY2D_H

