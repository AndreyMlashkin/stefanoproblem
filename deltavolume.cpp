#include <QDebug>

#include "deltavolume.h"

DeltaVolume::DeltaVolume()
    : //m_behaviour(NULL),
      m_type(NoType),
      m_behaviour(NoBehaviour)
{}

void DeltaVolume::setBehaviour(Behaviour _b)
{
    m_behaviour = _b;
}

Behaviour DeltaVolume::behaviour() const
{
    return m_behaviour;
}

DeltaVolume::Type DeltaVolume::type() const
{
    return m_type;
}

void DeltaVolume::setType(Type _type)
{
    m_type = _type;
}

void DeltaVolume::setTemperature(double _temp)
{
    m_temperature = _temp;
}

double DeltaVolume::temperature() const
{
    return m_temperature;
}
