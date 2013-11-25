#ifndef MELTVIEW_H
#define MELTVIEW_H

#include <QTableView>
#include "modelapi.h"

namespace model
{

class DeltaVolume;
class MeltView : public QTableView
{
    Q_OBJECT
public:

    enum MouseState {NOSTATE = NoType, ICE = Ice, DRILL = Drill, WATER = Water, INFO = TYPE_COUNT+1, LOUPE = TYPE_COUNT+2};

    enum BrushType {ONEPIX,
                    TWOPIX,
                    THREEPIX};

    explicit MeltView(QWidget* _parent = 0);
    void setMouseState(MouseState _state);
    void setBrushType(BrushType _brush);

    void resizeEvent(QResizeEvent*);

private:
    void mousePressEvent(QMouseEvent *_e);
    void wheelEvent(QWheelEvent *_ev);
    DeltaVolume* volumeFromPos(const QPoint& _p) const;
    void mouseMoveEvent(QMouseEvent *_e);
    void cellSizeUpdated();
    inline void brushStroke(DeltaVolume* const _v);

private:
    MouseState  m_state;
    BrushType m_brush;
    int m_minCellSize;
    double m_zoom;
};
}

#endif // MELTVIEW_H
