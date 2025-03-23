#include "checkgroup.h"

#include <QPainterPath>
#include <QDebug>
CheckGroup::CheckGroup(const QStringList &items, QWidget* parent)
    : QWidget{parent}
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);

    _pBorderRadius = 7;

    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(true);
    connect(buttonGroup, &QButtonGroup::buttonClicked,
            this, &CheckGroup::on_btnGroup_clicked);


    QHBoxLayout *lay = new QHBoxLayout(this);
    lay->setSpacing(0);
    lay->setContentsMargins(0, 2, 0, 2);

    for (int i=0; i < items.count(); i++) {
        QPushButton *btn = new QPushButton(items[i], this);
        btn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        btn->setCheckable(true);
        buttonGroup->addButton(btn, i);
        lay->addWidget(btn);
    }

    _themeMode = eTheme->getThemeMode();
    setStyleSheet(QString("QPushButton{background-color:transparent;border-style:none;color:%1; font-size: 12px;"
                          "padding-top: 4px; padding-right: 8px; padding-bottom: 4px; padding-left: 8px;}")
                      .arg("white"));

    connect(eTheme, &ElaTheme::themeModeChanged, this, [=](ElaThemeType::ThemeMode themeMode) {
        _themeMode = themeMode;
    });
    m_rect = QRect(0, 0, 0, height());
}

void CheckGroup::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    painter.setRenderHints(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

    QList<QAbstractButton*> btns = buttonGroup->buttons();
    for (int i=0; i < btns.count(); i++) {
        QAbstractButton *btn = btns.at(i);
        QRect _rect(btn->pos().x(), btn->pos().y(), btn->width(), btn->height());
        _rect = _rect.adjusted(0, 0, 1, 1);
        bool _first = i == 0;
        bool _last = i == btns.count() - 1;
        bool _checked = btn == checkedButton;
        if (_checked && _rect == m_rect)
            continue;
        QColor _color;
        if (_themeMode == ElaThemeType::Dark) {
            _color = i % 2 == 0 ? QColor("#332F2F") : QColor("#413C3C");
        } else {
            _color = i % 2 == 0 ? QColor("#BDB3B3") : QColor("#C7BFBF");
        }

        if (_first) {
            QPainterPath path;
            path.moveTo(_rect.topRight());
            path.lineTo(_rect.bottomRight());
            path.lineTo(_rect.x() + _pBorderRadius, _rect.bottom());
            path.quadTo(_rect.bottomLeft(), _rect.bottomLeft() - QPointF(0, _pBorderRadius));
            path.lineTo(_rect.topLeft() + QPointF(0, _pBorderRadius));
            path.quadTo(_rect.topLeft(), _rect.topLeft() + QPointF(_pBorderRadius, 0));
            path.closeSubpath();
            painter.fillPath(path, _color);
        } else if (_last) {
            QPainterPath path;
            path.moveTo(_rect.topLeft());
            path.lineTo(_rect.bottomLeft());
            path.lineTo(_rect.bottomRight() - QPointF(_pBorderRadius, 0));
            path.quadTo(_rect.bottomRight(), _rect.bottomRight() + QPointF(0, -_pBorderRadius));
            path.lineTo(_rect.topRight() + QPointF(0, _pBorderRadius));
            path.quadTo(_rect.topRight(), _rect.topRight() - QPointF(_pBorderRadius, 0));
            path.closeSubpath();
            painter.fillPath(path, _color);
        } else {
            QPainterPath path;
            path.moveTo(_rect.topRight());
            path.lineTo(_rect.bottomRight());
            path.lineTo(_rect.bottomLeft());
            path.lineTo(_rect.topLeft());
            path.closeSubpath();
            painter.fillPath(path, _color);
        }
    }

    if (checkedButton != nullptr) {
        QColor _color = QColor("#179BBB");
        bool _first = btns.indexOf(checkedButton) == 0;
        bool _last = btns.indexOf(checkedButton) == btns.count() - 1;

        if (_first) {
            QPainterPath path;
            path.moveTo(m_rect.topRight());
            path.lineTo(m_rect.bottomRight());
            path.lineTo(m_rect.x() + _pBorderRadius, m_rect.bottom());
            path.quadTo(m_rect.bottomLeft(), m_rect.bottomLeft() - QPointF(0, _pBorderRadius));
            path.lineTo(m_rect.topLeft() + QPointF(0, _pBorderRadius));
            path.quadTo(m_rect.topLeft(), m_rect.topLeft() + QPointF(_pBorderRadius, 0));
            path.closeSubpath();
            painter.fillPath(path, _color);
        } else if (_last) {
            QPainterPath path;
            path.moveTo(m_rect.topLeft());
            path.lineTo(m_rect.bottomLeft());
            path.lineTo(m_rect.bottomRight() - QPointF(_pBorderRadius, 0));
            path.quadTo(m_rect.bottomRight(), m_rect.bottomRight() + QPointF(0, -_pBorderRadius));
            path.lineTo(m_rect.topRight() + QPointF(0, _pBorderRadius));
            path.quadTo(m_rect.topRight(), m_rect.topRight() - QPointF(_pBorderRadius, 0));
            path.closeSubpath();
            painter.fillPath(path, _color);
        } else {
            QPainterPath path;
            path.moveTo(m_rect.topRight());
            path.lineTo(m_rect.bottomRight());
            path.lineTo(m_rect.bottomLeft());
            path.lineTo(m_rect.topLeft());
            path.closeSubpath();
            painter.fillPath(path, _color);
        }
    }
    QWidget::paintEvent(event);
}

void CheckGroup::on_btnGroup_clicked(QAbstractButton *btn)
{
    checkedButton = btn;

    QRect _rect(btn->pos().x(), btn->pos().y(), btn->width(), btn->height());

    startRectAnimation(_rect.adjusted(0, 0, 1, 1));
}

QRect CheckGroup::myRect() const {
    return m_rect;
}

void CheckGroup::setMyRect(const QRect &value) {
    if (m_rect != value) {
        m_rect = value;
        emit myRectChanged();
    }
}

void CheckGroup::startRectAnimation(QRect targetRect) {
    QPropertyAnimation* animation = new QPropertyAnimation(this, "myRect");
    connect(animation, &QPropertyAnimation::valueChanged, this, [=](const QVariant& value) {
        m_rect = value.toRect();
        update();
    });
    animation->setDuration(100);
    animation->setStartValue(m_rect);
    animation->setEndValue(targetRect);
    animation->start(QAbstractAnimation::DeleteWhenStopped);
}
