#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class CTitleWidget;

// 鼠标拖动方向
enum MoveDirection
{
    NoDir = 0x00,                       // 无拖动
    Left = 0x01,                        // 向左拖动
    Right = 0x02,                       // 向右拖动
    Top = 0x04,                         // 向上拖动
    Bottom = 0x08,                      // 向下拖动
    TopLeft = Top | Left,               // 向左上拖动
    TopRight = Top | Right,             // 向右上拖动
    BottomLeft = Bottom | Left,         // 向左下拖动
    BottomRight = Bottom | Right,       // 向右下拖动
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void onShowMaximized();

protected:
    void resizeEvent(QResizeEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    /*!
     * \brief setCursorShape 设置鼠标显示形状
     * \param enum_direction 拖动方向
     */
    void setCursorShape(MoveDirection enum_direction);
    /*!
     * \brief testEdge 窗体边缘检测
     * \param p        当前坐标位置，相对坐标
     */
    void testEdge(const QPoint &p);

private:
    QPoint start_pos_;                      // 鼠标落下点的坐标
    const int num_edge_ = 4;                // 边缘距离
    MoveDirection enum_direction_ = NoDir;  // 拖动方向

    CTitleWidget* p_title_widget_ = nullptr;
};

#endif // WIDGET_H
