QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include("install/share/QWindowKit/qmake/QWKWidgets.pri")
INCLUDEPATH += widgettools/include

SOURCES += \
    centerwindow.cpp \
    customtools/checkgroup.cpp \
    customtools/hlineedit.cpp \
    customtools/scrollitem.cpp \
    customtools/scrollrect.cpp \
    customtools/scrollwidget.cpp \
    customtools/usercard.cpp \
    main.cpp \
    mainwindow.cpp \
    subpage/p_home.cpp \
    widgetframe/windowbar.cpp \
    widgetframe/windowbutton.cpp \
    widgettools/DeveloperComponents/ElaMenuStyle.cpp \
    widgettools/DeveloperComponents/ElaScrollBarStyle.cpp \
    widgettools/ElaMenu.cpp \
    widgettools/ElaPushButton.cpp \
    widgettools/ElaScrollArea.cpp \
    widgettools/ElaScrollBar.cpp \
    widgettools/ElaText.cpp \
    widgettools/ElaTheme.cpp \
    widgettools/ElaToggleButton.cpp \
    widgettools/ElaToggleSwitch.cpp \
    widgettools/private/ElaMenuPrivate.cpp \
    widgettools/private/ElaPushButtonPrivate.cpp \
    widgettools/private/ElaScrollAreaPrivate.cpp \
    widgettools/private/ElaScrollBarPrivate.cpp \
    widgettools/private/ElaTextPrivate.cpp \
    widgettools/private/ElaThemePrivate.cpp \
    widgettools/private/ElaToggleButtonPrivate.cpp \
    widgettools/private/ElaToggleSwitchPrivate.cpp

HEADERS += \
    centerwindow.h \
    customtools/checkgroup.h \
    customtools/hlineedit.h \
    customtools/scrollitem.h \
    customtools/scrollrect.h \
    customtools/scrollwidget.h \
    customtools/usercard.h \
    mainwindow.h \
    subpage/p_home.h \
    widgetframe/windowbar.h \
    widgetframe/windowbar_p.h \
    widgetframe/windowbutton.h \
    widgetframe/windowbutton_p.h \
    widgettools/DeveloperComponents/ElaMenuStyle.h \
    widgettools/DeveloperComponents/ElaScrollBarStyle.h \
    widgettools/include/Def.h \
    widgettools/include/ElaMenu.h \
    widgettools/include/ElaPushButton.h \
    widgettools/include/ElaScrollArea.h \
    widgettools/include/ElaScrollBar.h \
    widgettools/include/ElaText.h \
    widgettools/include/ElaTheme.h \
    widgettools/include/ElaToggleButton.h \
    widgettools/include/ElaToggleSwitch.h \
    widgettools/include/singleton.h \
    widgettools/include/stdafx.h \
    widgettools/private/ElaMenuPrivate.h \
    widgettools/private/ElaPushButtonPrivate.h \
    widgettools/private/ElaScrollAreaPrivate.h \
    widgettools/private/ElaScrollBarPrivate.h \
    widgettools/private/ElaTextPrivate.h \
    widgettools/private/ElaThemePrivate.h \
    widgettools/private/ElaToggleButtonPrivate.h \
    widgettools/private/ElaToggleSwitchPrivate.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/shared.qrc

RC_ICONS = logo.ico
