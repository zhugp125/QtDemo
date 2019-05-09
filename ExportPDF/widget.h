#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    QString readFile(const QString& fileName);

    void htmlToPdf(const QString& fileName, const QString& html);
    void textToPdf(const QString& fileName, const QString& text);

private slots:
    void on_toolButton_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
