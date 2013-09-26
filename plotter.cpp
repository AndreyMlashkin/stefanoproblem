#include <QDebug>

//#include "qwt_plot_curve.h"

#include "plotter.h"
//#include "ui_plotter.h"

#include "modelfield.h"

Plotter::Plotter(QwtPlotCurve *_curve, QWidget *parent) :
    QWidget(parent)/*,
    m_ui(new Ui::Plotter())*/
{
 //   m_ui->setupUi(this);
   // _curve->attach(m_ui->plotter);
}

void Plotter::replot()
{
  //  m_ui->plotter->replot();
}

void Plotter::closeEvent(QCloseEvent*)
{
    emit closing();
    hide();
}

