#include <QDebug>
#include <QString>

#include "meltmodel.h"
#include "deltavolume.h"


MeltModel::MeltModel(int height, int width)
    : m_height(height),
      m_width(width)
{
    m_field = new DeltaVolume[height * width];

    for(int i = 0; i < width * height; i++)
    {
        if((i % width == 0) || ((i + 1) % width == 0) || (i > (height-1) * width ))
            m_field[i].setBehaviour(Border);
        else
            m_field[i].setBehaviour(Normal);
    }
}
