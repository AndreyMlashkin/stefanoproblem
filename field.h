#ifndef FIELD_H
#define FIELD_H

#include <iterator>

class DeltaVolume;
class Field
{
public:
    class iterator : public std::iterator<std::input_iterator_tag, DeltaVolume>
    {
    public:
      iterator() {}
      iterator(DeltaVolume* x);
      iterator(const iterator& mit);
      iterator& operator++();
      bool operator==(const iterator& rhs);
      bool operator!=(const iterator& rhs);
      DeltaVolume& operator*();
    private:
      DeltaVolume* m_pointer;
    };


    void setStartTemperature(int _startTemp);

    Field(int _width, int _height, int _startTemerature);
    iterator begin();
    iterator end();

private:
    int m_width, m_height;
    DeltaVolume* m_field;
};

#endif // FIELD_H
