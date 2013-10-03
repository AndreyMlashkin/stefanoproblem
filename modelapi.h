#ifndef MODELAPI_H
#define MODELAPI_H

namespace model
{
#define ABSNULL -273.15
//double absNull = -273.15;

enum Type {NoType, Ice, Water, Drill, TYPE_COUNT};

inline double toKelvin(double _temp)
{
    return _temp - ABSNULL;
}

inline double toCelsius(double _temp)
{
    return _temp + ABSNULL;
}

}
#endif // MODELAPI_H
