#include "widget.h"
#include <QMetaObject>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    btn = new QPushButton("btn", this);
    btn->resize(120, 40);
    btn->move(20, 20);

    const QMetaObject *obj = this->metaObject();
    qDebug() << "class name  " << obj->className();
    qDebug() << "super class name  " << obj->superClass()->className();

    for(int i = obj->methodOffset(); i < obj->methodCount(); ++i)
    {
        QMetaMethod method = obj->method(i);
        QString funcName;
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
        funcName = QString::fromLatin1(method.signature());
#else
        funcName = QString::fromLatin1(method.methodSignature());
#endif
        if(method.methodType() == QMetaMethod::Signal)
        {
            qDebug() << "signal  " << funcName;
        }
        else if(method.methodType() == QMetaMethod::Slot)
        {
            qDebug() << "slot   " << funcName;
            methods.insert(funcName, method);
        }
    }

    connect(btn, SIGNAL(clicked(bool)), this, SLOT(onBtnClicked()));
}

Widget::~Widget()
{

}

void Widget::onBtnClicked()
{
    qDebug() << "onBtnClicked()" << "\n";
    auto it = methods.find("onText()");
    if(it != methods.end())
    {
        it.value().invoke(this);
    }
}

void Widget::onText()
{
    qDebug() << "onText()";
}
