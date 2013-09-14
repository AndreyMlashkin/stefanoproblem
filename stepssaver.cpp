#include <QDataStream>
#include <QDebug>

#include "stepssaver.h"
#include "field.h"
#include "deltavolume.h"

StepsSaver::StepsSaver(const QString &_name)
    : m_file(_name)
{
    m_file.open(QIODevice::Append | QIODevice::Truncate);
}

StepsSaver::~StepsSaver()
{
    m_file.close();
}

void StepsSaver::saveStep(Field* _field)
{
    QDataStream out(&m_file);
    Field::iterator i = _field->begin();
    while(i != _field->end())
    {
        out << i->temperature();
        i++;
    }
}
