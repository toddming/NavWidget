#include "mainwindow.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
    QCoreApplication::setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);

    QApplication app(argc, argv);

    QFontDatabase::addApplicationFont("font/ElaAwesome.ttf");
    int fontId = QFontDatabase::addApplicationFont("font/AlimamaFangYuanTiVF-Thin.ttf");
    if(fontId >= 0)  {
        QFont font("阿里妈妈方圆体 VF Medium", -1);
        font.setPixelSize(12);
        font.setHintingPreference(QFont::PreferFullHinting);
        app.setFont(font);
    }

    MainWindow w;
    w.show();
    return app.exec();
}
