#ifndef DELTAVOLUME_H
#define DELTAVOLUME_H

#include "modelapi.h"

namespace model
{

enum Behaviour{NoBehaviour, Normal, Border, Central, BehaviourCount};

class DeltaVolume
{
public:
    DeltaVolume();

    void setBehaviour(Behaviour _b);
    Behaviour behaviour() const;

    Type type() const;
    void setType(Type _type);
    void setEnergy(double _energy);
    double Energy();

    void setTemperature(double _temp);
    double temperature() const;

private:
    Behaviour m_behaviour;
    Type m_type;

    double m_temperature;
    double m_innerEnergy;
};

}
#endif // DELTAVOLUME_H
