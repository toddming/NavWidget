#ifndef SCROLLRECT_H
#define SCROLLRECT_H

#include <QWidget>

#include "ElaTheme.h"

class ScrollRect : public QWidget
{
public:
    explicit ScrollRect(QWidget* parent = nullptr);

protected:
    virtual void paintEvent(QPaintEvent* event) override;

private:
    ElaThemeType::ThemeMode _themeMode;

    int _pBorderRadius{4};
};

#endif // SCROLLRECT_H
