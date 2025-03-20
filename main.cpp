#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font = a.font();
    font.setPixelSize(13);
    font.setFamily("Microsoft YaHei UI");
    font.setHintingPreference(QFont::PreferDefaultHinting);
    a.setFont(font);

    MainWindow w;
    w.show();
    return a.exec();
}
