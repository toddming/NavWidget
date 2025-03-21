#ifndef USERCARD_H
#define USERCARD_H

#include <QWidget>
#include <QEvent>
#include <QPainter>
#include <QPixmap>
#include <QPainterPath>

#include "Def.h"
#include "ElaTheme.h"

class UserCard : public QWidget
{
public:
    explicit UserCard(QWidget* parent = nullptr);

protected:
    virtual bool event(QEvent* event) override;

    virtual void paintEvent(QPaintEvent* event) override;

private:
    ElaThemeType::ThemeMode _themeMode;

    int _pBorderRadius;

    bool isEnter{false};

    bool isPress{false};

    QPixmap _pCardPixmap;

    QSize _pCardPixmapSize;

    ElaCardPixType::PixMode _pCardPixMode;
};

#endif // USERCARD_H
