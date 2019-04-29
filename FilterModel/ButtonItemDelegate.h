#ifndef BUTTONITEMDELEGATE_H
#define BUTTONITEMDELEGATE_H

#include <QItemDelegate>

class CButtonItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit CButtonItemDelegate(QObject *parent = nullptr);

    // painting
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

    // for non-widget editors
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

signals:
    void viewClicked(const QModelIndex& index);
    void closeClicked(const QModelIndex& index);

private:
    QPixmap view_pixmap_ = QPixmap(":/view.svg");
    QPixmap close_pixmap_ = QPixmap(":/close.svg");
};

#endif // BUTTONITEMDELEGATE_H
