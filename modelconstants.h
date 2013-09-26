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
    static const double absNull;// = -273.15;

    type m_type;
    double c;          // удельная теплоемкость,  Дж / (К * кг)
    double cMelt;      // теплоемкость плавления, Дж / кг
    double lambda;     // теплопроводность,       Вт / (м * К)
    double r;          // плотность

private:
    static QHash<type, ModelConstants* > m_constants;
};

inline double toKelvin(double _temp)
{
    return _temp - ModelConstants::absNull;
}

inline double toCelsius(double _temp)
{
    return _temp + ModelConstants::absNull;
}

#endif // MODELCONSTANTS_H
