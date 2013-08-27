#ifndef DISPLAYMELTMODEL_H
#define DISPLAYMELTMODEL_H

#include <QMainWindow>

namespace Ui
{
    class displaymeltmodel;
}

class MeltModel;
class MeltDelegate;
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
    void updateViewsVisibility();

    void writeConfigFile();
    void readConfigFile();

    void updateMinTemp(double _newTemp);
    void updateMaxTemp(double _newTemp);

private:
    void startNewModel(int _width, int _height, double _startTemperature);
    void setupModel();

    void resizeEvent(QResizeEvent* _event);

private:
    Ui::displaymeltmodel *ui;
    MeltModel* m_meltmodel;
    MeltDelegate* m_delegate;
};

#endif // DISPLAYMELTMODEL_H
