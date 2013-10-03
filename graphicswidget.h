#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <QWidget>
#include "plotter.h"

namespace Ui
{
    class Graphics;
}
class QCustomPlot;
class QAbstractItemDelegate;
class QAbstractItemModel;

namespace model
{
class MeltModel;

class GraphicsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GraphicsWidget();
    ~GraphicsWidget();

    void setModel(QAbstractItemModel* _model);
    void setDelegate(QAbstractItemDelegate* _delegate);
    void closeEvent(QCloseEvent *);

public slots:
    void updatePlotterVisibility();
    void updatePlotter();
    void chartOrientationChanged();
    void sliceMoved();

    void modelStep();

signals:
    void closing();
    void highlinghtRow(int);
    void highlinghtColumn(int);

private slots:
    void updateState();
    void updateBrush();

private:
    Plotter::chartOrientation orientation();
    inline void initChart();
    //inline void fillByValues(QVector<double> &x, QVector<double> &y, Qt::Orientation _orient, double& max, double& min);

private:
    Ui::Graphics* m_ui;
    MeltModel* m_model;

    QCustomPlot* m_chart;
};
}

#endif // GRAPHICSWIDGET_H
