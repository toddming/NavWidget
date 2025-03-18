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
#include <QTimer>

#include <QWKWidgets/widgetwindowagent.h>
#include <widgetframe/windowbar.h>
#include <widgetframe/windowbutton.h>
#include "navbar.h"
#include "widgettools/ElaToggleSwitch.h"
#include "widgettools/ElaText.h"
#include "widgettools/ElaTheme.h"


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

    NavBar *navBar{nullptr};

    QStackedWidget *stackedWidget{nullptr};

};
#endif // MAINWINDOW_H
