#ifndef MODELFIELD_H
#define MODELFIELD_H

#include "array2d.h"
#include "deltavolume.h"

class ModelField : public Array2d<DeltaVolume>
{
public:
    explicit ModelField(int _width, int _height, double _fillBy);
    explicit ModelField(int _width, int _height);
    explicit ModelField(const ModelField& _f);

    ~ModelField();

private:
    inline void fillBy(double _n);

    inline void initBehaviour();
    inline void initVolumes();
    inline void initSideAreas();

    void readDrillConfig();

private:
    double* m_volume;
    double* m_sideArea;

};

#endif // MODELFIELD_H
