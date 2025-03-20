#include "p_home.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

#include "ElaText.h"
#include "ElaToggleSwitch.h"
#include "ElaTheme.h"
P_Home::P_Home(QWidget* parent)
    : ScrollWidget(parent)
{

    QWidget *centerWidget = new QWidget(this);

    QVBoxLayout *lay = new QVBoxLayout(centerWidget);

    QStringList list = {"向系统通知栏发送相关消息", "开启时默认缩小至任务栏", "随机占用端口", "随机混合端扣",
                       "轻量模式", "检查更新", "新版本时提醒", "遵循系统主题", "使用系统表情符号",
                       "隐藏托盘图标", "透明", "指定协议", "静态主机", "悬浮窗", "显示筛选过滤器"};

    for (int i=0; i < 4; i++) {
        ScrollRect *rect = new ScrollRect(centerWidget);
        lay->addWidget(rect);

        QVBoxLayout *v_lay = new QVBoxLayout(rect);
        v_lay->setSpacing(0);
        v_lay->setContentsMargins(6,6,6,6);
        for (int n=0; n < 3; n++) {
            ScrollItem *item = new ScrollItem(rect);
            //item->setFixedHeight(40);
            v_lay->addWidget(item);
            QHBoxLayout *h_lay = new QHBoxLayout(item);
            h_lay->setContentsMargins(8,8,8,8);
            ElaText *text = new ElaText(list.at(i*4+n), 15, item);
            h_lay->addWidget(text);
            h_lay->addWidget(new ElaToggleSwitch(item));
        }
    }
    lay->addStretch();
    connect(eTheme, &ElaTheme::themeModeChanged, this, [=]() {
        if (!parent) {
            update();
        }
    });

    setWidget(new QWidget(this), centerWidget);
}
