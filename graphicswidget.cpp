#include <QDebug>
#include <QMouseEvent>
#include <QToolTip>

#include "graphicswidget.h"
#include "ui_graphics.h"
#include "meltmodel.h"
#include "deltavolume.h"

int inline min(int a, int b)
{
    return (a < b)? a : b;
}

GraphicsWidget::GraphicsWidget(QWidget *parent) :
    QWidget(parent),
    m_ui(new Ui::Graphics()),
    m_model(NULL)

{
    m_ui->setupUi(this);

    QHeaderView* header = m_ui->graphics->horizontalHeader();
    header->hide();

    header =  m_ui->graphics->verticalHeader();
    header->hide();

    m_ui->graphics->installEventFilter(this);
}

void GraphicsWidget::setModel(QAbstractItemModel *_model)
{
    m_model = static_cast<MeltModel*>(_model);
    m_ui->graphics->setModel(_model);
    resizeEvent(NULL);
}

void GraphicsWidget::setDelegate(QAbstractItemDelegate *_delegate)
{
    m_ui->graphics->setItemDelegate(_delegate);
}

void GraphicsWidget::closeEvent(QCloseEvent *)
{
    emit closing();
}
