#ifndef DISPLAYMELTMODEL_H
#define DISPLAYMELTMODEL_H

#include <QMainWindow>

namespace Ui
{
    class displaymeltmodel;
}

class MeltModel;
class MeltDelegate;
class GraphicsWidget;
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
    void graphicsClosed();

    void autoRepeatOn();
    void autoRepeatOff();

    void writeConfigFile();
    void readConfigFile();

    void updateMinTemp(double _newTemp);
    void updateMaxTemp(double _newTemp);

private:
    void initConstants();
    void startNewModel(int _width, int _height, double _startTemperature);
    void setupModel();

private:

    double m_modelTime;
    bool m_autoRepeat;
    GraphicsWidget* m_graphics;
    Ui::displaymeltmodel *ui;
    MeltModel* m_meltmodel;
    MeltDelegate* m_delegate;

};

#endif // DISPLAYMELTMODEL_H
