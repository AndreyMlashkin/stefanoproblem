#include "deltavolumeiterator.h"
#include "field.h"

Field::iterator::iterator(DeltaVolume *x)
    :m_pointer(x)
{}

Field::iterator::iterator(const Field::iterator &mit)
    : m_pointer(mit.m_pointer)
{}

Field::iterator &Field::iterator::operator ++()
{
    ++m_pointer;
    return *this;
}

bool Field::iterator::operator ==(const Field::iterator &rhs)
{
    return m_pointer == rhs.m_pointer;
}

bool Field::iterator::operator !=(const Field::iterator &rhs)
{
    return m_pointer!=rhs.m_pointer;
}

DeltaVolume &Field::iterator::operator *()
{
    return *m_pointer;
}
