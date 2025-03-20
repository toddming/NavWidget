#include "scrollrect.h"

#include <QPainter>

ScrollRect::ScrollRect(QWidget* parent)
    : QWidget{parent}
{
    _themeMode = eTheme->getThemeMode();
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        _themeMode = themeMode;
    });
}

void ScrollRect::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(_themeMode == ElaThemeType::Dark ? QColor(0xFF, 0xFF, 0xFF, 60) : QColor(0, 0, 0, 12));
    QRect foregroundRect(1, 1, width() - 2, height() - 2);
    painter.drawRoundedRect(foregroundRect, _pBorderRadius, _pBorderRadius);
    painter.restore();
}
