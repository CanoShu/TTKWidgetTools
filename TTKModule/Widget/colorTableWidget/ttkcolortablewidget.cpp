#include "ttkcolortablewidget.h"

#include <QFile>
#include <QDebug>
TTKColorTableWidget::TTKColorTableWidget(QWidget *parent)
    : QListWidget(parent)
{

}

void TTKColorTableWidget::init()
{
    QFile file(":/res/rgb");
    if(file.open(QFile::ReadOnly))
    {
#ifdef Q_OS_WIN
        QStringList items(QString(file.readAll()).split("\r\n"));
#else
        QStringList items(QString(file.readAll()).split("\n"));
#endif
        foreach(const QString &item, items)
        {
            QListWidgetItem *it = new QListWidgetItem(this);
            it->setText(item);

            QRegExp regx("RGB\\[(\\d+),(\\d+),(\\d+)\\]");
            int pos = item.indexOf(regx);
            while(pos != -1)
            {
                it->setBackground(QColor(regx.cap(1).toInt(),
                                         regx.cap(2).toInt(),
                                         regx.cap(3).toInt()));
                pos += regx.matchedLength();
                pos = regx.indexIn(item, pos);
            }
            addItem(it);
        }
        file.close();
    }
}
