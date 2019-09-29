#include "widget.h"
#include "SearchLine.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    ptr_search_line_ = new SearchLine(this);
    ptr_search_line_->setFixedSize(200, 30);
    ptr_search_line_->move(20, 20);

    ptr_search_line_->SetLayoutDirection(Qt::RightToLeft);
    ptr_search_line_->setAlignment(Qt::AlignRight | Qt::AlignAbsolute);
    ptr_search_line_->SetSearchButtonVisible(true);
}

Widget::~Widget()
{

}
