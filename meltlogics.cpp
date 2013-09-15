#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "meltlogics.h"
#include "deltavolume.h"
#include "modelconstants.h"

static double heating = 1;

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

        int width = realWidth();
        out << width  << ' ' << (*m_current).height() << '\n';

        for(int i = 0; i < m_current->height(); i++)
        {
            for(int j = 0; j < m_current->width(); j++)
            {
                out << (*m_current)[i][j].temperature() << '\t';
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

int MeltLogics::realWidth()
{
    return (*m_current).width() * 2;
}

int MeltLogics::realHeight()
{
    return (*m_current).height();
}

Field* MeltLogics::nextFrame()
{
    swapFrames();
    heat(m_prev);

    Field::iterator oldCell = m_prev->begin();
    Field::iterator newCell = m_current->begin();

    while(oldCell != m_prev->end())
    {
        if(((*oldCell).behaviour() != Border) && ((*oldCell).type() != DeltaVolume::Drill))
        {
            double koeff = calculateKoeff(oldCell);
            double oldTemp = (*oldCell).temperature();
            (*newCell).setTemperature(oldTemp + abs(oldTemp * koeff));
        }
        newCell++;
        oldCell++;
    }
    return m_current;
}

void MeltLogics::updateBehaviour()
{
    Field::iterator i = m_prev->begin();
    Field::iterator j = m_current->begin();

    for(; i != m_prev->end(); i++, j++)
        (*i).setType((*j).type());
}

void MeltLogics::swapFrames()
{
    Field* tmp = m_prev;
    m_prev = m_current;
    m_current = tmp;
}

void MeltLogics::heat(Field* _field)
{
    int k = 0;
    for(Field::iterator i = _field->begin(); i != _field->end(); i++)
    {
        if(i->type() == DeltaVolume::Drill)
        {
//            double temperature = (*i).temperature();
            (*i).setTemperature(0/*temperature + heating*/);
        }
        k++;
    }
}

double inline tempDiffusion()
{
    ModelConstants* constants = ModelConstants::getConstants(ICE);

    return constants->lambda / (constants->r * constants->c);
}

double MeltLogics::calculateKoeff(Field::iterator& _cell)
{
    const static double sqrA = tempDiffusion() * tempDiffusion();

    double curTemp = (*_cell).temperature();

    double lTemp;
    if((*_cell).behaviour() == Central)
           lTemp = curTemp;
    else
           lTemp = (*_cell.leftNeighbour()  ).temperature();
    double rTemp = (*_cell.rightNeighbour() ).temperature();
    double tTemp = (*_cell.topNeighbour()   ).temperature();
    double bTemp = (*_cell.bottomNeighbour()).temperature();

    double koeff = (lTemp + rTemp - curTemp - curTemp) / ModelConstants::dx +
                   (tTemp + bTemp - curTemp - curTemp) / ModelConstants::dy;

    koeff *= sqrA * ModelConstants::dt;
    return koeff;
}






