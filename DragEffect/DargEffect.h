#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class DargEffect : public QWidget
{
    Q_OBJECT

public:
    DargEffect(QWidget *parent = nullptr);
    ~DargEffect();

protected:
    void dragEnterEvent(QDragEnterEvent* event);
    void dragMoveEvent(QDragMoveEvent* event);
    void dragLeaveEvent(QDragLeaveEvent* event);
    void dropEvent(QDropEvent* event);
    void paintEvent(QPaintEvent* event);

private:
    QPixmap m_pixmap;
    bool m_drop_effect = false;
};

#endif // WIDGET_H
