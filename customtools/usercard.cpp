#include "usercard.h"

#include <QDebug>
UserCard::UserCard(QWidget* parent)
    : QWidget{parent}
{
    setMouseTracking(true);

    _pBorderRadius = 10;
    _pCardPixMode = ElaCardPixType::PixMode::Ellipse;
    _pCardPixmapSize.setWidth(46);
    _pCardPixmapSize.setHeight(46);
    _pCardPixmap.load(":/app/head.png");
    _pCardPixmap = _pCardPixmap.scaled(_pCardPixmapSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    _themeMode = eTheme->getThemeMode();
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        _themeMode = themeMode;
    });
}

void UserCard::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QRect _rect = rect().adjusted(6, 6, -6, -6);
    QRect _pic_rect = QRect(10, (height() - _pCardPixmapSize.height()) / 2, _pCardPixmapSize.width(), _pCardPixmapSize.height());

    QPainter painter(this);
    painter.save();
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);
    painter.setBrush(_themeMode == ElaThemeType::Dark ? isEnter ? QColor(0xFF, 0xFF, 0xFF, 25) : Qt::transparent : isEnter ? QColor(0, 0, 0, 25) : Qt::transparent);
    painter.drawRoundedRect(_rect, _pBorderRadius, _pBorderRadius);

    if (!_pCardPixmap.isNull()) {
        painter.save();
        QPainterPath path;

        if (_pCardPixMode == ElaCardPixType::PixMode::Ellipse) {
            path.addEllipse(QPointF(_pCardPixmapSize.width() / 2 + 10, height() / 2), _pCardPixmapSize.width() / 2, _pCardPixmapSize.height() / 2);
            painter.setClipPath(path);
            painter.drawPixmap(_pic_rect, _pCardPixmap);
        } else if (_pCardPixMode == ElaCardPixType::PixMode::Default) {
            painter.drawPixmap(_pic_rect, _pCardPixmap);
        } else if (_pCardPixMode == ElaCardPixType::PixMode::RoundedRect) {
            path.addRoundedRect(_pic_rect, _pBorderRadius, _pBorderRadius);
            painter.setClipPath(path);
            painter.drawPixmap(_pic_rect, _pCardPixmap);
        }
        painter.restore();
    }
    // 文字绘制
    painter.setPen(ElaThemeColor(_themeMode, BasicText));
    QFont font = this->font();
    font.setWeight(QFont::Bold);
    font.setPixelSize(13);
    painter.setFont(font);
    int textStartX = _pCardPixmapSize.width() + 20;
    int textWidth = _rect.width() - textStartX;
    painter.drawText(QRect(textStartX, _pic_rect.y(), textWidth, _pic_rect.height() / 2), Qt::TextWordWrap | Qt::AlignBottom | Qt::AlignLeft, "Admin");
    font.setWeight(QFont::Normal);
    font.setPixelSize(12);
    painter.setFont(font);
    painter.drawText(QRect(textStartX, _pic_rect.y() + _pic_rect.height() / 2, textWidth, _pic_rect.height() / 2), Qt::TextWordWrap | Qt::AlignTop | Qt::AlignLeft, "本地账户");
    painter.restore();
}

bool UserCard::event(QEvent* event)
{
    switch (event->type())
    {
    case QEvent::Enter: {
        if (!isEnter) {
            isEnter = true;
            update();
        }
    }
        break;
    case QEvent::Leave: {
        if (isEnter) {
            isEnter = false;
            update();
        }
    }
        break;
    case QEvent::MouseMove:
    {
        break;
    }
    case QEvent::MouseButtonPress: {
        if (!isPress) {
            isPress = true;
            update();
        }
    }
        break;
    case QEvent::MouseButtonRelease: {
        if (isPress) {
            isPress = false;
            update();
        }
    }
        break;
    default:
    {
        break;
    }
    }
    return QWidget::event(event);
}
