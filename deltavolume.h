#ifndef DELTAVOLUME_H
#define DELTAVOLUME_H

enum Behaviour{NoBehaviour, Normal, Border, Central, BehaviourCount};

class DeltaVolume
{
public:
    enum Type{NoType, Ice, Water, Drill};

    DeltaVolume();
//    bool isValid() const;

    void setBehaviour(Behaviour _b);
    Behaviour behaviour() const;

    DeltaVolume::Type type() const;
    void setType(DeltaVolume::Type _type);
    //   void setType(DeltaVolume::type _type);

    void setTemperature(double _temp);
    double temperature() const;


private:
    Behaviour m_behaviour;
    DeltaVolume::Type m_type;

    double m_temperature;
};

#endif // DELTAVOLUME_H
