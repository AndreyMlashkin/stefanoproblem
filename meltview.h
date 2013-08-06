#ifndef MELTVIEW_H
#define MELTVIEW_H

#include <QWidget>


class QGraphicsScene;
class QGraphicsView;

class MeltView : public QWidget
{
    Q_OBJECT
public:
    MeltView(QWidget *_parent = 0);

signals:
    
public slots:
    
private:
    QGraphicsScene* m_gScene;
    QGraphicsView* m_gView;
};

#endif // MELTVIEW_H
