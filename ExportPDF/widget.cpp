#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QPrinter>
#include <QPainter>
#include <QTextBlock>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

QString Widget::readFile(const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly))
    {
        return file.readAll();
    }
    return "";
}

void Widget::htmlToPdf(const QString &fileName, const QString &html)
{
    QPrinter printer;
    printer.setPageSize(QPrinter::A4);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    QTextDocument document;
    document.setHtml(html);
    document.print(&printer);
    document.end();
}

void Widget::textToPdf(const QString &fileName, const QString &text)
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    QPainter painter;
    painter.begin(&printer);

    QPoint point(10, 10);
    for (const QString& msg : text.split("\n"))
    {
        point.ry() += 20;
        painter.drawText(point, msg);
    }

    //printer.newPage();  //生成新的一页，可继续插入
    painter.end();
}

void Widget::on_toolButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open", ".", "Images(*.png *.jpeg *.jpg);;Text files(*.txt);;HTML files(*.html *.htm)");
    if (fileName.isEmpty())
    {
        return;
    }
    ui->lineEdit->setText(fileName);

    QFileInfo fileInfo(fileName);
    QString pdfFileName = fileInfo.absolutePath() + "/" + fileInfo.baseName() + ".pdf";

    if (fileName.endsWith(".txt"))
    {
        ui->plainTextEdit->setPlainText(readFile(fileName));
        textToPdf(pdfFileName, readFile(fileName));
    }
    else if(fileName.endsWith(".html") || fileName.endsWith(".htm"))
    {
        ui->plainTextEdit->setPlainText(readFile(fileName));
        htmlToPdf(pdfFileName, readFile(fileName));
    }
    else
    {
        ui->plainTextEdit->setPlainText(fileName);
    }
}
