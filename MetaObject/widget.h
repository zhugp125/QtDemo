#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QMetaMethod>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

signals:
    void clicked();

public slots:
    void onBtnClicked();

private slots:
    void onText();

private:
    QPushButton *btn;

    QMap<QString, QMetaMethod> methods;
};

#endif // WIDGET_H
