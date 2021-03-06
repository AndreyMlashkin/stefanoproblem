#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "meltlogics.h"
#include "deltavolume.h"
#include "modelconstants.h"

namespace model
{

inline double my_abs(double a)
{
    return (a > 0)? a : -a;
}

MeltLogics::MeltLogics()
    : m_current(NULL),
      m_prev(NULL)
{}

MeltLogics::MeltLogics(ModelField* _startFrame)
  : m_current(_startFrame),
    m_prev(new ModelField(*_startFrame))
{}

MeltLogics::MeltLogics(const MeltLogics& _logics)
    : m_current(_logics.currentFrame()),
      m_prev(_logics.m_prev)
{
    m_prev = new ModelField(*m_prev);
}

MeltLogics::~MeltLogics()
{
    delete m_prev;
}

bool MeltLogics::saveStep(const QString& _filename = "save.txt") const
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
                out << (*m_current)[i][j].temperature() << '\t';
            out << '\n';
        }
        file.close();
        return true;
    }
    else
        return false;
}

ModelField* MeltLogics::loadStep(const QString &_filename)
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

        m_current = new ModelField(width, height);
        m_prev    = new ModelField(width, height);

        for(ModelField::iterator i = m_current->begin(); i != m_current->end(); ++i)
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

ModelField* MeltLogics::currentFrame() const
{
    return m_current;
}

int MeltLogics::realWidth() const
{
    return (*m_current).width() * 2;
}

int MeltLogics::realHeight() const
{
    return (*m_current).height();
}

ModelField *MeltLogics::nextFrame()
{
    swapFrames();
    heat(m_prev);

    ModelField::iterator oldCell = m_prev->begin();
    ModelField::iterator newCell = m_current->begin();

    int i = 0;

    ModelField::iterator end = m_prev->end();
    while(oldCell != end)
    {
        if(((*oldCell).behaviour() != Border) && ((*oldCell).type() != Drill))
        {
            double koeff = calculateKoeff(oldCell);
            double oldTemp = (*oldCell).temperature();

//            ModelConstants* constants = ModelConstants::getConstants(Ice);
//           (*newCell).setTemperature(oldTemp + koeff / constants->c);
            (*newCell).setTemperature(oldTemp);
            (*newCell).setEnergy(koeff);
        }
        ++newCell;
        ++oldCell;
        i++;
    }
    return m_current;
}

void MeltLogics::updateBehaviour()
{
    ModelField::iterator i = m_prev->begin();
    ModelField::iterator j = m_current->begin();
    ModelField::iterator end = m_prev->end();

    for(; i != end; ++i, ++j)
        (*i).setType((*j).type());
}

void MeltLogics::swapFrames()
{
    ModelField* tmp = m_prev;
    m_prev = m_current;
    m_current = tmp;
}

void MeltLogics::heat(ModelField* _field)
{
    ModelField::iterator end = _field->end();
    for(ModelField::iterator i = _field->begin(); i != end; ++i)
    {
        if(i->type() == Drill)
        {
//            double temperature = (*i).temperature();
            (*i).setTemperature(toKelvin(0)/*temperature + heating*/);
        }
    }
}

double inline tempDiffusion()
{
    ModelConstants* constants = ModelConstants::getConstants(Ice);

    return constants->lambda / constants->r;
}

double MeltLogics::calculateKoeff(ModelField::iterator& _cell)
{
//    const static double sqrA = /*tempDiffusion() **/ tempDiffusion();
    double curTemp = _cell->temperature();

    double lTemp;
    if(_cell->behaviour() == Central)
           lTemp = curTemp;
    else
           lTemp = _cell.left()  ->temperature();

    double rTemp = _cell.right() ->temperature();
    double tTemp = _cell.top()   ->temperature();
    double bTemp = _cell.bottom()->temperature();

    double koeff = (lTemp + rTemp - curTemp - curTemp) / (ModelConstants::dx * ModelConstants::dx)+
                   (tTemp + bTemp - curTemp - curTemp) / (ModelConstants::dy * ModelConstants::dy);

    koeff *= tempDiffusion() * ModelConstants::dt;
    return koeff;
}

}
