#include <QDebug>
#include <QMouseEvent>
#include <QToolTip>
#include <QHeaderView>
#include <QScrollBar>

#include "meltview.h"
#include "deltavolume.h"
#include "meltmodel.h"

namespace model
{

inline int min(int a, int b)
{
    return (a < b)? a : b;
}

MeltView::MeltView(QWidget* _parent) :
    QTableView(_parent),
    m_brush(ONEPIX),
    m_state(NOSTATE),
    m_minCellSize(1),
    m_zoom(1)
{
    resizeEvent(NULL);
}

void MeltView::mousePressEvent(QMouseEvent *_e)
{
    QModelIndex index = indexAt(_e->pos());
    if(!index.isValid())
        return;

    if(m_state == INFO)
        QToolTip::showText(_e->globalPos(), index.data().toString());
    else
        mouseMoveEvent(_e);

}

void MeltView::resizeEvent(QResizeEvent*)
{
    if(!model())
        return;

    int cellWidth  = height() / model()->rowCount();
    int cellHeight = width()  / model()->columnCount();

    m_minCellSize = min(cellWidth, cellHeight);

    if(m_minCellSize < 1)
        m_minCellSize = 1;

    cellSizeUpdated();
}

void MeltView::setMouseState(MouseState _state)
{
    m_state = _state;
}

void MeltView::setBrushType(BrushType _brush)
{
    m_brush = _brush;
}

void MeltView::wheelEvent(QWheelEvent* _ev)
{
    bool sign = (_ev->delta() > 0) ? true : false;

    m_zoom += sign? 1 : -1;

    if(m_zoom < 1)
        m_zoom = 1;

    cellSizeUpdated();
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
    //    v->setType(DeltaVolume::Drill);
        brushStroke(v);
    else if(m_state == ICE)
        v->setType(Ice);

    MeltModel* mod = static_cast<MeltModel*>(model());
    mod->updateBehaviour();

    reset();
}

void MeltView::cellSizeUpdated()
{
    QHeaderView* header = horizontalHeader();
    header->setDefaultSectionSize(m_minCellSize * m_zoom);

    header =  verticalHeader();
    header->setDefaultSectionSize(m_minCellSize * m_zoom);
}

void MeltView::brushStroke(DeltaVolume* const _v)
{
    switch(m_brush)
    {
        case ONEPIX:
            _v->setType(Drill);
//        case TWOPIX:
//        {
//        }
    }
}

}
