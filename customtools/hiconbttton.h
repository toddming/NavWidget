#ifndef HICONBTTTON_H
#define HICONBTTTON_H

#include <QToolButton>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>

#include "Def.h"
#include "ElaTheme.h"

class HIconBttton : public QToolButton
{
    Q_OBJECT
public:
    explicit HIconBttton(ElaIconType::IconName icon, const QString &text = "", QWidget *parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent* event) override;

private slots:
    void changeTheme(ElaThemeType::ThemeMode theme);


private:
    ElaThemeType::ThemeMode _themeMode;

    ElaIconType::IconName _pElaIcon;
};

#endif // HICONBTTTON_H
