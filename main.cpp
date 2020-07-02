#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    QString pathstr = QCoreApplication::applicationDirPath();
    QDir fontDir(pathstr);
    if(fontDir.exists("font"))
    {
        fontDir.cd("font");
        int fontId = QFontDatabase::addApplicationFont(fontDir.path() + "/NotoSansHans-Medium.otf");
        QString msyh = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont font(msyh);
        QApplication::setFont(font);
        w.setFont(font);
    }
    else
    {
        QMessageBox::warning(&w,"Warning","font dir open error");
    }



    w.show();

    return a.exec();
}
