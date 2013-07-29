#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "meltlogics.h"
#include "deltavolume.h"

MeltLogics::MeltLogics(QObject* _parent)
    : QObject(_parent),
      m_current(NULL),
      m_prev(NULL)
{}

MeltLogics::MeltLogics(Field* _startFrame, QObject* _parent)
  : QObject(_parent),
    m_current(_startFrame),
    m_prev(new Field(*_startFrame))
{}

MeltLogics::~MeltLogics()
{
    delete m_prev;
}

bool MeltLogics::saveStep(const QString& _filename = "save.txt")
{   
    if(_filename.isNull())
        return false;

    QFile file(_filename);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);

        int width = (*m_current).width() * 2 - 1;
        out << width  << ' ' << (*m_current).height() << '\n';

        for(int i = 0; i < m_current->height(); i++)
        {
            for(int j = 0; j < m_current->width(); j++)
            {
                out << (*m_current)[i][j].temperature() << ' ';
            }
            out << '\n';
        }
        file.close();
        return true;
    }
    else
        return false;
}

Field *MeltLogics::loadStep(const QString &_filename)
{
    if(_filename.isNull())
        return NULL;

    QFile file(_filename);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);

        int width, height;
        in >> width >> height;

        delete m_current;
        delete m_prev;

        m_current = new Field(width, height);
        m_prev    = new Field(width, height);

        for(Field::iterator i = m_current->begin(); i != m_current->end(); i++)
        {
            double temp;
            in >> temp;
            (*i).setTemperature(temp);

        }
        return m_current;
    }
    else
        return NULL;


}

Field *MeltLogics::currentFrame()
{
    return m_current;
}

static double heating = 1;
Field* MeltLogics::nextFrame()
{
    swapFrames();

    double temperature = (*m_prev)[0][0].temperature();
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




