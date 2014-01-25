#include <QPainter>
#include <QDebug>

#include "meltdelegate.h"
#include "deltavolume.h"

namespace model
{

static const QColor background(0, 0, 255);
static const QColor borderColor(0, 255, 255);
static const QColor drillColor(0, 0, 0);
static const QColor highligtingColor(0, 0, 0, 50);


MeltDelegate::MeltDelegate(QObject *_parent) :
    QStyledItemDelegate(_parent),
    m_highlightedRow(-1),
    m_highlightedColumn(-1),
    m_maxTemp(INT_MIN),
    m_minTemp(INT_MAX)
{}

void MeltDelegate::paint(QPainter* _painter, const QStyleOptionViewItem& _option, const QModelIndex& _index) const
{
    if(!_index.isValid())
        return;

    _painter->save();

    _painter->fillRect(_option.rect, background);

    const DeltaVolume* v = reinterpret_cast<DeltaVolume*>(_index.internalPointer());

    if(v->type() == Drill)
    {
        _painter->fillRect(_option.rect, drillColor);
        _painter->restore();
        return;
    }

    switch(v->behaviour())
    {
        case Border:
             _painter->fillRect(_option.rect, borderColor);  break;
//        case Drill:
//             _painter->fillRect(_option.rect, drillColor);   break;

        default:
        {
            double temperature = v->temperature();
            double koeff = calculateBrightness(temperature);

            if(koeff == 0)
                break;

            QColor color(255, 0, 0, koeff);
            _painter->fillRect(_option.rect, color);
        }
    }

    if(m_highlightedColumn == _index.column())
        _painter->fillRect(_option.rect, highligtingColor);
    else if(m_highlightedRow == _index.row())
        _painter->fillRect(_option.rect, highligtingColor);

    _painter->restore();
}

QSize MeltDelegate::sizeHint(const QStyleOptionViewItem&, const QModelIndex&) const
{
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

void MeltDelegate::highlightColumn(int _n)
{
    m_highlightedRow = -1;
    m_highlightedColumn = _n;
}

void MeltDelegate::highlightRow(int _n)
{
    m_highlightedColumn = -1;
    m_highlightedRow = _n;
}


double MeltDelegate::calculateBrightness(double _temperature) const
{
    double diff = m_maxTemp - m_minTemp;

    if(diff == 0)
        return 0;

    return (_temperature - m_minTemp) * (255 / diff);
}

}
