#include "widget.h"
#include <QApplication>
#include <QString>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    w.setWindowTitle(QString::fromLocal8Bit("网关配置程序"));
    return a.exec();
}
