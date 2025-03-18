#include "navbar.h"


NavBar::NavBar(QWidget *parent) : QFrame(parent)
{
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(true);
    connect(buttonGroup, &QButtonGroup::buttonClicked,
            this, &NavBar::on_btnGroup_clicked);

    changeTheme(eTheme->getThemeMode());

    connect(eTheme, &ElaTheme::themeModeChanged, this, &NavBar::changeTheme);
}

void NavBar::paintEvent(QPaintEvent *event)
{
    if (_type != NavNone) {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(Qt::NoPen);
        int radius = 21;
        QRect _rect = rect().adjusted(-1, -1, 1, 1);

        if (_y1 * _y2 > 0) {
            QRect r1(0, 0, _rect.width(), _y1);
            QRect r2(0, _y2, _rect.width(), _rect.height() - _y2);

            QPainterPath path1;
            path1.moveTo(r1.topLeft());
            path1.lineTo(r1.topRight());
            path1.lineTo(r1.bottomRight() - QPointF(0, radius));
            path1.quadTo(r1.bottomRight(), r1.bottomRight() - QPointF(radius, 0));
            path1.lineTo(r1.bottomLeft());
            path1.closeSubpath();
            painter.fillPath(path1, cover_color);

            QPainterPath path2;
            path2.moveTo(r2.topLeft());
            path2.lineTo(r2.bottomLeft());
            path2.lineTo(r2.bottomRight());
            path2.lineTo(r2.topRight() + QPointF(0, radius));
            path2.quadTo(r2.topRight(), r2.topRight() - QPointF(radius, 0));
            path2.closeSubpath();
            painter.fillPath(path2, cover_color);
        } else if (_x1 * _x2 > 0) {
            QRect r1(0, 0, _x1, _rect.height());
            QRect r2(_x2, 0, _rect.width() - _x2, _rect.height());

            QPainterPath path1;
            path1.moveTo(r1.topLeft());
            path1.lineTo(r1.topRight());
            path1.lineTo(r1.bottomRight() - QPointF(0, radius));
            path1.quadTo(r1.bottomRight(), r1.bottomRight() - QPointF(radius, 0));
            path1.lineTo(r1.bottomLeft());
            path1.closeSubpath();
            painter.fillPath(path1, cover_color);

            QPainterPath path2;
            path2.moveTo(r2.topLeft());
            path2.lineTo(r2.topRight());
            path2.lineTo(r2.bottomRight());
            path2.lineTo(r2.bottomLeft() + QPointF(radius, 0));
            path2.quadTo(r2.bottomLeft(), r2.bottomLeft() - QPointF(0, radius));
            path2.closeSubpath();
            painter.fillPath(path2, cover_color);
        } else {
            QPainterPath path;
            path.moveTo(_rect.topLeft());
            path.lineTo(_rect.topRight());
            path.lineTo(_rect.bottomRight());
            path.lineTo(_rect.bottomLeft());
            path.closeSubpath();
            painter.fillPath(path, cover_color);
        }
    }
    QFrame::paintEvent(event);
}

bool NavBar::initNavBar(NavType type, const QStringList &btnList)
{
    int count = btnList.count();
    if (count < 1 || h_lay != nullptr || v_lay != nullptr)
        return false;
    _type = type;
    if (type == NavTop) {
        h_lay = new QHBoxLayout(this);
        h_lay->setContentsMargins(0, 0, 0, 0);
        h_lay->setSpacing(0);
        h_lay->addStretch();
        foreach (const QString &text, btnList) {
            QPushButton *btn = new QPushButton(text, this);
            btn->setCheckable(true);
            btn->setFixedWidth(80);
            h_lay->addWidget(btn);
            buttonGroup->addButton(btn);
        }
        h_lay->addStretch();
    } else if (type == NavLeft) {
        v_lay = new QVBoxLayout(this);
        v_lay->setContentsMargins(0, 0, 0, 0);
        v_lay->setSpacing(0);
        v_lay->addStretch();
        foreach (const QString &text, btnList) {
            QPushButton *btn = new QPushButton(text, this);
            btn->setCheckable(true);
            btn->setFixedHeight(50);
            v_lay->addWidget(btn);
            buttonGroup->addButton(btn);
        }
        v_lay->addStretch();
    }
    return true;
}

void NavBar::handleResize()
{
    if (checkedButton != nullptr) {
        if (_type == NavLeft) {
            _y1 = checkedButton->pos().y();
            _y2 = _y1 + checkedButton->height();
        } else if (_type == NavTop) {
            _x1 = checkedButton->x();
            _x2 = _x1 + checkedButton->width();
        }
        update();
    }
}

void NavBar::on_btnGroup_clicked(QAbstractButton *btn)
{
    checkedButton = btn;
    if (checkedButton != nullptr) {
        if (_type == NavLeft) {
            _y1 = checkedButton->pos().y();
            _y2 = _y1 + checkedButton->height();
        } else if (_type == NavTop) {
            _x1 = checkedButton->x();
            _x2 = _x1 + checkedButton->width();
        }
    }
    update();
}

void NavBar::changeTheme(ElaThemeType::ThemeMode theme) {
    if (theme == ElaThemeType::Dark) {
        cover_color = QColor(255, 255, 255, 30);
        QString qss = "QFrame{background-color:transparent;}"
                       "QPushButton{background-color:transparent;border-style:none;color:#D1D1D1;font: 12pt \"Microsoft YaHei\";}"
                       "QPushButton:checked{color:white;}";
        setStyleSheet(qss);
    } else {
        cover_color = QColor(0, 0, 0, 10);
        QString qss = "QFrame{background-color:transparent;}"
                       "QPushButton{background-color:transparent;border-style:none;color:#808080;font: 12pt \"Microsoft YaHei\";}"
                       "QPushButton:checked{color:black;}";
        setStyleSheet(qss);
    }
}
