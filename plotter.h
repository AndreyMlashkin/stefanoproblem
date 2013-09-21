#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>

namespace Ui
{
    class Plotter;
}

class QwtPlotCurve;
class ModelField;


class Plotter : public QWidget
{
    Q_OBJECT
public:
    enum chartOrientation {horizontal, vertical, time};

    explicit Plotter(QwtPlotCurve* _curve, QWidget *parent = 0);
    void replot();

signals:
    void closing();

private:
    void closeEvent(QCloseEvent*);

private:
    Ui::Plotter* m_ui;
};

#endif // PLOTTER_H
