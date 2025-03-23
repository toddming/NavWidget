#ifndef HTOOLBUTTON_H
#define HTOOLBUTTON_H

#include <QToolButton>
#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>

#include "ElaTheme.h"

class HToolButton : public QToolButton
{
public:
    explicit HToolButton(const QString &text = "", bool underline = false, QWidget *parent = nullptr);

    void setUnderline(bool);

protected:
    virtual void paintEvent(QPaintEvent* event) override;

private:
    bool m_underline{false};

    int m_pSize{10};


    ElaThemeType::ThemeMode _themeMode;

};

#endif // HTOOLBUTTON_H
