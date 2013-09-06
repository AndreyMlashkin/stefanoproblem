#ifndef DELTAVOLUME_H
#define DELTAVOLUME_H

enum VolumeType{NoType, Ice, Water, Dill};
enum Behaviour{NoBehaviour, Normal, Border, Central, Drill, BehaviourCount};

class DeltaVolume
{
public:
    DeltaVolume();
    void setType(VolumeType _type);
    void setBehaviour(Behaviour _b);
    Behaviour behaviour() const;

    void setTemperature(double _temp);
    double temperature() const;

private:
    Behaviour m_behaviour;
    VolumeType m_type;

    double m_temperature;
    int m_density;
};

#endif // DELTAVOLUME_H
