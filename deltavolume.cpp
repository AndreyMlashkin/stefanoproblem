#include <QDebug>

#include "deltavolume.h"

DeltaVolume::DeltaVolume()
    : //m_behaviour(NULL),
      m_type(NoType)
{}

void DeltaVolume::setType(VolumeType _type)
{
    m_type = _type;
}

void DeltaVolume::setBehaviour(Behaviour _b)
{
    m_behaviour = _b;
}

Behaviour DeltaVolume::behaviour() const
{
    return m_behaviour;
}

void DeltaVolume::setTemperature(double _temp)
{
//    if(m_behaviour == Border)
//        m_temperature = -1;

    m_temperature = _temp;
}

double DeltaVolume::temperature() const
{
    return m_temperature;
}

//double DeltaVolume::rTemperature()
//{
//    return *(&m_temperature);
//}
