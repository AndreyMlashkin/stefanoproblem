#ifndef FIELD_H
#define FIELD_H

#include <iterator>

class DeltaVolume;
class Field
{
public:
    class iterator;

    Field(int _width, int _height, int _startTemerature);
    Field(int _width, int _height);
    Field(const Field& _f);
    void setStartTemperature(int _startTemp);
    iterator begin();
    iterator end();
    iterator operator[](int n);
    const int height();
    const int width();
private:
    void initBehaviour();
private:
    int m_width, m_height;
    DeltaVolume* m_field;
};

class Field::iterator : public std::iterator<std::input_iterator_tag, DeltaVolume>
{
public:
  iterator() {}
  explicit iterator(DeltaVolume* _x, Field* _parent);
  iterator(const iterator& mit);
  iterator& operator++(int);
  iterator& operator+(int _n);
  bool operator==(const iterator& rhs);
  bool operator!=(const iterator& rhs);
  DeltaVolume& operator*();
  DeltaVolume* operator->();
  DeltaVolume& operator[](int _n);

  DeltaVolume* leftNeighbour();
  DeltaVolume* rightNeighbour();
  DeltaVolume* topNeighbour();
  DeltaVolume* bottomNeighbour();

private:
  inline int numberInArray();

private:
  Field* m_parent;
  DeltaVolume* m_pointer;
};

#endif // FIELD_H

