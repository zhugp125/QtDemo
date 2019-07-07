#ifndef FILTERHEADERVIEW_H
#define FILTERHEADERVIEW_H

#include <QHeaderView>

enum {
    FilterRole = Qt::UserRole + 2,
    FilterAlignmentRole = Qt::UserRole + 3,
};

class CFilterHeaderView : public QHeaderView
{
    Q_OBJECT

    Q_PROPERTY(QPixmap m_norFilterPix READ norFilterPix WRITE setNorFilterPix)
    Q_PROPERTY(QPixmap m_hovFilterPix READ hovFilterPix WRITE setHovFilterPix)
    Q_PROPERTY(QPixmap m_preFilterPix READ preFilterPix WRITE setPreFilterPix)

public:
    CFilterHeaderView(QWidget *parent = nullptr);

    void setNorFilterPix(const QPixmap& nor_pix) { m_norFilterPix = nor_pix; }
    QPixmap norFilterPix() const { return m_norFilterPix; }
    void setHovFilterPix(const QPixmap& hov_pix) { m_hovFilterPix = hov_pix; }
    QPixmap hovFilterPix() const { return m_hovFilterPix; }
    void setPreFilterPix(const QPixmap& pre_pix) { m_preFilterPix = pre_pix; }
    QPixmap preFilterPix() const { return m_preFilterPix; }

Q_SIGNALS:
    void filterClicked(int section);

protected:
    virtual void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const;

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent* e);
    bool event(QEvent* e);

private:
    QRect getFilterRect(const QRect& rect) const;

private:
    QPixmap m_norFilterPix;
    QPixmap m_hovFilterPix;
    QPixmap m_preFilterPix;

    int m_hover = -1;
    int m_press = -1;
};

#endif // FILTERHEADERVIEW_H
