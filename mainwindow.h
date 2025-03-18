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
#include <QHBoxLayout>
#include <QStackedWidget>

#include <QWKWidgets/widgetwindowagent.h>
#include <widgetframe/windowbar.h>
#include <widgetframe/windowbutton.h>
#include "navbar.h"
#include "widgettools/ElaToggleSwitch.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum Theme {
        Dark,
        Light,
    };
    Q_ENUM(Theme)

Q_SIGNALS:
    void themeChanged();

protected:
    bool event(QEvent *event) override;

private:
    void installWindowAgent();

    void initUI();

    void loadStyleSheet(Theme theme);

    Theme currentTheme{};

    QWK::WidgetWindowAgent *windowAgent;

    NavBar *navBar{nullptr};

    QStackedWidget *stackedWidget{nullptr};

};
#endif // MAINWINDOW_H
