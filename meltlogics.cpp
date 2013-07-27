#include <QDebug>
#include <QFile>
#include <QTextStream>

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

void MeltLogics::saveStep()
{
    QFile file("F://proj//stefanoproblem//save.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    for(int i = 0; i < m_current->height(); i++)
    {
        for(int j = 0; j < m_current->width(); j++)
        {
            out << (*m_current)[i][j].temperature() << ' ';
        }
        out << '\n';
    }
    file.close();
}

void MeltLogics::loadStep()
{
}

static double heating = 0;
Field* MeltLogics::nextFrame()
{
    swapFrames();

    double temperature = (*m_prev)[0][0].temperature();
    heating++;
    (*m_prev)[0][0].setTemperature(temperature + heating);


    Field::iterator oldCell = m_prev->begin();
    Field::iterator newCell = m_current->begin();
    while(oldCell != m_prev->end())
    {
        double t = 0;
        while(oldCell.isNextNeighbour())
        {
            DeltaVolume* d = (oldCell.nextNeighbour());
            t += d->temperature();
        }
        double saf = t / 5;

        double oldTemp = (*oldCell).temperature();
        (*newCell).setTemperature(saf + oldTemp/5);
        newCell++;
        oldCell++;
    }

//    for(int i = 0; i < m_current->height(); i++)
//        for(int j = 0; j < m_current->width(); j++)
//        {
//            int temperature = (*m_prev)[i][j].temperature();
//            (*m_current)[i][j].setTemperature(temperature + 1);
//        }

    return m_current;
}

void MeltLogics::swapFrames()
{
    Field* tmp = m_prev;
    m_prev = m_current;
    m_current = tmp;
}


