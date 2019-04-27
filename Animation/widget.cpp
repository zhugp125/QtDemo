#include "widget.h"
#include "ui_widget.h"
#include <QPropertyAnimation>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    m_ptr_widget(new QWidget(this))
{
    ui->setupUi(this);
    m_ptr_widget->setFixedWidth(200);
    m_ptr_widget->setStyleSheet("QWidget{background: red;}");
    m_ptr_widget->raise();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::resizeEvent(QResizeEvent *event)
{
    m_ptr_widget->setFixedHeight(ui->textEdit->height());
    m_ptr_widget->move(QPoint(width(), 0));
    QWidget::resizeEvent(event);
}

void Widget::on_pushButton_clicked()
{
    QPropertyAnimation *animation = new QPropertyAnimation(m_ptr_widget, "pos");
    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::OutBack);
    animation->setStartValue(QPoint(width(), 0));
    animation->setEndValue(QPoint(width() - m_ptr_widget->width(), 0));
    animation->start();
}
