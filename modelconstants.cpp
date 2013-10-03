#include "modelconstants.h"

namespace model
{

QHash<Type, ModelConstants* > ModelConstants::m_constants;
double ModelConstants::dx;
double ModelConstants::dy;
double ModelConstants::dt;

ModelConstants::ModelConstants(Type _t, double _c, double _lambda, double _r)
    : m_type(_t),
      c(_c),
      lambda(_lambda),
      r(_r)
{}

ModelConstants* ModelConstants::getConstants(Type _t)
{
    return m_constants[_t];
}

void ModelConstants::setEnvironmentConstants(Type _t, double _c, double _lambda, double _r)
{
    m_constants[_t] = new ModelConstants(_t, _c, _lambda, _r);
}

}
