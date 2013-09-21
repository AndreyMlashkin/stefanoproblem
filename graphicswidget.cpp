#include <QDebug>
#include <QMouseEvent>
#include <QToolTip>

#include "qwt_plot_curve.h"
#include "graphicswidget.h"
#include "ui_graphics.h"

#include "meltmodel.h"
#include "meltdelegate.h"
#include "deltavolume.h"

int inline min(int a, int b)
{
    return (a < b)? a : b;
}

GraphicsWidget::GraphicsWidget() :
    QWidget(),
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

    connect(m_ui->chartOrientation, SIGNAL(currentIndexChanged(int)),SLOT(chartOrientationChanged()));
    connect(m_ui->makeChart,        SIGNAL(clicked()),               SLOT(updatePlotterVisibility()));
    connect(m_ui->axis,             SIGNAL(valueChanged(int)),       SLOT(sliceMoved()));

    connect(m_ui->info,  SIGNAL(pressed()), SLOT(setInfoState()));
    connect(m_ui->drill, SIGNAL(pressed()), SLOT(setDrillState()));
    connect(m_ui->ice,   SIGNAL(pressed()), SLOT(setIceState()));
    connect(m_ui->loupe, SIGNAL(pressed()), SLOT(setLoupState()));

    connect(m_plotter, SIGNAL(closing()), m_ui->makeChart, SLOT(click()));

    m_ui->additionalAxis->hide();
}

GraphicsWidget::~GraphicsWidget()
{
    delete m_ui;
    delete m_plotter;
}

void GraphicsWidget::setModel(QAbstractItemModel *_model)
{
    m_model = static_cast<MeltModel*>(_model);
    m_ui->graphics->setModel(_model);
    chartOrientationChanged();
    m_ui->graphics->resizeEvent(NULL);
}

void GraphicsWidget::setDelegate(QAbstractItemDelegate* _delegate)
{
    connect(this, SIGNAL(highlinghtColumn(int)), static_cast<MeltDelegate*>(_delegate), SLOT(highlightColumn(int)));
    connect(this, SIGNAL(highlinghtRow(int)),    static_cast<MeltDelegate*>(_delegate), SLOT(highlightRow(int)));

    m_ui->graphics->setItemDelegate(_delegate);
}

void GraphicsWidget::closeEvent(QCloseEvent *)
{
    m_ui->makeChart->setChecked(false);
    updatePlotterVisibility();

    emit closing();
}

void GraphicsWidget::updatePlotterVisibility()
{
    if(m_ui->makeChart->isChecked())
    {
        updatePlotter();
        static const QString s(tr("Спрятать график"));
        m_ui->makeChart->setText(s);
        m_plotter->show();
    }
    else
    {
        static const QString s(tr("Построить график"));
        m_ui->makeChart->setText(s);
        m_plotter->hide();
    }
}

void GraphicsWidget::updatePlotter()
{  
    if(!m_model)
        return;

    m_curve->setRenderHint(QwtPlotItem::RenderAntialiased);
    m_curve->setPen(QPen(Qt::red));

    size_t size;
    double* y;
    double* x;
    switch(orientation())
    {
        case Plotter::horizontal:
        {
            size = m_model->columnCount();
            y = new double[size];
            x = new double[size];
            int row = m_ui->axis->value();

            for(size_t i = 0; i < size; i++)
            {
                void* data = m_model->index(row, i).internalPointer();
                DeltaVolume* d = static_cast<DeltaVolume*>(data);

                double temp = d->temperature();

                y[i] = temp;
                x[i] = i;
            }
            break;
        }
        case Plotter::vertical:
        {
            size = m_model->rowCount();

            y = new double[size];
            x = new double[size];
            int column = m_ui->axis->value();

            for(size_t i = 0; i < size; i++)
            {
                void* data = m_model->index(i, column).internalPointer();
                DeltaVolume* d = static_cast<DeltaVolume*>(data);

                double temp = d->temperature();

                y[i] = temp;
                x[i] = i;
            }
            break;
        }
    }
    m_curve->setSamples(x, y, size);
    m_plotter->replot();
    delete[] x;
    delete[] y;
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
        m_ui->axis->setMaximum(m_model->columnCount()-1);
        m_ui->additionalAxis->setMaximum(m_model->rowCount()-1);
        break;
    }
    case Plotter::horizontal:
        m_ui->axis->setMaximum(m_model->rowCount()-1);    break;
    case Plotter::vertical:
        m_ui->axis->setMaximum(m_model->columnCount()-1); break;
    }
    sliceMoved();
}

void GraphicsWidget::sliceMoved()
{
    if(orientation() == Plotter::horizontal)
        emit highlinghtRow(m_ui->axis->value());

    else if(orientation() == Plotter::vertical)
        emit highlinghtColumn(m_ui->axis->value());

    m_ui->graphics->reset();
    updatePlotter();
}

void GraphicsWidget::modelStep()
{
    if(m_ui->makeChart->isChecked())
        updatePlotter();
}

Plotter::chartOrientation GraphicsWidget::orientation()
{
    return (Plotter::chartOrientation)m_ui->chartOrientation->currentIndex();
}

void GraphicsWidget::resetState()
{
    m_ui->info->setChecked(false);
    m_ui->drill->setChecked(false);
    m_ui->ice->setChecked(false);
    m_ui->loupe->setChecked(false);
}

void GraphicsWidget::setInfoState()
{
    resetState();
    m_ui->graphics->setMouseState(INFO);
}


void GraphicsWidget::setDrillState()
{
    resetState();
    m_ui->graphics->setMouseState(DRILL);
}

void GraphicsWidget::setIceState()
{
    resetState();
    m_ui->graphics->setMouseState(ICE);
}

void GraphicsWidget::setLoupState()
{
    resetState();
    m_ui->graphics->setMouseState(LOUPE);
}
