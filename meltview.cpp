#include "meltview.h"

#include <QGraphicsView>
#include <QGraphicsScene>

MeltView::MeltView(QWidget *_parent)
    : QWidget(_parent)
{
    m_gScene = new QGraphicsScene(_parent);
    m_gView = new QGraphicsView(m_gScene);
    m_gView->show();

    m_gScene->setBackgroundBrush(Qt::red);

    QLinearGradient gradient(0, 0, 100, 100);
    //gradient.setSpread(QGradient::RepeatSpread);
    m_gScene->setBackgroundBrush(gradient);
    show();
}
