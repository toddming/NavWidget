#ifndef NAVBAR_H
#define NAVBAR_H

#include <QObject>
#include <QFrame>
#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QAbstractButton>
#include <QButtonGroup>
#include <QMetaType>
#include <QPainterPath>
#include <QDebug>

#include "widgettools/ElaTheme.h"


enum NavType {
    NavLeft = 0,
    NavTop = 1,
    NavNone
};
Q_DECLARE_METATYPE(NavType)

class NavBar : public QFrame
{
    Q_OBJECT
public:
    explicit NavBar(QWidget *parent = nullptr);

    bool initNavBar(NavType type, const QStringList &btnList);

    void handleResize();

protected:
    virtual void paintEvent(QPaintEvent *event) override;

private slots:
    void on_btnGroup_clicked(QAbstractButton *btn);

    void changeTheme(ElaThemeType::ThemeMode theme);

private:
    QButtonGroup *buttonGroup;

    QVBoxLayout *v_lay{nullptr};

    QHBoxLayout *h_lay{nullptr};

    NavType _type{NavNone};

    QColor cover_color;

    QAbstractButton* checkedButton{nullptr};

    int _x1{0};
    int _x2{0};
    int _y1{0};
    int _y2{0};
};

#endif // NAVBAR_H
