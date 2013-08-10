#ifndef DISPLAYMELTMODEL_H
#define DISPLAYMELTMODEL_H

#include <QMainWindow>


namespace Ui
{
    class displaymeltmodel;
}

class MeltModel;
class DisplayMeltmodel : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit DisplayMeltmodel(QWidget *parent = 0);
    ~DisplayMeltmodel();
private slots:
    void initModel();
    void step();
    void callSaveDialog();
    void callOpenDialog();
private:
    void startNewModel(int _width, int _height, double _startTemperature);
    void setupModel();

private:
    Ui::displaymeltmodel *ui;
    MeltModel* m_meltmodel;
};

#endif // DISPLAYMELTMODEL_H
