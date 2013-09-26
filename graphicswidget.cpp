#include <QDebug>
#include <QMouseEvent>
#include <QToolTip>
#include <QVector>

#include "qcustomplot/qcustomplot.h"

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
    m_chart(new QCustomPlot())
{
    m_ui->setupUi(this);
    initChart();

    QHeaderView* header = m_ui->graphics->horizontalHeader();
    header->hide();

    header =  m_ui->graphics->verticalHeader();
    header->hide();

    connect(m_ui->chartOrientation, SIGNAL(currentIndexChanged(int)),SLOT(chartOrientationChanged()));
    connect(m_ui->makeChart,        SIGNAL(clicked()),               SLOT(updatePlotterVisibility()));
    connect(m_ui->axis,             SIGNAL(valueChanged(int)),       SLOT(sliceMoved()));

    //connect(m_plotter, SIGNAL(closing()), m_ui->makeChart, SLOT(click()));

    m_ui->additionalAxis->hide();

    connect(m_ui->info,  SIGNAL(pressed()), SLOT(updateState()));
    connect(m_ui->drill, SIGNAL(pressed()), SLOT(updateState()));
    connect(m_ui->ice,   SIGNAL(pressed()), SLOT(updateState()));
    connect(m_ui->loupe, SIGNAL(pressed()), SLOT(updateState()));

    connect(m_ui->onePix,   SIGNAL(pressed()), SLOT(updateBrush()));
    connect(m_ui->twoPix,   SIGNAL(pressed()), SLOT(updateBrush()));
    connect(m_ui->threePix, SIGNAL(pressed()), SLOT(updateBrush()));
}

GraphicsWidget::~GraphicsWidget()
{
    delete m_ui;
    delete m_chart;
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
        m_chart->show();
    }
    else
    {
        static const QString s(tr("Построить график"));
        m_ui->makeChart->setText(s);
        m_chart->hide();
    }
}

void GraphicsWidget::updatePlotter()
{  
    if(!m_model)
        return;

    //m_curve->setRenderHint(QwtPlotItem::RenderAntialiased);
   // m_curve->setPen(QPen(Qt::red));

    QVector<double> x, y;
    size_t size;

    switch(orientation())
    {
        case Plotter::horizontal:
        {
            size = m_model->columnCount();
            x.reserve(size);
            y.reserve(size);
            int row = m_ui->axis->value();

            for(size_t i = 0; i < size; i++)
            {
                void* data = m_model->index(row, i).internalPointer();
                DeltaVolume* d = static_cast<DeltaVolume*>(data);

                double temp = d->temperature();
                y.push_back(temp);
                x.push_back(i);
            }
            break;
        }
        case Plotter::vertical:
        {
            size = m_model->rowCount();
            x.reserve(size);
            y.reserve(size);

            int column = m_ui->axis->value();

            for(size_t i = 0; i < size; i++)
            {
                void* data = m_model->index(i, column).internalPointer();
                DeltaVolume* d = static_cast<DeltaVolume*>(data);

                double temp = d->temperature();
                y.push_back(temp);
                x.push_back(i);

            }
            break;
        }
    }

    if(!m_chart->graph())
        m_chart->addGraph();

    QPen graphPen;
    graphPen.setColor(Qt::black);
    graphPen.setWidthF(5);
    m_chart->graph()->setPen(graphPen);

    m_chart->graph()->setData(x, y);

 //   m_chart->replot();
    //m_curve->setSamples(x, y, size);
    //m_plotter->replot();
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

void GraphicsWidget::initChart()
{
    m_chart->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);
    m_chart->xAxis->setRange(0, 50);
    m_chart->yAxis->setRange(0, -250);
    m_chart->axisRect()->setupFullAxesBox();

    m_chart->plotLayout()->insertRow(0);
    m_chart->plotLayout()->addElement(0, 0, new QCPPlotTitle(m_chart, "������������� �����������"));

//    m_chart->xAxis->setLabel("����������");
//    m_chart->yAxis->setLabel("�����������");
    m_chart->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
}

void GraphicsWidget::updateState()
{
    m_ui->info->setChecked(false);
    m_ui->drill->setChecked(false);
    m_ui->ice->setChecked(false);
    m_ui->loupe->setChecked(false);

    if     (sender() == m_ui->info)
        m_ui->graphics->setMouseState(INFO);
    else if(sender() == m_ui->drill)
        m_ui->graphics->setMouseState(DRILL);
    else if(sender() == m_ui->ice)
        m_ui->graphics->setMouseState(ICE);
    else if(sender() == m_ui->loupe)
        m_ui->graphics->setMouseState(LOUPE);
}

void GraphicsWidget::updateBrush()
{
    m_ui->onePix->setChecked(false);
    m_ui->twoPix->setChecked(false);
    m_ui->threePix->setChecked(false);

    if     (sender() == m_ui->onePix)
        m_ui->graphics->setBrushType(ONEPIX);
    else if(sender() == m_ui->twoPix)
        m_ui->graphics->setBrushType(TWOPIX);
    else if(sender() == m_ui->threePix)
        m_ui->graphics->setBrushType(THREEPIX);
}
