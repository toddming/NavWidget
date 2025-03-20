#include "centerwindow.h"


CenterWindow::CenterWindow(QWidget *parent) : QWidget(parent)
{
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(true);
    connect(buttonGroup, &QButtonGroup::buttonClicked,
            this, &CenterWindow::on_btnGroup_clicked);

    changeTheme(eTheme->getThemeMode());

    connect(eTheme, &ElaTheme::themeModeChanged, this, &CenterWindow::changeTheme);
}

void CenterWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int radius = 21;
    QRect _rect = rect().adjusted(-1, -1, 1, 1);

    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(_themeMode == ElaThemeType::Dark ? QColor("#2C2A38") : QColor("#FFFFFF")));
    painter.drawRect(_rect);

    _rect.setWidth(btn_w);

    if (_y1 * _y2 > 0) {
        QRect r1(0, 0, _rect.width(), _y1);
        QRect r2(0, _y2, _rect.width(), _rect.height() - _y2);

        QPainterPath path1;
        path1.moveTo(r1.topLeft());
        path1.lineTo(r1.topRight());
        if (r1.bottom() < 85) {
            path1.lineTo(r1.bottomRight());
        } else {
            path1.lineTo(r1.bottomRight() - QPointF(0, radius));
            path1.quadTo(r1.bottomRight(), r1.bottomRight() - QPointF(radius, 0));
        }
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
    } else {
        QPainterPath path;
        path.moveTo(_rect.topLeft());
        path.lineTo(_rect.topRight());
        path.lineTo(_rect.bottomRight());
        path.lineTo(_rect.bottomLeft());
        path.closeSubpath();
        painter.fillPath(path, cover_color);
    }

    painter.setRenderHint(QPainter::Antialiasing, false);

    QColor color = _themeMode == ElaThemeType::Dark ? QColor("#554F4F") : QColor("#DCDCDC");
    color.setAlpha(128);
    QPen pen(color);
    pen.setWidthF(1);
    painter.setPen(pen);
    painter.drawLine(_rect.x(), 80, rect().right(), 80);

    QWidget::paintEvent(event);
}

void CenterWindow::handleResize()
{
    if (checkedButton != nullptr) {
        _y1 = checkedButton->pos().y();
        _y2 = _y1 + checkedButton->height();
        update();
    }
}

void CenterWindow::on_btnGroup_clicked(QAbstractButton *btn)
{
    checkedButton = btn;
    if (checkedButton != nullptr) {
        _y1 = checkedButton->pos().y();
        _y2 = _y1 + checkedButton->height();
        update();
        stackedWidget->setCurrentIndex(buttonGroup->buttons().indexOf(btn));
    }
}

void CenterWindow::changeTheme(ElaThemeType::ThemeMode theme) {
    _themeMode = theme;
    if (theme == ElaThemeType::Dark) {
        cover_color = QColor(255, 255, 255, 30);
        QString qss = "QPushButton[btn-type=nav-button]{background-color:transparent;border-style:none;color:#D1D1D1;font: 12pt \"Microsoft YaHei\";}"
                       "QPushButton[btn-type=nav-button]:checked{color:white;}";
        setStyleSheet(qss);
    } else {
        cover_color = QColor(0, 0, 0, 10);
        QString qss = "QPushButton[btn-type=nav-button]{background-color:transparent;border-style:none;color:#808080;font: 12pt \"Microsoft YaHei\";}"
                       "QPushButton[btn-type=nav-button]:checked{color:black;}";
        setStyleSheet(qss);
    }
}

void CenterWindow::addPage(const QString &name, QWidget *widget)
{
    if (btn_lay == nullptr) {
        btn_lay = new QVBoxLayout;

        QLabel *label = new QLabel(this);
        label->setFixedHeight(81);
        btn_lay->addWidget(label);
        btn_lay->addStretch();
        stackedWidget = new QStackedWidget(this);
        QHBoxLayout *lay = new QHBoxLayout(this);
        lay->setContentsMargins(0, 0, 0, 0);
        lay->setSpacing(0);
        lay->addLayout(btn_lay);
        lay->addWidget(stackedWidget);
    }

    QPushButton *btn = new QPushButton(name, this);
    btn->setProperty("btn-type", "nav-button");
    btn->setCheckable(true);
    btn->setFixedSize(btn_w, 45);
    btn_lay->insertWidget(btn_lay->count() - 1, btn);
    buttonGroup->addButton(btn, stackedWidget->addWidget(widget));

    update();
}

bool CenterWindow::event(QEvent *event) {
    switch (event->type()) {
        case QEvent::Resize:
        if (checkedButton != nullptr) {
            _y1 = checkedButton->pos().y();
            _y2 = _y1 + checkedButton->height();
            update();
        }
        break;
    default:
        break;
    }
    return QWidget::event(event);
}
