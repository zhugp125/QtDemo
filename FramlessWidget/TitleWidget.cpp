#include "TitleWidget.h"
#include <QLabel>
#include <QToolButton>
#include <QHBoxLayout>
#include <QStyle>
#include <QMouseEvent>

CTitleWidget::CTitleWidget(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);

    QHBoxLayout* pMainLayout = new QHBoxLayout(this);
    pMainLayout->setMargin(0);
    setLayout(pMainLayout);

    m_pTitleLabel = new QLabel(this);
    pMainLayout->addWidget(m_pTitleLabel);
    pMainLayout->addStretch();

    m_pMinButton = new QToolButton(this);
    m_pMinButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMinButton));
    pMainLayout->addWidget(m_pMinButton);

    m_pMaxButton = new QToolButton(this);
    m_pMaxButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarMaxButton));
    pMainLayout->addWidget(m_pMaxButton);

    m_pCloseButton = new QToolButton(this);
    m_pCloseButton->setIcon(style()->standardIcon(QStyle::SP_TitleBarCloseButton));
    pMainLayout->addWidget(m_pCloseButton);

    connect(m_pMinButton, &QAbstractButton::clicked, this, &CTitleWidget::signalMin);
    connect(m_pMaxButton, &QAbstractButton::clicked, this, &CTitleWidget::signalMax);
    connect(m_pCloseButton, &QAbstractButton::clicked, this, &CTitleWidget::signalClose);
}

void CTitleWidget::setTitle(const QString &title)
{
    if (m_pTitleLabel != nullptr)
    {
        m_pTitleLabel->setText(title);
    }
}

void CTitleWidget::mouseMoveEvent(QMouseEvent *event)
{
    event->ignore();
}
