#include "ShowFilterWidget.h"
#include <QListView>
#include <QStandardItemModel>
#include <QHBoxLayout>

CShowFilterWidget::CShowFilterWidget(QWidget *parent) : QWidget(parent)
{
    m_listView = new QListView(this);
    m_model = new QStandardItemModel(m_listView);
    m_listView->setModel(m_model);

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setMargin(0);
    mainLayout->addWidget(m_listView);
    setLayout(mainLayout);

    m_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_listView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_listView->setSelectionBehavior(QAbstractItemView::SelectRows);

    setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);

    setFixedWidth(80);
    setMaximumHeight(100);

    connect(m_listView, &QAbstractItemView::clicked, this, &CShowFilterWidget::onItemCliked);
}

void CShowFilterWidget::onItemCliked(const QModelIndex &index)
{
    QStandardItem* pItem = m_model->itemFromIndex(index);
    Qt::CheckState checkState = (pItem->checkState() == Qt::Checked ? Qt::Unchecked : Qt::Checked);
    pItem->setCheckState(checkState);
    m_filterData[m_currentSection][pItem->text()] = (checkState == Qt::Checked);
}

/*!
 * \brief addFilter   添加过滤项
 * \param section     要过滤的列
 */
void CShowFilterWidget::addFilter(int section)
{
    if (m_filterData.find(section) == m_filterData.end())
    {
        m_filterData[section];
    }
}

/*!
 * \brief addData  添加过滤数据
 * \param section  要过滤的列
 * \param strData  过滤数据
 */
void CShowFilterWidget::addData(int section, const QString &strData)
{
   auto it = m_filterData.find(section);
   if (it != m_filterData.end())
   {
       it.value().insert(strData, true);
   }
}

/*!
 * \brief removeData  移除过滤数据
 * \param section     要过滤的列
 * \param strData     移除数据
 */
void CShowFilterWidget::removeData(int section, const QString &strData)
{
    auto it = m_filterData.find(section);
    if (it != m_filterData.end())
    {
        it.value().remove(strData);
    }
}

/*!
 * \brief showFilter  显示过滤项
 * \param section     要过滤的列
 */
void CShowFilterWidget::showFilter(int section)
{
    auto it = m_filterData.find(section);
    if (it != m_filterData.end())
    {
        m_currentSection = section;
        const QMap<QString, bool>& data_map = it.value();
        int row = 0;
        int rowCount = m_items.size();
        for (auto mit = data_map.begin(); mit != data_map.end(); ++mit, ++row)
        {
            if (row < rowCount)
            {
                m_items[row]->setText(mit.key());
                m_items[row]->setCheckState(mit.value() ? Qt::Checked : Qt::Unchecked);
            }
            else
            {
                QStandardItem* pItem = new QStandardItem(mit.key());
                pItem->setCheckState(mit.value() ? Qt::Checked : Qt::Unchecked);
                m_items.append(pItem);
                m_model->appendRow(pItem);
            }
        }
        for (int start = data_map.size(); start < rowCount; ++start)
        {
            m_model->removeRow(start);
        }
    }
    show();
}

/*!
 * \brief filter 返回要过滤的项
 * \return
 */
QList<int> CShowFilterWidget::filter() const
{
    return m_filterData.keys();
}

/*!
 * \brief getSelectData 获取选中的数据
 * \return
 */
QList<QString> CShowFilterWidget::getSelectData() const
{
    QList<QString> strDatas;
   auto it = m_filterData.find(m_currentSection);
   if (it != m_filterData.end())
   {
       for (auto mit = it.value().begin(); mit != it.value().end(); ++mit)
       {
           if (mit.value())
           {
               strDatas.append(mit.key());
           }
       }
   }
   return strDatas;
}

void CShowFilterWidget::hideEvent(QHideEvent *event)
{
    emit filterHide(m_currentSection);
    QWidget::hideEvent(event);
}
