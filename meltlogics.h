#ifndef MELTLOGICS_H
#define MELTLOGICS_H

#include "modelfield.h"

namespace model
{

class MeltLogics
{
public:
    MeltLogics();
    MeltLogics(ModelField* _startFrame);
    MeltLogics(const MeltLogics& _logics);

    ~MeltLogics();

    bool   saveStep(const QString& _filename) const;
    ModelField* loadStep(const QString& _filename);

    ModelField* currentFrame() const;

    int realWidth() const;
    int realHeight() const;

    ModelField* nextFrame();
    void updateBehaviour();

private:
    void swapFrames();
    inline void heat(ModelField* _field);
    inline double calculateKoeff(ModelField::iterator& _cell);

private:
    ModelField* m_current;
    ModelField* m_prev;
};
}

#endif // MELTLOGICS_H
