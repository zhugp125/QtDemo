#include "widget.h"
#include <QPushButton>
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include "Wating.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_pButton = new QPushButton("wating 10s", this);
    m_pButton->move(20, 20);
    connect(m_pButton, &QAbstractButton::clicked, this, [=](){
        if (nullptr == m_pWating)
        {
            m_pWating = new CWating(this);
            m_pWating->setMessage("Wating for some minute");
        }
        QTimer::singleShot(10 * 1000, m_pWating, &CWating::stop);
        m_pWating->start();
        m_pWating->exec();
    });
}

Widget::~Widget()
{
    if (m_pWating != nullptr)
    {
        delete m_pWating;
        m_pWating = nullptr;
    }
}
