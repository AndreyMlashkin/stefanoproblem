#include <QDebug>
#include <QMouseEvent>
#include <QToolTip>

#include "graphicswidget.h"
#include "ui_graphics.h"
#include "meltmodel.h"
#include "deltavolume.h"

#include "qwt_plot.h"
#include "qwt_plot_curve.h"

int inline min(int a, int b)
{
    return (a < b)? a : b;
}

GraphicsWidget::GraphicsWidget(QWidget *parent) :
    QWidget(parent, Qt::Window),
    m_ui(new Ui::Graphics()),
    m_model(NULL),
    m_plot(new QwtPlot),
    m_curve(new QwtPlotCurve(QString("Temperature")))
{
    m_ui->setupUi(this);

    QHeaderView* header = m_ui->graphics->horizontalHeader();
    header->hide();

    header =  m_ui->graphics->verticalHeader();
    header->hide();

    connect(m_ui->chartOrientation, SIGNAL(currentIndexChanged(int)), this, SLOT(chartOrientationChanged()));
    connect(m_ui->makeChart, SIGNAL(clicked()), this, SLOT(makeChart()));

    m_ui->additionalAxis->hide();
}

GraphicsWidget::~GraphicsWidget()
{
    delete m_ui;
    delete m_model;
    delete m_plot;
    delete m_curve;
}

void GraphicsWidget::setModel(QAbstractItemModel *_model)
{
    m_model = static_cast<MeltModel*>(_model);
    m_ui->graphics->setModel(_model);
    chartOrientationChanged();
    m_ui->graphics->resizeEvent(NULL);
}

void GraphicsWidget::setDelegate(QAbstractItemDelegate *_delegate)
{
    m_ui->graphics->setItemDelegate(_delegate);
}

void GraphicsWidget::closeEvent(QCloseEvent *)
{
    emit closing();
}

void GraphicsWidget::makeChart()
{  
    m_curve->setRenderHint(QwtPlotItem::RenderAntialiased);
    m_curve->setPen(QPen(Qt::red));

    switch(orientation())
    {
        case vertical:
        {
        double* y = new double[m_model->columnCount()];
        double* x = new double[m_model->columnCount()];

        for(int i = 0; i < m_model->columnCount(); i++)
        {
            int column = m_ui->axis->value();

            void* data = m_model->index(i, column).internalPointer();
            DeltaVolume* d = static_cast<DeltaVolume*>(data);

            double temp = d->temperature();

            y[i] = temp;
            x[i] = i;
        }

        m_curve->setSamples(x, y, m_model->columnCount());
        m_curve->attach(m_plot);
        break;
        }
    }
    m_plot->replot();
    m_plot->show();
}

void GraphicsWidget::chartOrientationChanged()
{
    chartOrientation orient = orientation();

    m_ui->additionalAxis->hide();
    switch(orient)
    {
    case time:
    {
        m_ui->additionalAxis->show();
        m_ui->axis->setMaximum(m_model->columnCount());
        m_ui->additionalAxis->setMaximum(m_model->rowCount());
        break;
    }
    case horizontal:
        m_ui->axis->setMaximum(m_model->columnCount()); break;
    case vertical:
        m_ui->axis->setMaximum(m_model->rowCount());    break;

    }
}

GraphicsWidget::chartOrientation GraphicsWidget::orientation()
{
    return (GraphicsWidget::chartOrientation)m_ui->chartOrientation->currentIndex();
}
