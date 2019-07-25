#include "widget.h"
#include <QTableView>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QHBoxLayout>

#include "FilterHeaderView.h"
#include "ShowFilterWidget.h"
#include "SortFilterProxyModel.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_tableView = new QTableView(this);
    m_model = new QStandardItemModel(this);
    m_filterModel = new CSortFilterProxyModel(this);
    m_filterModel->setFilterRole(Qt::ToolTipRole);
    m_filterModel->setSourceModel(m_model);
    m_tableView->setModel(m_filterModel);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_tableView);
    setLayout(mainLayout);

    m_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    m_tableView->verticalHeader()->hide();
    CFilterHeaderView* pHeader = new CFilterHeaderView(this);
    connect(pHeader, &CFilterHeaderView::filterClicked, this, &Widget::onFilterClicked);
    m_tableView->setHorizontalHeader(pHeader);

    m_filterWidget = QSharedPointer<CShowFilterWidget>(new CShowFilterWidget);
    m_filterWidget->hide();
    connect(m_filterWidget.get(), &CShowFilterWidget::filterHide, this, &Widget::onFilterHide);

    connect(m_model, &QAbstractItemModel::headerDataChanged, this, &Widget::onHeaderDataChanged);
    connect(m_model, &QAbstractItemModel::rowsInserted, this, &Widget::onRowInserted);
    connect(m_model, &QAbstractItemModel::rowsRemoved, this, &Widget::onRowRemoved);

    m_model->setColumnCount(4);
    Qt::Orientation orientation = Qt::Horizontal;
    int section = 0;
    m_model->setHeaderData(section, orientation, "ID", Qt::DisplayRole);
    m_model->setHeaderData(section, orientation, "ID", Qt::ToolTipRole);
    m_model->setHeaderData(section, orientation, Qt::AlignCenter, Qt::TextAlignmentRole);

    ++section;
    m_model->setHeaderData(section, orientation, "Name", Qt::DisplayRole);
    m_model->setHeaderData(section, orientation, "Name", Qt::ToolTipRole);
    m_model->setHeaderData(section, orientation, Qt::AlignCenter, Qt::TextAlignmentRole);
    m_model->setHeaderData(section, orientation, true, FilterRole);
    m_model->setHeaderData(section, orientation, static_cast<int>(Qt::AlignRight | Qt::AlignVCenter), FilterAlignmentRole);

    ++section;
    m_model->setHeaderData(section, orientation, "Score", Qt::DisplayRole);
    m_model->setHeaderData(section, orientation, "Score", Qt::ToolTipRole);
    m_model->setHeaderData(section, orientation, Qt::AlignCenter, Qt::TextAlignmentRole);

    ++section;
    m_model->setHeaderData(section, orientation, "Level", Qt::DisplayRole);
    m_model->setHeaderData(section, orientation, "Level", Qt::ToolTipRole);
    m_model->setHeaderData(section, orientation, Qt::AlignCenter, Qt::TextAlignmentRole);
    m_model->setHeaderData(section, orientation, true, FilterRole);
    m_model->setHeaderData(section, orientation, static_cast<int>(Qt::AlignRight | Qt::AlignVCenter), FilterAlignmentRole);

    appendRow(QStringList() << "1" << "张三" << "80" << "良");
    appendRow(QStringList() << "2" << "李四" << "70" << "中");
    appendRow(QStringList() << "3" << "王五" << "90" << "优");
    appendRow(QStringList() << "4" << "赵六" << "50" << "差");

    resize(420, 300);
}

Widget::~Widget()
{

}

void Widget::appendRow(const QStringList &items)
{
    QList<QStandardItem* > ptr_items;
    for (const auto& text : items)
    {
        QStandardItem* pItem = new QStandardItem;
        pItem->setData(text, Qt::DisplayRole);
        pItem->setData(text, Qt::ToolTipRole);
        ptr_items.append(pItem);
    }
    m_model->appendRow(ptr_items);
}

void Widget::onFilterClicked(int section)
{
    m_filterWidget->move(cursor().pos());
    m_filterWidget->showFilter(section);
}

void Widget::onHeaderDataChanged(Qt::Orientation orientation, int first, int last)
{
    if (first > last)
    {
        return;
    }

    for (int section = first; section <= last; ++section)
    {
        QVariant var = m_model->headerData(section, orientation, FilterRole);
        if (var.isValid() && var.toBool())
        {
            m_filterWidget->addFilter(section);
            m_filterModel->addFilter(section);
        }
    }
}

void Widget::onRowInserted(const QModelIndex &, int first, int last)
{
    QList<int> list_filter = m_filterWidget->filter();
    for (int row = first; row <= last; ++row)
    {
        for (const auto col : list_filter)
        {
            QStandardItem* pItem = m_model->item(row, col);
            m_filterWidget->addData(col, pItem->data(Qt::ToolTipRole).toString());
        }
    }
}

void Widget::onRowRemoved(const QModelIndex &, int first, int last)
{
    QList<int> list_filter = m_filterWidget->filter();
    for (int row = first; row <= last; ++row)
    {
        for (const auto col : list_filter)
        {
            QStandardItem* pItem = m_model->item(row, col);
            m_filterWidget->removeData(col, pItem->data(Qt::ToolTipRole).toString());
        }
    }
}

void Widget::onFilterHide(int section)
{
    m_filterModel->setFilterData(section, m_filterWidget->getSelectData());
}

