QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include("install/share/QWindowKit/qmake/QWKWidgets.pri")
INCLUDEPATH += widgettools/include

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    navbar.cpp \
    widgetframe/windowbar.cpp \
    widgetframe/windowbutton.cpp \
    widgettools/ElaText.cpp \
    widgettools/ElaTheme.cpp \
    widgettools/ElaToggleButton.cpp \
    widgettools/ElaToggleSwitch.cpp \
    widgettools/private/ElaTextPrivate.cpp \
    widgettools/private/ElaThemePrivate.cpp \
    widgettools/private/ElaToggleButtonPrivate.cpp \
    widgettools/private/ElaToggleSwitchPrivate.cpp

HEADERS += \
    mainwindow.h \
    navbar.h \
    widgetframe/windowbar.h \
    widgetframe/windowbar_p.h \
    widgetframe/windowbutton.h \
    widgetframe/windowbutton_p.h \
    widgettools/include/Def.h \
    widgettools/include/ElaText.h \
    widgettools/include/ElaTheme.h \
    widgettools/include/ElaToggleButton.h \
    widgettools/include/ElaToggleSwitch.h \
    widgettools/include/singleton.h \
    widgettools/include/stdafx.h \
    widgettools/private/ElaTextPrivate.h \
    widgettools/private/ElaThemePrivate.h \
    widgettools/private/ElaToggleButtonPrivate.h \
    widgettools/private/ElaToggleSwitchPrivate.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources/shared.qrc
