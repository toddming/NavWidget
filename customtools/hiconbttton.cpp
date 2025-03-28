#include "hiconbttton.h"


HIconBttton::HIconBttton(ElaIconType::IconName icon, const QString &text, QWidget *parent) : QToolButton(parent)
{
    setText(text);

    _pElaIcon = icon;

    QCursor handCursor(Qt::PointingHandCursor);
    setCursor(handCursor);

    setStyleSheet("background-color:transparent;border-style:none;");

    _themeMode = eTheme->getThemeMode();
    connect(eTheme, &ElaTheme::themeModeChanged, this, &HIconBttton::changeTheme);

}

void HIconBttton::changeTheme(ElaThemeType::ThemeMode theme) {
    _themeMode = theme;
    update();
}

void HIconBttton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    if (_themeMode == ElaThemeType::Dark) {
        painter.setPen(isChecked() ? Qt::white : QColor("#D1D1D1"));
    } else {
        painter.setPen(isChecked() ? Qt::black : QColor("#808080"));
    }
    painter.setFont(this->font());
    QFontMetrics metrics(this->font());
    QRect textRect = metrics.boundingRect(this->text());
    textRect = textRect.adjusted(-4, -2, 4, 2);
    int x = (this->width() - textRect.width()) / 2;
    int y = (this->height() - textRect.height()) / 2;
    textRect.moveTo(x, y);

    painter.drawText(textRect, Qt::AlignCenter, this->text());

    int _h = textRect.height();
    QFont iconFont = QFont("ElaAwesome");
    iconFont.setPixelSize(_h * 0.57);
    painter.setFont(iconFont);
    painter.drawText(QRect(textRect.x()-_h, textRect.y(), _h, _h), Qt::AlignCenter, QChar((unsigned short)_pElaIcon));
}
