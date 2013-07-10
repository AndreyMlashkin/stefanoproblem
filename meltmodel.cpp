#include <QDebug>
#include <QString>

#include "meltmodel.h"
#include "deltavolume.h"


MeltModel::MeltModel(int width, int height)
    : m_width((width+1)/2),
      m_height(height)
{
    qDebug() << m_width;
    qDebug() << width << "x" << height;

    m_field = new DeltaVolume[m_height * m_width];

    for(int i = 0; i < m_width * m_height; i++)
    {
        if(((i + 1) % m_width == 0) || (i > (m_height-1) * m_width - 1) || (i < m_width))
            m_field[i].setBehaviour(Border);
        else if(i % m_width == 0)
            m_field[i].setBehaviour(Central);
        else
            m_field[i].setBehaviour(Normal);
    }
}
