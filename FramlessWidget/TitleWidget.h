#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>

class QLabel;
class QToolButton;

class CTitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CTitleWidget(QWidget *parent = nullptr);

    void setTitle(const QString& title);

protected:
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void signalClose();
    void signalMax();
    void signalMin();

private:
    QLabel* m_pTitleLabel = nullptr;
    QToolButton* m_pMinButton = nullptr;
    QToolButton* m_pMaxButton = nullptr;
    QToolButton* m_pCloseButton = nullptr;

};

#endif // TITLEWIDGET_H
