#include "dropwidget.h"
#include "ui_dropwidget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QDebug>

DropWidget::DropWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DropWidget)
{
    ui->setupUi(this);
    setAcceptDrops(true);
}

DropWidget::~DropWidget()
{
    delete ui;
}

void DropWidget::setBackgroundColor(const QString &background_color)
{
    m_background_color = background_color;
}

QString DropWidget::backgroundColor() const
{
    return m_background_color;
}

void DropWidget::setLable(const QString &label)
{
    ui->label->setText(label);
}

void DropWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(rect(), QColor(m_background_color));
    QWidget::paintEvent(event);
}

void DropWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "********* mousePressEvent " << event->pos();
    m_start_pos = event->pos();
    QWidget::mousePressEvent(event);
}

void DropWidget::mouseMoveEvent(QMouseEvent *event)
{
    qDebug() << "********* mouseMoveEvent " << event->pos();
    if ((event->pos() - m_start_pos).manhattanLength() >= QApplication::startDragDistance())
    {
        performDrag();
    }
    QWidget::mouseMoveEvent(event);
}

void DropWidget::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "********* mouseReleaseEvent " << event->pos();
    QWidget::mouseReleaseEvent(event);
}

void DropWidget::dragMoveEvent(QDragMoveEvent *event)
{
    qDebug() << "********* dragMoveEvent " << event->pos();
    DropWidget* source = qobject_cast<DropWidget*>(event->source());
    if (source && source != this)
    {
        event->setDropAction(Qt::MoveAction);
    }
    event->acceptProposedAction();
    QWidget::dragMoveEvent(event);
}

void DropWidget::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug() << "********* dragEnterEvent " << event->pos();
    DropWidget* source = qobject_cast<DropWidget*>(event->source());
    if (source && source != this)
    {
        event->setDropAction(Qt::MoveAction);
    }
    event->acceptProposedAction();
    QWidget::dragEnterEvent(event);
}

void DropWidget::dropEvent(QDropEvent *event)
{
    qDebug() << "********* dropEvent " << event->pos();
    setCursor(Qt::ArrowCursor);
    DropWidget* source = qobject_cast<DropWidget*>(event->source());
    if (source && source != this)
    {
        QRect source_rect = source->geometry();
        QRect this_rect = this->geometry();
        this->setGeometry(source_rect);
        source->setGeometry(this_rect);
        event->setDropAction(Qt::MoveAction);
    }
    event->acceptProposedAction();
    QWidget::dropEvent(event);
}

void DropWidget::performDrag()
{
    QDrag *drag = new QDrag(this);
    drag->setMimeData(new QMimeData);
    drag->setPixmap(QPixmap::grabWindow(winId()));
    drag->setHotSpot(QPoint(width() / 2, height() / 2));
    if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
        return;
}
