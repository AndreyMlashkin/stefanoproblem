#ifndef MODELCONSTANTS_H
#define MODELCONSTANTS_H

#include <QHash>

enum type {ICE, WATER, TYPE_COUNT};

class ModelConstants
{
public:
    static ModelConstants* getConstants(type _t);
    static void setEnvironmentConstants(type _t, double _c, double _lambda, double _r);

private:
    ModelConstants(type _t, double _c, double _lambda, double _r);

public:
    static double dx;
    static double dy;
    static double dt;
    static double absNull;

    type m_type;
    double c;          // �������� ������������,  �� / (� * ��)
    double cMelt;      // ������������ ���������, �� / ��
    double lambda;     // ����������������,       �� / (� * �)
    double r;          // ���������

private:
    static QHash<type, ModelConstants* > m_constants;
};

#endif // MODELCONSTANTS_H
