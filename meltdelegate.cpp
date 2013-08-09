#include <QPainter>

#include "meltdelegate.h"
#include <QDebug>

MeltDelegate::MeltDelegate(QObject *_parent) :
    QStyledItemDelegate(_parent)
{}

void MeltDelegate::paint(QPainter *_painter, const QStyleOptionViewItem &_option, const QModelIndex &_index) const
{
    if(!_index.isValid())
        return;

    _painter->save();

    double temperature = _index.data().toDouble(); //static_cast<double>(_index.internalPointer());



    QColor color(temperature * 500, 0, 255);
    _painter->fillRect(_option.rect, color);
    _painter->restore();
}

QSize MeltDelegate::sizeHint(const QStyleOptionViewItem &_option, const QModelIndex &_index) const
{
    qDebug() << "sizeHint";
    return QSize(20, 20);
}
