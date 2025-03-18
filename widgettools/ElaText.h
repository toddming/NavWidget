#ifndef ELATEXT_H
#define ELATEXT_H

#include <QLabel>

#include "Def.h"
#include "stdafx.h"
class ElaTextPrivate;
class ElaText : public QLabel
{
    Q_OBJECT
    Q_Q_CREATE(ElaText)
    Q_PROPERTY_CREATE_Q_H(bool, IsWrapAnywhere)
    Q_PROPERTY_CREATE_Q_H(int, TextPixelSize)
    Q_PROPERTY_CREATE_Q_H(int, TextPointSize)
    Q_PROPERTY_CREATE_Q_H(ElaTextType::TextStyle, TextStyle)
    Q_PROPERTY_CREATE_Q_H(ElaIconType::IconName, ElaIcon)
public:
    explicit ElaText(QWidget* parent = nullptr);
    explicit ElaText(QString text, QWidget* parent = nullptr);
    explicit ElaText(QString text, int pixelSize, QWidget* parent = nullptr);
    ~ElaText() override;

private:
    void onThemeChanged(ElaThemeType::ThemeMode themeMode);

    void _changeTheme();


protected:
    virtual void paintEvent(QPaintEvent* event) override;
};

#endif // ELATEXT_H
