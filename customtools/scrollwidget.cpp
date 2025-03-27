#include "scrollwidget.h"

#include <QVBoxLayout>
#include <QPainter>
#include <QResizeEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QScroller>
#include <QStackedWidget>
#include <QDebug>


ScrollWidget::ScrollWidget(QWidget* parent)
    : QWidget(parent)
{ 
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=](){
        floatVScrollBar->setVisible(false);
    });
    timer->setInterval(2000);
}


void ScrollWidget::setWidget(QWidget *topWidget, QWidget *cenWidget)
{
    if (scrollArea != nullptr)
        return;

    QVBoxLayout *main_lay = new QVBoxLayout(this);
    main_lay->setContentsMargins(0, 0, 0, 0);
    main_lay->setSpacing(1);

    scrollArea = new ElaScrollArea(this);
    scrollArea->setMouseTracking(true);
    scrollArea->setIsAnimation(Qt::Vertical, true);
    scrollArea->setWidgetResizable(true);
    scrollArea->setIsGrabGesture(true, 0);
    scrollArea->setIsOverShoot(Qt::Vertical, true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    floatVScrollBar = new ElaScrollBar(scrollArea->verticalScrollBar(), scrollArea);
    floatVScrollBar->setIsAnimation(true);

    if (topWidget != nullptr) {
        topWidget->setFixedHeight(80);
        main_lay->addWidget(topWidget);
    }
    main_lay->addWidget(scrollArea);
    cenWidget->setProperty("widget-type", "base-widget");
    cenWidget->setStyleSheet("QWidget[widget-type=base-widget]{background-color:transparent;border:0px;}");
    scrollArea->setWidget(cenWidget);

    m_topWidget = topWidget;
    m_cenWidget = cenWidget;
}

void ScrollWidget::showEvent(QShowEvent *)
{
    floatVScrollBar->setVisible(false);
    floatVScrollBar->setValue(floatVScrollBar->minimum());

    if (m_cenWidget != nullptr) {
        QTimer::singleShot(100, this, [=]() {
            QWidget* currentWidget = m_cenWidget;
            QPropertyAnimation* currentWidgetAnimation = new QPropertyAnimation(currentWidget, "pos");
            currentWidgetAnimation->setEasingCurve(QEasingCurve::OutCubic);
            currentWidgetAnimation->setDuration(200);
            QPoint currentWidgetPos = currentWidget->pos();
            currentWidgetAnimation->setEndValue(currentWidgetPos);
            currentWidgetPos.setY(currentWidgetPos.y() + 200);
            currentWidgetAnimation->setStartValue(currentWidgetPos);
            currentWidgetAnimation->start(QAbstractAnimation::DeleteWhenStopped);
        });
    }
}

bool ScrollWidget::event(QEvent* event)
{
    switch (event->type())
    {
    case QEvent::Enter:
    {
        floatVScrollBar->setVisible(true);
        if (timer->isActive()) {
            timer->stop();
        }
        break;
    }
    case QEvent::Leave:
    {
        if (timer->isActive()) {
            timer->stop();
        }
        timer->start();
        break;
    }
    case QEvent::MouseMove:
    {
        break;
    }
    default:
    {
        break;
    }
    }
    return QWidget::event(event);
}
