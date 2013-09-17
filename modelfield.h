#ifndef MODELFIELD_H
#define MODELFIELD_H

#include <QFile>
#include <QStringList>

#include "array2d.h"
#include "deltavolume.h"


class ModelField : public Array2d<DeltaVolume>
{
public:
    explicit ModelField(int _width, int _height, double _fillBy);
    explicit ModelField(int _width, int _height);

private:
    inline void fillBy(double _n);

    void initBehaviour();
    void readDrillConfig();

  //  explicit ModelField(const ModelField& _f);
};

#endif // MODELFIELD_H
