#ifndef MELTLOGICS_H
#define MELTLOGICS_H

#include <QObject>
#include "field.h"

class MeltLogics : public QObject
{
    Q_OBJECT
public:
    MeltLogics(QObject* _parent = NULL);
    MeltLogics(Field* _startFrame, QObject *_parent = NULL);
    ~MeltLogics();

    bool   saveStep(const QString& _filename);
    Field* loadStep(const QString& _filename);

    Field*  currentFrame();

    int realWidth();
    int realHeight();

public slots:
    Field* nextFrame();

    void updateBehaviour();

private:
    void swapFrames();
    inline void heat(Field* _field);
    inline double calculateKoeff(Field::iterator& _cell);

private:
    Field* m_current;
    Field* m_prev;

};

#endif // MELTLOGICS_H
