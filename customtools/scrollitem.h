#ifndef SCROLLITEM_H
#define SCROLLITEM_H

#include <QWidget>
#include <QEvent>
#include <QPainter>
#include <QPropertyAnimation>

#include "ElaTheme.h"

class ScrollItem : public QWidget
{
public:
    explicit ScrollItem(QWidget* parent = nullptr);

protected:
    virtual bool event(QEvent* event) override;

    virtual void paintEvent(QPaintEvent* event) override;

private:
    ElaThemeType::ThemeMode _themeMode;

    int _pBorderRadius{4};

    qreal m_alpha{0};

    void startAlphaAnimation(int targetAlpha);

};

#endif // SCROLLITEM_H
