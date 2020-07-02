#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    int fontId = QFontDatabase::addApplicationFont("E:/Hades_Work/LCD_KEY/qt/keyBoard/font/NotoSansHans-Medium.otf");
    QString msyh = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(msyh);
    QApplication::setFont(font);

    MainWindow w;
    w.setFont(font);
    w.show();

    return a.exec();
}
