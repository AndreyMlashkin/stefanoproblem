
#include <iterator>

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

