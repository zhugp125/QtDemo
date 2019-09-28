#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class SearchLine;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    SearchLine* ptr_search_line_ = nullptr;
};

#endif // WIDGET_H
