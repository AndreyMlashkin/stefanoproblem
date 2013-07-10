#ifndef MELTMODEL_H
#define MELTMODEL_H

class DeltaVolume;

class MeltModel
{
public:
    MeltModel(int width, int height);

private:
    int m_height, m_width;
    DeltaVolume* m_field;
};

#endif // MELTMODEL_H
