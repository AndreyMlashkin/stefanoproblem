#ifndef FIELD_H
#define FIELD_H

#include <iterator>

class DeltaVolume;
class Field
{
public:
    class iterator;

    explicit Field(int _width, int _height, double _startTemerature);
    explicit Field(int _width, int _height);
    explicit Field(const Field& _f);
    void fillBy(double _n);
    iterator begin();
    iterator end();
    iterator operator[](int n);
    const int height();
    const int width();

private:
    void initBehaviour();
    void setDrillBehaviour();
private:
    int m_width, m_height;
    DeltaVolume* m_field;

    friend class Field;
};

class Field::iterator : public std::iterator<std::input_iterator_tag, DeltaVolume>
{
public:
  iterator() {}
  explicit iterator(DeltaVolume* _x, Field* _parent);
  iterator(const iterator& mit);
  iterator& operator++(int);
  iterator& operator+(int _n);
  iterator& operator-(int _n);
  bool operator==(const iterator& rhs);
  bool operator!=(const iterator& rhs);
  DeltaVolume& operator*();
  DeltaVolume* operator->();
  DeltaVolume& operator[](int _n);

  DeltaVolume* leftNeighbour();
  DeltaVolume* rightNeighbour();
  DeltaVolume* topNeighbour();
  DeltaVolume* bottomNeighbour();

  DeltaVolume* nextNeighbour();
  bool isNextNeighbour();
  void resetNext();
private:
  inline int numberInArray();

private:
  Field* m_parent;
  DeltaVolume* m_pointer;
  char m_nextNeighbour; // перечисление соседей 0-3 - против часовой стрелки с самого правого
};

#endif // FIELD_H

