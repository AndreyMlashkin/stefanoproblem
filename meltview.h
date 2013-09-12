#ifndef MELTVIEW_H
#define MELTVIEW_H

#include <QTableView>

class MeltView : public QTableView
{
    Q_OBJECT
public:
    explicit MeltView(QWidget* _parent = 0);
    void mousePressEvent(QMouseEvent *_e);

private:
    void resizeEvent(QResizeEvent*);
    void paintEvent(QPaintEvent* _ev);


};

#endif // MELTVIEW_H
