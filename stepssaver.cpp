#include <QDataStream>
#include <QDebug>

#include "stepssaver.h"
#include "modelfield.h"
#include "deltavolume.h"

namespace model
{

StepsSaver::StepsSaver(const QString& _name)
    : m_file(_name)
{
    m_file.open(QIODevice::Append | QIODevice::Truncate);
}

StepsSaver::~StepsSaver()
{
    m_file.close();
}

void StepsSaver::saveStep(ModelField* _field)
{
    QDataStream out(&m_file);
    ModelField::iterator i = _field->begin();
    while(i != _field->end())
    {
        out << i->temperature();
        ++i;
    }
}

}
