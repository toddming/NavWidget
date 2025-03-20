#ifndef P_HOME_H
#define P_HOME_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "customtools/scrollrect.h"
#include "customtools/scrollitem.h"
#include "customtools/scrollwidget.h"

class P_Home : public ScrollWidget
{
public:
    explicit P_Home(QWidget* parent = nullptr);


};

#endif // P_HOME_H
