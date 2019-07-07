#include "FilterHeaderView.h"
#include <QPainter>
#include <QMouseEvent>

CFilterHeaderView::CFilterHeaderView(QWidget *parent)
    : QHeaderView(Qt::Horizontal, parent)
{
}

void CFilterHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();

    QVariant filterVar = model()->headerData(logicalIndex, orientation(), FilterRole);
    if (filterVar.isValid() && filterVar.toBool())
    {
        QPixmap pix = m_norFilterPix;
        bool b_contain = getFilterRect(rect).contains(cursor().pos());
        if (logicalIndex == m_hover && b_contain)
        {
            pix = m_hovFilterPix;
        }
        if (logicalIndex == m_press && b_contain)
        {
            pix = m_preFilterPix;
        }

        int align = Qt::AlignRight | Qt::AlignVCenter;
        QVariant alignVar = model()->headerData(logicalIndex, orientation(), FilterAlignmentRole);
        if (alignVar.isValid())
        {
            align = alignVar.toInt();
        }
        style()->drawItemPixmap(painter, rect, align, pix);
    }
}

void CFilterHeaderView::mousePressEvent(QMouseEvent *e)
{
    m_press = logicalIndexAt(e->pos());
    if (m_press != -1)
        updateSection(m_press);
    QHeaderView::mousePressEvent(e);
}

void CFilterHeaderView::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        int section = logicalIndexAt(e->pos());
        QVariant filterVar = model()->headerData(section, orientation(), FilterRole);
        if (filterVar.isValid() && filterVar.toBool())
        {
            QRect rect(sectionViewportPosition(section), 0, sectionSize(section), height());
            if (getFilterRect(rect).contains(cursor().pos()))
            {
                emit filterClicked(section);
            }
        }
    }
    m_press = -1;
    QHeaderView::mouseReleaseEvent(e);
}

void CFilterHeaderView::mouseMoveEvent(QMouseEvent *e)
{
    m_hover = logicalIndexAt(e->pos());
    if (m_hover != -1)
        updateSection(m_hover);
    QHeaderView::mouseMoveEvent(e);
}

bool CFilterHeaderView::event(QEvent *e)
{
    switch(e->type())
    {
    case QEvent::Leave:
    case QEvent::HoverLeave:
        if (m_hover != -1)
            updateSection(m_hover);
        m_hover = -1;
        break;
    default:
        break;
    }
    return QHeaderView::event(e);
}

QRect CFilterHeaderView::getFilterRect(const QRect &rect) const
{
    QPoint g_topRight = mapToGlobal(rect.topRight());
    return QRect(g_topRight - QPoint(m_norFilterPix.width(), (m_norFilterPix.height() - rect.height()) / 2), m_norFilterPix.size());
}
