#include "htoolbutton.h"


HToolButton::HToolButton(const QString &text, bool underline, QWidget *parent) : QToolButton(parent)
{
    setText(text);

    m_underline = underline;

    setStyleSheet("background-color:transparent;border-style:none;"
                  "padding-top: 4px; padding-right: 4px; padding-bottom: 4px; padding-left: 4px;");

    QCursor handCursor(Qt::PointingHandCursor);
    setCursor(handCursor);

    _themeMode = eTheme->getThemeMode();
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        _themeMode = themeMode;
    });

}

void HToolButton::setUnderline(bool underline)
{
    m_underline = underline;
}

void HToolButton::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(_themeMode == ElaThemeType::Dark ? QColor("#D4D4D4") : QColor("#747D88"));

    QFont font = this->font();
    font.setPointSize(10);
    painter.setFont(font);
    QFontMetrics metrics(font);
    QRect textRect = metrics.boundingRect(this->text());

    int x = (this->width() - textRect.width()) / 2;
    int y = (this->height() - textRect.height()) / 2;
    textRect.moveTo(x, y);

    painter.drawText(rect(), Qt::AlignCenter, text());

    if (m_underline) {
        QPen pen(ElaThemeColor(_themeMode, BasicText));
        QVector<qreal> dashPattern;
        dashPattern << 2 << 2;
        pen.setDashPattern(dashPattern);

        painter.setPen(pen);
        painter.drawLine(textRect.bottomLeft() + QPointF(2, 5), textRect.bottomRight() + QPointF(2, 5));
    }
}
