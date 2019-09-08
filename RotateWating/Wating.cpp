#include "Wating.h"
#include <QPainter>
#include <QTimer>
#include <QVector>

constexpr int r_wating = 8;

CWating::CWating(QWidget *parent) : QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    resize(240, 200);
}

CWating::~CWating()
{
    if (m_pTimer != nullptr)
    {
        if (m_pTimer->isActive())
        {
            m_pTimer->stop();
        }
        delete m_pTimer;
        m_pTimer = nullptr;
    }
}

void CWating::setColor(const QColor &color)
{
    m_color = color;
    update();
}

void CWating::setFont(const QFont &font)
{
    m_font = font;
    update();
}

void CWating::setMessage(const QString &msg)
{
    m_strMsg = msg;
    update();
}

void CWating::start()
{
    if (nullptr == m_pTimer)
    {
        m_pTimer = new QTimer(this);
        connect(m_pTimer, &QTimer::timeout, this, [&](){
            m_rotate += 30;
            m_rotate %= 360;
            update();
        });
    }
    m_rotate = 0;
    m_pTimer->start(50);
}

void CWating::stop()
{
    m_pTimer->stop();
    hide();
}

void CWating::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    int font_height = 0;
    if (!m_strMsg.isEmpty())
    {
        painter.setFont(m_font);
        painter.setRenderHint(QPainter::TextAntialiasing, true);
        font_height = painter.fontMetrics().height();
    }

    QPoint wating_pos;
    if (font_height != 0)
    {
        int w = std::min(width(), height() - 10 - font_height);
        wating_pos = QPoint(0, 20 - w / 2);
        painter.translate(width() / 2, (height() - 10 - font_height) / 2);
    }
    else
    {
        int w = std::min(width(), height());
        wating_pos = QPoint(0, 20 - w / 2);
        painter.translate(rect().center());
    }
    painter.setPen(Qt::NoPen);

    QColor color = m_color;
    for (int i = 0; i < 12; ++i)
    {
        color.setAlphaF(1.0 - (i / 12.0));
        painter.setBrush(color);
        painter.save();
        painter.rotate(m_rotate - i * 30.0);
        painter.drawEllipse(wating_pos, r_wating, r_wating);
        painter.restore();
    }

    if (font_height != 0)
    {
        painter.save();
        painter.setPen(Qt::black);
        QPoint start_pos(width() / (-2), (height() - 10 - font_height) / 2);
        painter.drawText(QRect(start_pos, QSize(width(), font_height + 10)), Qt::AlignCenter, m_strMsg);
        painter.restore();
    }

    QWidget::paintEvent(event);
}
