#include <QPainter>

#include "meltdelegate.h"
#include "deltavolume.h"
#include <QDebug>

static const QColor background(0, 0, 255);
static const QColor borderColor(0, 255, 255);
static const QColor drillColor(0, 0, 0);


MeltDelegate::MeltDelegate(QObject *_parent) :
    QStyledItemDelegate(_parent)
{}

void MeltDelegate::paint(QPainter* _painter, const QStyleOptionViewItem& _option, const QModelIndex& _index) const
{
    if(!_index.isValid())
        return;

    _painter->save();

    _painter->fillRect(_option.rect, background);

    const DeltaVolume* v = reinterpret_cast<DeltaVolume*>(_index.internalPointer());

    switch(v->behaviour())
    {
        case Border:
             _painter->fillRect(_option.rect, borderColor);  break;
        case Drill:
             _painter->fillRect(_option.rect, drillColor);   break;

        default:
        {
            double temperature = v->temperature();
            double koeff = calculateBrightness(temperature);

            QColor color(255, 0, 0, koeff);
            _painter->fillRect(_option.rect, color);
        }
    }
    _painter->restore();
}

QSize MeltDelegate::sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const
{
//    qDebug() << "sizeHint";
    return QSize(20, 20);
}

void MeltDelegate::updateMinTemp(double _newMin)
{
    m_minTemp = _newMin;
}

void MeltDelegate::updateMaxTemp(double _newMax)
{
    m_maxTemp = _newMax;
}

double MeltDelegate::calculateBrightness(double _temperature) const
{
    double diff = m_maxTemp - m_minTemp;

    if(diff == 0)
        return 0;

    return (_temperature - m_minTemp) * (255 / diff);
}
