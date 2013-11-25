#ifndef MODELFIELD_H
#define MODELFIELD_H

#include "array2d/array2d.h"
#include "deltavolume.h"

namespace model
{

class ModelField : public Array2d<DeltaVolume>
{
public:
    explicit ModelField(int _width, int _height, double _fillBy);
    explicit ModelField(int _width, int _height);
    explicit ModelField(const ModelField& _f);
    ~ModelField();

    void readDrillConfig();
    void writeDrillConfig() const;

private:
    inline void fillBy(double _n);

    inline void initBehaviour();
    inline void initVolumes();
    inline void initSideAreas();

private:
    double* m_volume;
    double* m_sideArea;

};
}
#endif // MODELFIELD_H
