#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QPushButton;
class CWating;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QPushButton* m_pButton = nullptr;
    CWating* m_pWating= nullptr;
};

#endif // WIDGET_H
