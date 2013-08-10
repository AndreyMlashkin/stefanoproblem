#include <QPainter>

#include "meltdelegate.h"
#include <QDebug>

static const double ABSNULL = -273.15;

MeltDelegate::MeltDelegate(QObject *_parent) :
    QStyledItemDelegate(_parent)
{}

void MeltDelegate::paint(QPainter *_painter, const QStyleOptionViewItem &_option, const QModelIndex &_index) const
{
    if(!_index.isValid())
        return;

    _painter->save();

    double temperature = _index.data().toDouble(); //static_cast<double>(_index.internalPointer());

    static const double maxTemp = 0.6;//= 100;
    static const double minTemp = 0; //= -273.15;

    double diff = maxTemp - minTemp;
    double koeff = temperature * (255 / diff);

//    qDebug() << koeff;

    QColor color(255, 0, 0, koeff);
    _painter->fillRect(_option.rect, color);
    _painter->restore();
}

QSize MeltDelegate::sizeHint(const QStyleOptionViewItem &_option, const QModelIndex &_index) const
{
    qDebug() << "sizeHint";
    return QSize(20, 20);
}
