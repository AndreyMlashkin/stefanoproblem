#ifndef GRAPHICSWIDGET_H
#define GRAPHICSWIDGET_H

#include <QWidget>
#include "ui_graphics.h"

class Graphics;
class QAbstractItemDelegate;
class QAbstractItemModel;
class MeltModel;

class GraphicsWidget : public QWidget
{
    Q_OBJECT

    enum chartOrientation {horizontal, vertical, time};

public:
    explicit GraphicsWidget(QWidget *parent = 0);

    void setModel(QAbstractItemModel* _model);
    void setDelegate(QAbstractItemDelegate* _delegate);
    void closeEvent(QCloseEvent *);

public slots:
    void chartOrientationChanged();

signals:
    void closing();

private:
    Ui::Graphics* m_ui;
    MeltModel* m_model;
};

#endif // GRAPHICSWIDGET_H
