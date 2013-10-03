#ifndef MODELCONSTANTS_H
#define MODELCONSTANTS_H

#include <QHash>
#include "modelapi.h"

namespace model
{

class ModelConstants
{
public:
    static ModelConstants* getConstants(Type _t);
    static void setEnvironmentConstants(Type _t, double _c, double _lambda, double _r);

private:
    ModelConstants(Type _t, double _c, double _lambda, double _r);

public:
    static double dx;
    static double dy;
    static double dt;

    Type m_type;
    double c;          // �������� ������������,  �� / (� * ��)
    double cMelt;      // ������������ ���������, �� / ��
    double lambda;     // ����������������,       �� / (� * �)
    double r;          // ���������

private:
    static QHash<Type, ModelConstants* > m_constants;
};
}

#endif // MODELCONSTANTS_H
