#include "ButtonItemDelegate.h"
#include <QPainter>
#include <QMouseEvent>

CButtonItemDelegate::CButtonItemDelegate(QObject *parent) : QItemDelegate(parent)
{

}

void CButtonItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)

    painter->save();
    painter->drawPixmap(option.rect.topLeft(), view_pixmap_);
    // mouse over下Mac上有点问题
    // window下，vs2015环境，tableview->setMouseTracking(true)后正常
    //if (option.state & QStyle::State_MouseOver)
    {
        painter->drawPixmap(option.rect.topRight() - QPoint(40, 0), close_pixmap_);
    }
    painter->restore();
}

bool CButtonItemDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option,
                                      const QModelIndex &index)
{
    Q_UNUSED(model)
    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* p_mouse_event = dynamic_cast<QMouseEvent*>(event);
        if (!p_mouse_event)
            return false;

        QRect view_rect(option.rect.topLeft(), view_pixmap_.size());
        if (view_rect.contains(p_mouse_event->pos()))
        {
            emit viewClicked(index);
        }

        QRect close_rect(option.rect.topRight() - QPoint(close_pixmap_.width(), 0), close_pixmap_.size());
        if (close_rect.contains(p_mouse_event->pos()))
        {
            emit closeClicked(index);
        }
    }
    return true;
}
