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
    explicit GraphicsWidget();
    ~GraphicsWidget();

    void setModel(QAbstractItemModel* _model);
    void setDelegate(QAbstractItemDelegate* _delegate);
    void closeEvent(QCloseEvent *);

public slots:
    void makeChart();
    void chartOrientationChanged();

    void sliceMoved();

signals:
    void closing();
    void highlinghtRow(int);
    void highlinghtColumn(int);

private slots:
    void setInfoState();
    void setDrillState();
    void setIceState();
    void setLoupState();

private:
    Plotter::chartOrientation orientation();
    inline void resetState();

private:
    Ui::Graphics* m_ui;
    MeltModel* m_model;

    QwtPlotCurve* m_curve;
    Plotter* m_plotter;
};

#endif // GRAPHICSWIDGET_H
