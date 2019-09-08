#ifndef WATING_H
#define WATING_H

#include <QDialog>

class QTimer;

class CWating : public QDialog
{
    Q_OBJECT
public:
    explicit CWating(QWidget *parent = nullptr);
    ~CWating();

    void setColor(const QColor& color);
    void setFont(const QFont& font);
    void setMessage(const QString& msg);

public Q_SLOTS:
    void start();
    void stop();

protected:
    void paintEvent(QPaintEvent* event);

private:
    QTimer* m_pTimer = nullptr;
    int m_rotate = 0;
    QColor m_color = QColor(Qt::gray);
    QFont m_font;
    QString m_strMsg;
};

#endif // WATING_H
