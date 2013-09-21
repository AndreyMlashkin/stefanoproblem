#include <QDebug>

#include "deltavolume.h"
#include "modelconstants.h"

DeltaVolume::DeltaVolume()
    : m_behaviour(NoBehaviour),
      m_type(NoType),
      m_innerEnergy(0)
{}

//bool DeltaVolume::isValid() const
//{
//    if((m_volume == -1) || (m_sideArea == -1))
//        return false;
//    return true;
//}

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

void DeltaVolume::setEnergy(double _energy)
{
    ModelConstants* constants = ModelConstants::getConstants(ICE);

    m_temperature += _energy / constants->c;
    m_innerEnergy += _energy;
}

double DeltaVolume::Energy()
{
    return m_innerEnergy;
}

void DeltaVolume::setTemperature(double _temp)
{
    m_temperature = _temp;
}

double DeltaVolume::temperature() const
{
    return m_temperature;
}
