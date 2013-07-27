#ifndef MELTLOGICS_H
#define MELTLOGICS_H

#include <QObject>
#include "field.h"

class MeltLogics : public QObject
{
    Q_OBJECT
public:
    MeltLogics(Field* _startFrame, QObject *parent = 0);
    ~MeltLogics();
    void saveStep();
    void loadStep();

public slots:
    Field* nextFrame();

private:
    void swapFrames();

private:
    Field* m_current;
    Field* m_prev;

};

#endif // MELTLOGICS_H
