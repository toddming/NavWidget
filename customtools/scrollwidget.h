#ifndef SCROLLWIDGET_H
#define SCROLLWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPropertyAnimation>

#include "ElaScrollArea.h"
#include "ElaScrollBar.h"

class ScrollWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScrollWidget(QWidget* parent = nullptr);

    void setWidget(QWidget *topWidget, QWidget *cenWidget);

    void showWidget();

protected:
    virtual bool event(QEvent* event) override;

private:

    ElaScrollArea* scrollArea{nullptr};

    QWidget *m_topWidget{nullptr};

    QWidget *m_cenWidget{nullptr};

    ElaScrollBar* floatVScrollBar;

    QTimer *timer;
};

#endif // SCROLLWIDGET_H
