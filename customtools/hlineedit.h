#ifndef HLINEEDIT_H
#define HLINEEDIT_H

#include <QLineEdit>
#include <QPainter>
#include <QContextMenuEvent>
#include <QGuiApplication>
#include <QClipboard>

#include "ElaTheme.h"
#include "ElaMenu.h"

class HLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit HLineEdit(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
    void contextMenuEvent(QContextMenuEvent* event) override;

private slots:
    void onThemeChanged(ElaThemeType::ThemeMode themeMode);

private:
    int _pBorderRadius{4};

    ElaThemeType::ThemeMode _themeMode;



};

#endif // HLINEEDIT_H
