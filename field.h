#ifndef FIELD_H
#define FIELD_H

#include <iterator>

class DeltaVolume;
class Field
{
public:
    class iterator;

    void setStartTemperature(int _startTemp);

    Field(int _width, int _height, int _startTemerature);
    iterator begin();
    iterator end();
    iterator operator[](int n);
    int height();
    int width();
private:
    int m_width, m_height;
    DeltaVolume* m_field;
};



class Field::iterator : public std::iterator<std::input_iterator_tag, DeltaVolume>
{
public:
  iterator() {}
  explicit iterator(DeltaVolume* x);
  iterator(const iterator& mit);
  iterator& operator++(int);
  iterator& operator+(int _n);
  bool operator==(const iterator& rhs);
  bool operator!=(const iterator& rhs);
  DeltaVolume& operator*();
  DeltaVolume* operator->();
  DeltaVolume& operator[](int _n);

private:
  DeltaVolume* m_pointer;
};

#endif // FIELD_H

