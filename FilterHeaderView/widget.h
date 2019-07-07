#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSharedPointer>

QT_BEGIN_NAMESPACE

class QTableView;
class QStandardItemModel;
class QStandardItem;
class QSortFilterProxyModel;

QT_END_NAMESPACE

class CShowFilterWidget;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void appendRow(const QStringList& items);

private Q_SLOTS:
    void onFilterClicked(int section);
    void onHeaderDataChanged(Qt::Orientation orientation, int first, int last);
    void onRowInserted(const QModelIndex &parent, int first, int last);
    void onRowRemoved(const QModelIndex &parent, int first, int last);
    void onFilterHide(int section);

private:
    QTableView* m_tableView = nullptr;
    QStandardItemModel* m_model = nullptr;
    QSortFilterProxyModel* m_filterModel = nullptr;

    QSharedPointer<CShowFilterWidget> m_filterWidget;
};

#endif // WIDGET_H
