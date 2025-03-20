#include "scrollwidget.h"

#include <QVBoxLayout>
#include <QPainter>
#include <QResizeEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QScroller>
#include <QStackedWidget>
#include <QDebug>


#include "ElaScrollArea.h"
#include "ElaScrollBar.h"

ScrollWidget::ScrollWidget(QWidget* parent)
    : QWidget(parent)
{ 

}

void ScrollWidget::setWidget(QWidget *topWidget, QWidget *cenWidget)
{
    if (scrollArea != nullptr)
        return;

    QVBoxLayout *main_lay = new QVBoxLayout(this);
    main_lay->setContentsMargins(2, 0, 2, 0);
    main_lay->setSpacing(1);

    scrollArea = new ElaScrollArea(this);
    scrollArea->setMouseTracking(true);
    scrollArea->setIsAnimation(Qt::Vertical, true);
    scrollArea->setWidgetResizable(true);
    scrollArea->setIsGrabGesture(true, 0);
    scrollArea->setIsOverShoot(Qt::Vertical, true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    ElaScrollBar* floatVScrollBar = new ElaScrollBar(scrollArea->verticalScrollBar(), scrollArea);
    floatVScrollBar->setIsAnimation(true);

    if (topWidget != nullptr) {
        topWidget->setFixedHeight(80);
        main_lay->addWidget(topWidget);
    }
    main_lay->addWidget(scrollArea);

    cenWidget->setProperty("widget-type", "base-widget");
    cenWidget->setStyleSheet("QWidget[widget-type=base-widget]{background-color:transparent;border:0px;}");
    scrollArea->setWidget(cenWidget);
}

