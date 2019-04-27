#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->widget_left->setLable("Left");
    ui->widget_left->setBackgroundColor("red");
    ui->widget_right->setLable("Right");
    ui->widget_right->setBackgroundColor("Yellow");
}

Widget::~Widget()
{
    delete ui;
}
