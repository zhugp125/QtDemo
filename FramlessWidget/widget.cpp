#include "widget.h"
#include "TitleWidget.h"
#include <QMouseEvent>
#include <QDesktopWidget>
#include <QApplication>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    p_title_widget_ = new CTitleWidget(this);
    p_title_widget_->setTitle("Frameless Widget");
    connect(p_title_widget_, &CTitleWidget::signalClose, this, &QWidget::close);
    connect(p_title_widget_, &CTitleWidget::signalMin, this, &QWidget::showMinimized);
    connect(p_title_widget_, &CTitleWidget::signalMax, this, &Widget::onShowMaximized);

    resize(400, 300);
    setMinimumSize(320, 240);
    //setMaximumSize(600, 500);
    setMouseTracking(true);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Widget);
}

Widget::~Widget()
{
}

void Widget::onShowMaximized()
{
    if (size() == QApplication::desktop()->size()) // 已经最大化，还原
    {
        setGeometry(property("geometry").toRect());
    }
    else
    {
        setProperty("geometry", geometry());
        setGeometry(QApplication::desktop()->geometry());
    }
}

void Widget::resizeEvent(QResizeEvent *event)
{
    if (p_title_widget_ != nullptr)
    {
        p_title_widget_->setFixedWidth(width());
        p_title_widget_->move(0, 0);
    }
    QWidget::resizeEvent(event);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        start_pos_ = event->pos();
    }
    QWidget::mousePressEvent(event);
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        if (enum_direction_ == NoDir) // 不拖动，只移动窗体位置
        {
            move(event->pos() - start_pos_ + pos());
        }
        else
        {
            int n_left = geometry().left();
            int n_top = geometry().top();
            int n_right = geometry().right();
            int n_bottom = geometry().bottom();
            // 根据拖动方向，重新计算窗体位置
            if (enum_direction_ & Top)
            {
                n_top = event->globalY();
            }
            else if (enum_direction_ & Bottom)
            {
                n_bottom = event->globalY();
            }

            if (enum_direction_ & Left)
            {
                n_left = event->globalX();
            }
            else if (enum_direction_ & Right)
            {
                n_right = event->globalX();
            }

            // 重新计算后的宽度在最小宽度和最大宽度之外，则计算无效，恢复原先的坐标
            if (n_right - n_left < minimumWidth() ||
                n_right - n_left > maximumWidth())
            {
                n_right = geometry().right();
                n_left = geometry().left();
            }
            // 重新计算后的高度在最小高度和最大高度之外，则计算无效，恢复原先的坐标
            if (n_bottom - n_top < minimumHeight() ||
                n_bottom - n_top > maximumHeight())
            {
                n_top = geometry().top();
                n_bottom = geometry().bottom();
            }
            setGeometry(QRect(QPoint(n_left, n_top), QPoint(n_right, n_bottom)));
        }
    }
    else
    {
        // 检测边缘
        testEdge(event->pos());
    }
    QWidget::mouseMoveEvent(event);
}

/*!
 * \brief setCursorShape 设置鼠标显示形状
 * \param enum_direction 拖动方向
 */
void Widget::setCursorShape(MoveDirection enum_direction)
{
    Qt::CursorShape shape = Qt::ArrowCursor;
    switch(enum_direction)
    {
    case TopLeft:
    case BottomRight:
        shape = Qt::SizeFDiagCursor;
        break;
    case TopRight:
    case BottomLeft:
        shape = Qt::SizeBDiagCursor;
        break;
    case Top:
    case Bottom:
        shape = Qt::SizeVerCursor;
        break;
    case Left:
    case Right:
        shape = Qt::SizeHorCursor;
        break;
    default:
        break;
    }
    setCursor(shape);
}

/*!
 * \brief testEdge 窗体边缘检测
 * \param p        当前坐标位置，相对坐标
 */
void Widget::testEdge(const QPoint &p)
{
    int enum_direction = NoDir;
    if (p.x() < num_edge_)
    {
        enum_direction |= Left;
    }
    else if (p.x() > (width() - num_edge_))
    {
        enum_direction |= Right;
    }

    if (p.y() < num_edge_)
    {
        enum_direction |= Top;
    }
    else if (p.y() > (height() - num_edge_))
    {
        enum_direction |= Bottom;
    }
    enum_direction_ = static_cast<MoveDirection>(enum_direction);
    setCursorShape(enum_direction_);
}
