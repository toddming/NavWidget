#include "scrollitem.h"


ScrollItem::ScrollItem(QWidget* parent)
    : QWidget{parent}
{
    setProperty("alpha", 0);

    _themeMode = eTheme->getThemeMode();
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        _themeMode = themeMode;
    });
}


void ScrollItem::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(_themeMode == ElaThemeType::Dark ?QColor(0xFF, 0xFF, 0xFF, m_alpha) : QColor(0, 0, 0, m_alpha));
    QRect foregroundRect(1, 1, width() - 2, height() - 2);
    painter.drawRoundedRect(foregroundRect, _pBorderRadius, _pBorderRadius);
    painter.restore();
}

bool ScrollItem::event(QEvent* event)
{
    switch (event->type())
    {
    case QEvent::Enter:
    {
        startAlphaAnimation(_themeMode == ElaThemeType::Dark ? 100 : 50);
        break;
    }
    case QEvent::Leave:
    {
        startAlphaAnimation(0);
        break;
    }
    default:
    {
        break;
    }
    }
    return QWidget::event(event);
}

void ScrollItem::startAlphaAnimation(int targetAlpha) {
    QPropertyAnimation* animation = new QPropertyAnimation(this, "alpha");
    connect(animation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
        m_alpha = value.toReal();
        update();
    });
    animation->setDuration(200);
    animation->setStartValue(m_alpha);
    animation->setEndValue(targetAlpha);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
