#ifndef MELTMODEL_H
#define MELTMODEL_H

class DeltaVolume;

class MeltModel
{
public:
    MeltModel(int height, int width);

private:
    int m_height, m_width;
    DeltaVolume* m_field;
};

#endif // MELTMODEL_H
