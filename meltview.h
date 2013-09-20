#ifndef MELTVIEW_H
#define MELTVIEW_H

#include <QTableView>


enum MouseState{NOSTATE = 0,
                INFO    = 1,
                DRILL   = 2,
                ICE     = 4,
                LOUPE   = 8};

class DeltaVolume;
class MeltView : public QTableView
{
    Q_OBJECT
public:
    explicit MeltView(QWidget* _parent = 0);
    void setMouseState(MouseState _state);
    void resizeEvent(QResizeEvent*);

private:
    void mousePressEvent(QMouseEvent *_e);
    void wheelEvent(QWheelEvent *_ev);
    DeltaVolume* volumeFromPos(const QPoint& _p);
    void mouseMoveEvent(QMouseEvent *_e);
    void cellSizeUpdated();

private:
    MouseState  m_state;
    int m_minCellSize;
    double m_zoom;
};

#endif // MELTVIEW_H
