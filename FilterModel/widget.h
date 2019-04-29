#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class QStandardItemModel;
class QSortFilterProxyModel;

namespace Qt
{
    enum MyItemDataRole
    {
        StatusRole = Qt::UserRole + 1,
    };
}

class Widget : public QWidget
{
    Q_OBJECT    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void onOpenDir();
    void onFile();
    void onDir();
    void onCloseClicked(const QModelIndex& index);
    void onViewClicked(const QModelIndex& index);

private:
    Ui::Widget *ui;

    QStandardItemModel* ptr_model_ = nullptr;
    QSortFilterProxyModel* ptr_filter_model_ = nullptr;
};

#endif // WIDGET_H
