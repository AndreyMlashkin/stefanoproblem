#ifndef MELTDELEGATE_H
#define MELTDELEGATE_H

#include <QStyledItemDelegate>

class MeltDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MeltDelegate(QObject *_parent = 0);
    void paint(QPainter *_painter, const QStyleOptionViewItem &_option, const QModelIndex &_index) const;
    QSize sizeHint(const QStyleOptionViewItem &_option, const QModelIndex &_index) const;

signals:
    
public slots:
    
};

#endif // MELTDELEGATE_H
