#include "FilterHeaderView.h"
#include <QPainter>
#include <QMouseEvent>
#include <QStyleOption>
#include <QStyle>

CFilterHeaderView::CFilterHeaderView(QWidget *parent)
    : QHeaderView(Qt::Horizontal, parent)
{
    setSectionsClickable(true);
}

void CFilterHeaderView::onUpdateCheckState(const QModelIndex &index)
{
    if (!index.isValid())
    {
        return;
    }

    QVariant checkStateVar = model()->data(index, Qt::CheckStateRole);
    if (checkStateVar.isValid())
    {
        (checkStateVar.toInt() == Qt::Checked) ? (++m_checkedNum) : (--m_checkedNum);

        if (m_checkedNum <= 0)
        {
            model()->setHeaderData(index.column(), orientation(), Qt::Unchecked, Qt::CheckStateRole);
        }
        else if (m_checkedNum >= model()->rowCount())
        {
            model()->setHeaderData(index.column(), orientation(), Qt::Checked, Qt::CheckStateRole);
        }
        else
        {
            model()->setHeaderData(index.column(), orientation(), Qt::PartiallyChecked, Qt::CheckStateRole);
        }
    }
}

void CFilterHeaderView::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    painter->save();
    QHeaderView::paintSection(painter, rect, logicalIndex);
    painter->restore();

    QVariant checkStateVar = model()->headerData(logicalIndex, orientation(), Qt::CheckStateRole);
    if (checkStateVar.isValid())
    {
        QStyleOptionViewItem option;
        option.initFrom(this);

        option.checkState = static_cast<Qt::CheckState>(checkStateVar.toInt());
        option.features = QStyleOptionViewItem::HasCheckIndicator;
        option.viewItemPosition = QStyleOptionViewItem::OnlyOne;

        style()->drawControl(QStyle::CE_ItemViewItem, &option, painter, this);
    }

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

    QVariant checkStateVar = model()->headerData(m_press, orientation(), Qt::CheckStateRole);
    if (checkStateVar.isValid())
    {
        Qt::CheckState checkState = static_cast<Qt::CheckState>(checkStateVar.toInt());
        checkState = (checkState == Qt::Checked) ? Qt::Unchecked : Qt::Checked;
        model()->setHeaderData(m_press, orientation(), checkState, Qt::CheckStateRole);

        // 更新选中行数
        m_checkedNum = (checkState == Qt::Checked) ? model()->rowCount() : 0;

        for (int r = 0; r < model()->rowCount(); ++r)
        {
            QModelIndex index = model()->index(r, m_press);
            model()->setData(index, checkState, Qt::CheckStateRole);
        }
    }

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
