#include <QDebug>
#include "meltlogics.h"
#include "deltavolume.h"

MeltLogics::MeltLogics(Field* _startFrame, QObject* _parent) :
    QObject(_parent),
    m_current(_startFrame),
    m_prev(new Field(*_startFrame))
{}

MeltLogics::~MeltLogics()
{
  delete m_prev;
}

Field* MeltLogics::nextFrame()
{
    swapFrames();
    for(int i = 0; i < m_current->height(); i++)
        for(int j = 0; j < m_current->width(); j++)
        {
            int temperature = (*m_prev)[i][j].temperature();
            (*m_current)[i][j].setTemperature(temperature + 1);
        }

//    Field::iterator i = m_current->begin() + (1);
//    qDebug() << "rightNeighbour" << i.rightNeighbour();
//    qDebug() << "leftNeighbou" << i.leftNeighbour();
//    qDebug() << "bottomNeighbour" << i.bottomNeighbour();
//    qDebug() << "topNeighbour" << i.topNeighbour();

//    qDebug() << "rightNeighbour" << i.rightNeighbour()->temperature();
//    qDebug() << "leftNeighbou" << i.leftNeighbour()->temperature();
//    qDebug() << "bottomNeighbour" << i.bottomNeighbour()->temperature();
//    qDebug() << "topNeighbour" << i.topNeighbour()->temperature();

    return m_current;
}

void MeltLogics::swapFrames()
{
    Field* tmp = m_prev;
    m_prev = m_current;
    m_current = tmp;
}


