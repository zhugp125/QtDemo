#include "widget.h"
#include <QMouseEvent>
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    m_point1 = event->pos();
    QWidget::mousePressEvent(event);
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    m_point1 = m_point2;
    update();
    QWidget::mouseReleaseEvent(event);
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    m_point2 = event->pos();
    update();
    QWidget::mouseMoveEvent(event);
}

void Widget::paintEvent(QPaintEvent *event)
{
    if (m_point1 != m_point2)
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);
        QPen pen;
        pen.setWidth(2);
        pen.setCapStyle(Qt::RoundCap);
        pen.setColor(Qt::lightGray);
        painter.setPen(pen);
        painter.setBrush(QBrush(Qt::transparent));
        painter.drawRect(QRect(m_point1, m_point2));
    }
    QWidget::paintEvent(event);
}
