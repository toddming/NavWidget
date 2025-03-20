#ifndef SCROLLWIDGET_H
#define SCROLLWIDGET_H

#include <QWidget>

#include "ElaScrollArea.h"

class ScrollWidget : public QWidget
{
public:
    explicit ScrollWidget(QWidget* parent = nullptr);

    void setWidget(QWidget *topWidget, QWidget *cenWidget);

private:

    ElaScrollArea* scrollArea{nullptr};

};

#endif // SCROLLWIDGET_H
