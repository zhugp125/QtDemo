#include "widget.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/style_sheet.qss");
    if (file.open(QIODevice::ReadOnly))
    {
        a.setStyleSheet(file.readAll());
    }

    Widget w;
    w.show();

    return a.exec();
}
