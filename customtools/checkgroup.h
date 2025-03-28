#ifndef CHECKGROUP_H
#define CHECKGROUP_H

#include <QWidget>
#include <QPainter>
#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QPropertyAnimation>


#include "Def.h"
#include "ElaTheme.h"

class CheckGroup : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QRect myRect READ myRect WRITE setMyRect)
public:
    explicit CheckGroup(const QStringList &items, QWidget* parent = nullptr);

    QRect myRect() const;
    void setMyRect(const QRect &value);

protected:
    virtual void paintEvent(QPaintEvent* event) override;

signals:
    void myRectChanged();

private slots:
    void on_btnGroup_clicked(QAbstractButton *btn);

private:
    ElaThemeType::ThemeMode _themeMode;

    int _pBorderRadius;

    QButtonGroup *buttonGroup{nullptr};

    QAbstractButton* checkedButton{nullptr};

    QRect m_rect;

    void startRectAnimation(QRect targetRect, int duration);

};

#endif // CHECKGROUP_H
