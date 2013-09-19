#include <QDebug>
#include <QMouseEvent>
#include <QToolTip>
#include <QHeaderView>

#include "meltview.h"
#include "deltavolume.h"
#include "meltmodel.h"

inline int min(int a, int b)
{
    return (a < b)? a : b;
}

MeltView::MeltView(QWidget* _parent) :
    QTableView(_parent),
    m_state(NOSTATE)
{
}

void MeltView::mousePressEvent(QMouseEvent *_e)
{
    const DeltaVolume* v = volumeFromPos(_e->pos());
    if(!v)
        return;

    if(m_state == NOSTATE)
        QToolTip::showText(_e->globalPos(), QString::number(v->temperature(), 'f'));
    else
        mouseMoveEvent(_e);

}

void MeltView::resizeEvent(QResizeEvent*)
{
    if(!model())
        return;

    int cellWidth  = height() / model()->rowCount();
    int cellHeight = width()  / model()->columnCount();

    int cellSize = min(cellWidth, cellHeight);

    if(cellSize < 1)
        cellSize = 1;

    QHeaderView* header = horizontalHeader();
    header->setDefaultSectionSize(cellSize);

    header =  verticalHeader();
    header->setDefaultSectionSize(cellSize);
}

void MeltView::setMouseState(MouseState _state)
{
    m_state = _state;
}

void MeltView::wheelEvent(QWheelEvent* _ev)
{
    qDebug() << _ev->delta();
}

DeltaVolume *MeltView::volumeFromPos(const QPoint& _p)
{
    QModelIndex index = indexAt(_p);
    if(!index.isValid())
        return NULL;

    return reinterpret_cast<DeltaVolume*>(index.internalPointer());
}

void MeltView::mouseMoveEvent(QMouseEvent *_e)
{
    DeltaVolume* v = volumeFromPos(_e->pos());
    if(!v)
        return;

    if(v->behaviour() == Border)
        return;

    if(m_state == DRILL)
        v->setType(DeltaVolume::Drill);
    else if(m_state == ICE)
        v->setType(DeltaVolume::Ice);

    MeltModel* mod = static_cast<MeltModel*>(model());
    mod->updateBehaviour();

    reset();
}
