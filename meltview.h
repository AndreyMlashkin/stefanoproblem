#ifndef MELTVIEW_H
#define MELTVIEW_H

#include <QTableView>


enum MouseState{NOSTATE, DRILL, ICE};

class DeltaVolume;
class MeltView : public QTableView
{
    Q_OBJECT
public: 
    explicit MeltView(QWidget* _parent = 0);
    void mousePressEvent(QMouseEvent *_e);
    void resizeEvent(QResizeEvent*);
    void setMouseState(MouseState _state);
    void wheelEvent(QWheelEvent *_ev);

private:
    MouseState  m_state;
    DeltaVolume* volumeFromPos(const QPoint& _p);
    void mouseMoveEvent(QMouseEvent *_e);

};

#endif // MELTVIEW_H
