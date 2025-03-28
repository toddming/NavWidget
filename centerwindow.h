#ifndef CENTERWINDOW_H
#define CENTERWINDOW_H

#include <QObject>
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
#include <QStackedWidget>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>
#include <QDebug>

#include "ElaTheme.h"
#include "customtools/usercard.h"
#include "customtools/scrollwidget.h"
#include "customtools/hiconbttton.h"

class CenterWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CenterWindow(QWidget *parent = nullptr);

    void addPage(const QString &name, QWidget *widget);

protected:
    virtual void paintEvent(QPaintEvent *event) override;

    bool event(QEvent *event) override;

private slots:
    void on_btnGroup_clicked(QAbstractButton *btn);

    void changeTheme(ElaThemeType::ThemeMode theme);

private:
    QButtonGroup *buttonGroup;

    QVBoxLayout *btn_lay{nullptr};

    QStackedWidget *stackedWidget{nullptr};

    QColor cover_color;

    QAbstractButton* checkedButton{nullptr};

    ElaThemeType::ThemeMode _themeMode;

    UserCard *userCard{nullptr};

    int m_topy{0};
    int m_toph{80};
    int btn_w{150};
    int btn_h{45};

    void startTopyAnimation(int targetTopy);
};

#endif // CENTERWINDOW_H
