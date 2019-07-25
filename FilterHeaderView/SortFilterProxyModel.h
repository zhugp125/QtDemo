#ifndef CSORTFILTERPROXYMODEL_H
#define CSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class CSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    CSortFilterProxyModel(QObject *parent = nullptr);

    void addFilter(int section);
    void setFilterData(int section, const QList<QString>& strData);

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

private:
    QMap<int, QStringList> m_filterData;
};

#endif // CSORTFILTERPROXYMODEL_H
