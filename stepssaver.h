#ifndef STEPSSAVER_H
#define STEPSSAVER_H

#include <QFile>
#include <QString>

class ModelField;
class StepsSaver
{
public:
    StepsSaver(const QString& _name);
    ~StepsSaver();

    void saveStep(ModelField* _field);

private:
    QFile m_file;
};

#endif // STEPSSAVER_H
