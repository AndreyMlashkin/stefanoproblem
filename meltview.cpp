#include <QDebug>
#include <QMouseEvent>
#include <QToolTip>
#include <QHeaderView>

#include "meltview.h"
#include "deltavolume.h"

inline int min(int a, int b)
{
    return (a < b)? a : b;
}

MeltView::MeltView(QWidget* _parent) :
    QTableView(_parent)
{
}

void MeltView::mousePressEvent(QMouseEvent *_e)
{
    QModelIndex index = indexAt(_e->pos());
    if(!index.isValid())
        return;

    const DeltaVolume* v = reinterpret_cast<DeltaVolume*>(index.internalPointer());
    QToolTip::showText(_e->globalPos(), QString::number(v->temperature(), 'f'));
}

void MeltView::resizeEvent(QResizeEvent*)
{
    if(!model())
        return;

    int cellWidth  = height() / model()->rowCount();
    int cellHeight = width()  / model()->columnCount();

    int cellSize = min(cellWidth, cellHeight);

    QHeaderView* header = horizontalHeader();
    header->setDefaultSectionSize(cellSize);

    header =  verticalHeader();
    header->setDefaultSectionSize(cellSize);
}
