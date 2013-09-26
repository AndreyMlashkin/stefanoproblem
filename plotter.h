#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>

class QCustomPlot;

namespace Ui
{
    class Plotter;
}

class ModelField;


class Plotter : public QWidget
{
    Q_OBJECT
public:
    enum chartOrientation {horizontal, vertical, time};

    explicit Plotter(QWidget *parent = 0);
    void replot();

signals:
    void closing();

private:
    void closeEvent(QCloseEvent*);

private:
   // Ui::Plotter* m_ui;
    QCustomPlot* m_plotter;
};

#endif // PLOTTER_H
