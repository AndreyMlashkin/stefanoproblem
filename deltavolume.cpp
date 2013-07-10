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
    qDebug() << _b;
}
