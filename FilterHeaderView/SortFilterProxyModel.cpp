#include "SortFilterProxyModel.h"
#include <QDebug>

CSortFilterProxyModel::CSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}

void CSortFilterProxyModel::addFilter(int section)
{
    if (m_filterData.find(section) == m_filterData.end())
    {
        m_filterData[section];
    }
}

void CSortFilterProxyModel::setFilterData(int section, const QList<QString> &strData)
{
    if (m_filterData.contains(section))
    {
        m_filterData[section] = strData;
        invalidate();
    }
}

bool CSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    for (auto iter = m_filterData.begin(); iter != m_filterData.end(); ++iter)
    {
        const QStringList& str_list = iter.value();
        if (str_list.isEmpty())
        {
            continue;
        }

        QModelIndex source_index = sourceModel()->index(source_row, iter.key(), source_parent);
        QVariant var = sourceModel()->data(source_index, filterRole());
        if (!var.isValid() || !str_list.contains(var.toString()))
        {
            return false;
        }
    }
    return true;
}
