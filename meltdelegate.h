#ifndef MELTDELEGATE_H
#define MELTDELEGATE_H

#include <QStyledItemDelegate>

namespace model
{

class MeltDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MeltDelegate(QObject *_parent = 0);
    void paint(QPainter *_painter, const QStyleOptionViewItem &_option, const QModelIndex &_index) const;
    QSize sizeHint(const QStyleOptionViewItem &_option, const QModelIndex &_index) const;

public slots:
    void updateMinTemp(double _newMin);
    void updateMaxTemp(double _newMax);

    void highlightColumn(int _n);
    void highlightRow(int _n);

private:
    inline double calculateBrightness(double _temperature) const;

private:
    double m_maxTemp, m_minTemp;
    int m_highlightedRow;
    int m_highlightedColumn;
};
}
#endif // MELTDELEGATE_H
