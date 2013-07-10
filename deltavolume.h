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

private:
    DeltaVolumeBehaviour* m_behaviour;
    VolumeType m_type;

    int m_temperature;
    int m_density;
};

#endif // DELTAVOLUME_H
