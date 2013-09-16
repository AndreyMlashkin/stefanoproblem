#ifndef MODELFIELD_H
#define MODELFIELD_H

#include "array2d.h"
#include "deltavolume.h"

class ModelField : public Array2d<DeltaVolume>
{
public:
    explicit ModelField(int _width, int _height, double _fillBy)
        : Array2d(_width, _height, _fillBy)
    {}

    explicit ModelField(int _width, int _height)
        : Array2d(_width, _height)
    {}

  //  explicit ModelField(const ModelField& _f);
};

#endif // MODELFIELD_H
