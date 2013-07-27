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
    // switch
    //qDebug() << _b;
}

void DeltaVolume::setTemperature(double _temp)
{
    m_temperature = _temp;
}

double DeltaVolume::temperature()
{
    return m_temperature;
}

double DeltaVolume::rTemperature()
{
    return *(&m_temperature);
}
