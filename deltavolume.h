#ifndef DELTAVOLUME_H
#define DELTAVOLUME_H

enum VolumeType{NoType, Ice, Water};
enum Behaviour{NoBehaviour, Normal, Border, Central};

class DeltaVolumeBehaviour;

class DeltaVolume
{
public:
    DeltaVolume();
    void setType(VolumeType _type);
    void setBehaviour(Behaviour _b);

    void setTemperature(double _temp);
    double temperature();
    double rTemperature();
private:
    DeltaVolumeBehaviour* m_behaviour;
    VolumeType m_type;

    double m_temperature;
    int m_density;
};

#endif // DELTAVOLUME_H
