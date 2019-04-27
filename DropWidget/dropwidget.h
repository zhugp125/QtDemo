#ifndef DROPWIDGET_H
#define DROPWIDGET_H

#include <QWidget>

namespace Ui {
class DropWidget;
}

class DropWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DropWidget(QWidget *parent = 0);
    ~DropWidget();

    void setBackgroundColor(const QString& background_color);
    QString backgroundColor() const;
    void setLable(const QString& label);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

private:
    void performDrag();

    Ui::DropWidget *ui;
    QString m_background_color;
    QPoint m_start_pos;
    QPoint m_end_pos;
};

#endif // DROPWIDGET_H
