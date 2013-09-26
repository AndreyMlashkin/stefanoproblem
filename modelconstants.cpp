#include "modelconstants.h"

QHash<type, ModelConstants* > ModelConstants::m_constants;
double ModelConstants::dx;
double ModelConstants::dy;
double ModelConstants::dt;
const double ModelConstants::absNull(-273.15);
//const double ModelConstants::absNull;

ModelConstants::ModelConstants(type _t, double _c, double _lambda, double _r)
    : m_type(_t),
      c(_c),
      lambda(_lambda),
      r(_r)
{}

ModelConstants* ModelConstants::getConstants(type _t)
{
    return m_constants[_t];
}

void ModelConstants::setEnvironmentConstants(type _t, double _c, double _lambda, double _r)
{
    m_constants[_t] = new ModelConstants(_t, _c, _lambda, _r);
}

