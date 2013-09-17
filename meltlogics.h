#ifndef MELTLOGICS_H
#define MELTLOGICS_H

#include <QObject>
#include "modelfield.h"

class MeltLogics : public QObject
{
    Q_OBJECT
public:
    MeltLogics(QObject* _parent = NULL);
    MeltLogics(ModelField* _startFrame, QObject *_parent = NULL);
    ~MeltLogics();

    bool   saveStep(const QString& _filename);
    ModelField* loadStep(const QString& _filename);

    ModelField*  currentFrame();

    int realWidth();
    int realHeight();

public slots:
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

#endif // MELTLOGICS_H
