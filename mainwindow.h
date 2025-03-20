#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QTimer>
#include <QFile>
#include <QPainter>
#include <QPushButton>
#include <QCoreApplication>
#include <QGuiApplication>
#include <QStyle>
#include <QDebug>
#include <QTimer>

#include <QWKWidgets/widgetwindowagent.h>
#include <widgetframe/windowbar.h>
#include <widgetframe/windowbutton.h>
#include "centerwindow.h"
#include "ElaToggleSwitch.h"
#include "ElaText.h"
#include "ElaTheme.h"

#include "customtools/scrollwidget.h"
#include "subpage/p_home.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool event(QEvent *event) override;

private:
    void installWindowAgent();

    void initUI();

    void loadStyleSheet(ElaThemeType::ThemeMode theme);

    QWK::WidgetWindowAgent *windowAgent;

    QStackedWidget *stackedWidget{nullptr};

};
#endif // MAINWINDOW_H
