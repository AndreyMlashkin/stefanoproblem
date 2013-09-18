#include <QDebug>
#include <QMouseEvent>
#include <QToolTip>

#include "qwt_plot_curve.h"
#include "graphicswidget.h"
#include "ui_graphics.h"
#include "meltmodel.h"
#include "deltavolume.h"

int inline min(int a, int b)
{
    return (a < b)? a : b;
}

GraphicsWidget::GraphicsWidget(QWidget *parent) :
    QWidget(parent, Qt::Window),
    m_ui(new Ui::Graphics()),
    m_model(NULL),
    m_curve(new QwtPlotCurve(QString("Temperature"))),
    m_plotter(new Plotter(m_curve))
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
    delete m_plotter;
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

    size_t size;
    switch(orientation())
    {
        case Plotter::horizontal:
        {
            size = m_model->columnCount();
            double* y = new double[size];
            double* x = new double[size];
            int row = m_ui->axis->value();

            for(int i = 0; i < size; i++)
            {
                void* data = m_model->index(row, i).internalPointer();
                DeltaVolume* d = static_cast<DeltaVolume*>(data);

                double temp = d->temperature();

                y[i] = temp;
                x[i] = i;
            }
            m_curve->setSamples(x, y, size);
            break;
        }
        case Plotter::vertical:
        {
            size = m_model->rowCount();

            double* y = new double[size];
            double* x = new double[size];
            int column = m_ui->axis->value();

            for(int i = 0; i < size; i++)
            {
                void* data = m_model->index(i, column).internalPointer();
                DeltaVolume* d = static_cast<DeltaVolume*>(data);

                double temp = d->temperature();

                y[i] = temp;
                x[i] = i;
            }
            m_curve->setSamples(x, y, size);
            break;
        }
    }
    m_plotter->replot();
    m_plotter->show();
}

void GraphicsWidget::chartOrientationChanged()
{
    Plotter::chartOrientation orient = orientation();

    m_ui->additionalAxis->hide();
    switch(orient)
    {
    case Plotter::time:
    {
        m_ui->additionalAxis->show();
        m_ui->axis->setMaximum(m_model->columnCount());
        m_ui->additionalAxis->setMaximum(m_model->rowCount());
        break;
    }
    case Plotter::horizontal:
        m_ui->axis->setMaximum(m_model->columnCount()); break;
    case Plotter::vertical:
        m_ui->axis->setMaximum(m_model->rowCount());    break;

    }
}

Plotter::chartOrientation GraphicsWidget::orientation()
{
    return (Plotter::chartOrientation)m_ui->chartOrientation->currentIndex();
}
