#include <QDebug>
#include <QMouseEvent>
#include <QToolTip>
#include <QHeaderView>
#include <QScrollBar>

#include "meltview.h"
#include "deltavolume.h"
#include "meltmodel.h"
#include "modelfield.h"

namespace model
{

inline int min(int a, int b)
{
    return (a < b)? a : b;
}

MeltView::MeltView(QWidget* _parent)
  : QTableView(_parent),
    m_state(NOSTATE),
    m_brush(ONEPIX),
    m_minCellSize(1),
    m_zoom(1)
{
    resizeEvent(NULL);
}

void MeltView::mousePressEvent(QMouseEvent* _e)
{
    QModelIndex index = indexAt(_e->pos());
    if(!index.isValid())
        return;

    if(m_state == INFO)
        QToolTip::showText(_e->globalPos(), index.data().toString());
    else if(m_state == LOUPE)
        qDebug() << "Zoom";
    else
    {
        DeltaVolume* v = volumeFromPos(_e->pos());
        applyMouseBrush(v);
    }
}

void MeltView::mouseMoveEvent(QMouseEvent* _e)
{
    DeltaVolume* v = volumeFromPos(_e->pos());
    applyMouseBrush(v);
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

DeltaVolume* MeltView::volumeFromPos(const QPoint& _p) const
{
    QModelIndex index = indexAt(_p);
    if(!index.isValid())
        return NULL;

    return reinterpret_cast<DeltaVolume*>(index.internalPointer());
}

void MeltView::cellSizeUpdated()
{
    QHeaderView* header = horizontalHeader();
    header->setDefaultSectionSize(m_minCellSize * m_zoom);

    header =  verticalHeader();
    header->setDefaultSectionSize(m_minCellSize * m_zoom);
}

void MeltView::applyMouseBrush(DeltaVolume* _clickedCell)
{
    if(!_clickedCell)
        return;

    if(_clickedCell->behaviour() == Border)
        return;

    if((m_state == DRILL) || (m_state == ICE) || (m_state == WATER))
        changeCellsType(getSelection(_clickedCell, m_brush), Type(m_state));

    MeltModel* mod = static_cast<MeltModel*>(model());
    mod->updateBehaviour();

    reset();
}

QVector<DeltaVolume*> MeltView::getSelection(DeltaVolume* _center, MeltView::BrushType _selectionType)
{
    ModelField* field = static_cast<MeltModel*>(model())->field();
    ModelField::iterator center(_center, field);

    QVector<ModelField::iterator> checked;
    QVector<DeltaVolume*> ans;
    if(!center.isValid() || !field)
    {
        qDebug() << Q_FUNC_INFO;
        return ans;
    }

    switch(_selectionType)
    {
        case THREEPIX:
        {
            checked.reserve(9);

            bool isTop    = center.top().isValid();
            bool isBottom = center.bottom().isValid();
            bool isLeft   = center.left().isValid();
            bool isRight  = center.right().isValid();

            if(isLeft && isBottom)
                checked.push_back(center.left().bottom());

            if(isLeft && isTop)
                checked.push_back(center.left().top());

            if(isRight && isTop)
                checked.push_back(center.right().top());

            if(isRight && isBottom)
                checked.push_back(center.right().bottom());
        }

        case TWOPIX:
//            checked.reserve(5);
            while(center.isNextNeighbour())
                checked.push_back(center.next());

        case ONEPIX:
            checked.push_back(center); break;
    }

    foreach (ModelField::iterator i, checked)
        ans << i.take();

    return ans;
}

void MeltView::changeCellsType(QVector<DeltaVolume*> _cells, Type _newType)
{
    foreach (DeltaVolume* cell, _cells)
        if(cell->behaviour() != Border)
            cell->setType(_newType);
}

}
