#ifndef DELTAVOLUME_H
#define DELTAVOLUME_H

#include "modelapi.h"

enum Behaviour{NoBehaviour, Normal, Border, Central, BehaviourCount};

class DeltaVolume
{
public:
    DeltaVolume();
//    bool isValid() const;

    void setBehaviour(Behaviour _b);
    Behaviour behaviour() const;

    Type type() const;
    void setType(DeltaVolume::Type _type);
    //   void setType(DeltaVolume::type _type);

    void setEnergy(double _energy);
    double Energy();

    void setTemperature(double _temp);
    double temperature() const;


private:
    Behaviour m_behaviour;
    DeltaVolume::Type m_type;

    double m_temperature;
    double m_innerEnergy;
};

#endif // DELTAVOLUME_H
