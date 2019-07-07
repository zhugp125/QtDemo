#ifndef SHOWFILTERWIDGET_H
#define SHOWFILTERWIDGET_H

#include <QWidget>
#include <QMap>
#include <QList>

QT_BEGIN_NAMESPACE

class QListView;
class QStandardItemModel;
class QStandardItem;

QT_END_NAMESPACE

class CShowFilterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CShowFilterWidget(QWidget *parent = nullptr);

private Q_SLOTS:
    void onItemCliked(const QModelIndex& index);

Q_SIGNALS:
    void filterHide(int section);

public:
    /*!
     * \brief addFilter   添加过滤项
     * \param section     要过滤的列
     */
    void addFilter(int section);

    /*!
     * \brief addData     添加过滤数据
     * \param section     要过滤的列
     * \param strData     过滤数据
     */
    void addData(int section, const QString& strData);

    /*!
     * \brief removeData  移除过滤数据
     * \param section     要过滤的列
     * \param strData     移除数据
     */
    void removeData(int section, const QString& strData);

    /*!
     * \brief showFilter  显示过滤项
     * \param section     要过滤的列
     */
    void showFilter(int section);

    /*!
     * \brief filter 返回要过滤的项
     * \return
     */
    QList<int> filter() const;

    /*!
     * \brief getSelectData 获取选中的数据
     * \return
     */
    QList<QString> getSelectData() const;

protected:
    virtual void hideEvent(QHideEvent *event);

private:
    QMap<int, QMap<QString, bool> > m_filterData;
    int m_currentSection = -1;

    QListView* m_listView = nullptr;
    QStandardItemModel* m_model = nullptr;
    QList<QStandardItem*> m_items;

};

#endif // SHOWFILTERWIDGET_H
