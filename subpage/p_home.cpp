#include "p_home.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

#include "ElaText.h"
#include "ElaToggleSwitch.h"
#include "ElaTheme.h"
#include "ElaPushButton.h"

P_Home::P_Home(QWidget* parent)
    : ScrollWidget(parent)
{
    QWidget *centerWidget = new QWidget(this);

    QVBoxLayout *lay = new QVBoxLayout(centerWidget);

    QStringList rect_list = {"安全", "常规", "外观", "系统代理"};
    QStringList item_list = {"向系统通知栏发送相关消息", "开启时默认缩小至任务栏", "随机占用端口", "随机混合端扣",
                             "轻量模式", "检查更新", "新版本时提醒", "遵循系统主题", "使用系统表情符号",
                             "隐藏托盘图标", "透明", "指定协议", "静态主机", "悬浮窗", "显示筛选过滤器"};

    for (int i=0; i < 4; i++) {
        ElaText *title = new ElaText(rect_list.at(i), 17, centerWidget);
        title->setContentsMargins(0, 6, 0, 0);
        lay->addWidget(title);

        ScrollRect *rect = new ScrollRect(centerWidget);
        lay->addWidget(rect);
        QVBoxLayout *v_lay = new QVBoxLayout(rect);
        v_lay->setSpacing(0);
        v_lay->setContentsMargins(6,6,6,6);
        for (int n=0; n < 3; n++) {
            ScrollItem *item = new ScrollItem(rect);
            v_lay->addWidget(item);
            QHBoxLayout *h_lay = new QHBoxLayout(item);
            h_lay->setContentsMargins(8,8,8,8);
            ElaText *text = new ElaText(item_list.at(i*4+n), 15, item);
            h_lay->addWidget(text);
            if (i == 0) {
                h_lay->addWidget(new CheckGroup(QStringList({"明亮", "黑暗", "赛博朋克", "国庆中秋"}), item));
            } else {
                h_lay->addWidget(new ElaToggleSwitch(item));
            }
        }
    }
    lay->addStretch();

    QStringList btn_list = {"重置所有设置", "强制退出", "退出程序"};
    QWidget *topWidget = new QWidget(this);
    QHBoxLayout *top_lay = new QHBoxLayout(topWidget);
    top_lay->addWidget(new ElaText("设置", 20, topWidget));
    top_lay->addStretch();
    for (int i=0; i < btn_list.count(); i++) {
        ElaPushButton *btn = new ElaPushButton(btn_list.at(i), topWidget);
        btn->setLightTextColor(QColor("#FF5F5F"));
        btn->setDarkTextColor(QColor("#FF5F5F"));
        btn->setLightDefaultColor(QColor(0, 0, 0, 12));
        btn->setDarkDefaultColor(QColor(0xFF, 0xFF, 0xFF, 60));
        btn->setLightHoverColor(QColor(0, 0, 0, 20));
        btn->setDarkHoverColor(QColor(0xFF, 0xFF, 0xFF, 80));
        btn->setLightPressColor(QColor(0, 0, 0, 28));
        btn->setDarkPressColor(QColor(0xFF, 0xFF, 0xFF, 110));
        top_lay->addWidget(btn);
    }

    setWidget(topWidget, centerWidget);

    connect(eTheme, &ElaTheme::themeModeChanged, this, [=]() {
        if (!parent) {
            update();
        }
    });
}
