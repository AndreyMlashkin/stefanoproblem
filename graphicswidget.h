#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <QWidget>
#include "plotter.h"

namespace Ui
{
    class Graphics;
}

class QAbstractItemDelegate;
class QAbstractItemModel;
class QwtPlotCurve;
class MeltModel;

class GraphicsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GraphicsWidget(QWidget *parent = 0);
    ~GraphicsWidget();

    void setModel(QAbstractItemModel* _model);
    void setDelegate(QAbstractItemDelegate* _delegate);
    void closeEvent(QCloseEvent *);

public slots:
    void makeChart();
    void chartOrientationChanged();

signals:
    void closing();

private:
    Plotter::chartOrientation orientation();

private:
    Ui::Graphics* m_ui;
    MeltModel* m_model;

    QwtPlotCurve* m_curve;
    Plotter* m_plotter;
};

#endif // GRAPHICSWIDGET_H
