#include "DargEffect.h"
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QPainter>
#include <QLinearGradient>
#include <QPainterPath>

constexpr int g_line = 30;

DargEffect::DargEffect(QWidget *parent)
    : QWidget(parent)
{
    setAcceptDrops(true);
}

DargEffect::~DargEffect()
{

}

void DargEffect::dragEnterEvent(QDragEnterEvent *event)
{
    m_drop_effect = true;
    update();
    event->acceptProposedAction();
}

void DargEffect::dragMoveEvent(QDragMoveEvent *event)
{
    m_drop_effect = true;
    update();
    event->acceptProposedAction();
}

void DargEffect::dragLeaveEvent(QDragLeaveEvent *event)
{
    m_drop_effect = false;
    update();
    QWidget::dragLeaveEvent(event);
}

void DargEffect::dropEvent(QDropEvent *event)
{
    m_drop_effect = false;
    update();

    const QMimeData *ptr_mime_data = event->mimeData();
    if (nullptr == ptr_mime_data)
    {
        return;
    }

    if (ptr_mime_data->hasUrls())
    {
        QList<QUrl> urls = ptr_mime_data->urls();
        if (urls.isEmpty())
        {
            return;
        }
        if (m_pixmap.load(urls.front().toLocalFile()))
        {
            update();
        }
    }
}

void DargEffect::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    if (!m_pixmap.isNull())
    {
        if (m_pixmap.size() != size())
        {
            m_pixmap = m_pixmap.scaled(size(), Qt::KeepAspectRatio);
        }
        p.drawPixmap(rect(), m_pixmap);
    }

    QLinearGradient liner_gradient;
    liner_gradient.setColorAt(0.0, Qt::red);
    liner_gradient.setColorAt(1.0, Qt::gray);
    p.save();
    p.setBrush(liner_gradient);
    p.setPen(Qt::white);

    if (m_drop_effect)
    {
        QPainterPath path;
        path.moveTo(0, 0);
        path.lineTo(width(), 0);
        path.lineTo(width() - g_line, g_line);
        path.lineTo(g_line, g_line);
        path.closeSubpath();
        p.drawPath(path);
    }
    if (m_drop_effect)
    {
        QPainterPath path;
        path.moveTo(width(), 0);
        path.lineTo(width(), height());
        path.lineTo(width() - g_line, height() - g_line);
        path.lineTo(width() - g_line, g_line);
        path.closeSubpath();
        p.drawPath(path);
    }
    if (m_drop_effect)
    {
        QPainterPath path;
        path.moveTo(width(), height());
        path.lineTo(0, height());
        path.lineTo(g_line, height() - g_line);
        path.lineTo(width() - g_line, height() - g_line);
        path.closeSubpath();
        p.drawPath(path);
    }
    if (m_drop_effect)
    {
        QPainterPath path;
        path.moveTo(0, height());
        path.lineTo(0, 0);
        path.lineTo(g_line, g_line);
        path.lineTo(g_line, height() - g_line);
        path.closeSubpath();
        p.drawPath(path);
    }
    p.restore();
    QWidget::paintEvent(event);
}
