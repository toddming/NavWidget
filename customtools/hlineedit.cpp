#include "hlineedit.h"


HLineEdit::HLineEdit(QWidget *parent) : QLineEdit(parent)
{
    setFixedWidth(120);

    setAlignment(Qt::AlignCenter);

    onThemeChanged(eTheme->getThemeMode());

    connect(eTheme, &ElaTheme::themeModeChanged, this, &HLineEdit::onThemeChanged);
}

void HLineEdit::onThemeChanged(ElaThemeType::ThemeMode themeMode)
{
    _themeMode = themeMode;
    if (themeMode == ElaThemeType::Light) {
        QPalette palette;
        palette.setColor(QPalette::Text, Qt::black);
        palette.setColor(QPalette::PlaceholderText, QColor(0x00, 0x00, 0x00, 128));
        setPalette(palette);
    } else {
        QString styleSheet = "QLineEdit {"
                             "    background-color: rgb(55, 55, 57);"
                             "    border: none;"
                             "    border-bottom: 1px solid rgba(255, 255, 255, 0.5442);"
                             "    border-radius: 5px;"
                             "    padding: 5px 10px;"
                             "    color: white;"
                             "    selection-color: black;"
                             "}"
                             "QLineEdit:hover {"
                             "    background: rgba(255, 255, 255, 0.0837);"
                             "}"
                             "QLineEdit:focus {"
                             "    background: rgb(31, 31, 31);"
                             "}"
                             "QLineEdit:disabled {"
                             "    color: rgba(255, 255, 255, 0.36);"
                             "    background-color: rgba(255, 255, 255, 0.0419);"
                             "    border: 1px solid rgba(255, 255, 255, 0.0698);"
                             "}";
        setStyleSheet(styleSheet);
    }
}

void HLineEdit::paintEvent(QPaintEvent* event)
{
    QLineEdit::paintEvent(event);
    // QPainter painter(this);
    // painter.save();
    // painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    // painter.setPen(Qt::NoPen);
    // painter.setBrush(_themeMode == ElaThemeType::Dark ? QColor(55,55,57) : QColor(255,255,255));
    // painter.drawRoundedRect(rect(), _pBorderRadius, _pBorderRadius);
    // painter.restore();
}

void HLineEdit::contextMenuEvent(QContextMenuEvent* event)
{
    ElaMenu* menu = new ElaMenu(this);
    menu->setMenuItemHeight(27);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    QAction* action = nullptr;
    if (!isReadOnly())
    {
        action = menu->addElaIconAction(ElaIconType::ArrowRotateLeft, tr("撤销"), QKeySequence::Undo);
        action->setEnabled(isUndoAvailable());
        connect(action, &QAction::triggered, this, &HLineEdit::undo);

        action = menu->addElaIconAction(ElaIconType::ArrowRotateRight, tr("恢复"), QKeySequence::Redo);
        action->setEnabled(isRedoAvailable());
        connect(action, &QAction::triggered, this, &HLineEdit::redo);
        menu->addSeparator();
    }
#ifndef QT_NO_CLIPBOARD
    if (!isReadOnly())
    {
        action = menu->addElaIconAction(ElaIconType::KnifeKitchen, tr("剪切"), QKeySequence::Cut);
        action->setEnabled(!isReadOnly() && hasSelectedText() && echoMode() == QLineEdit::Normal);
        connect(action, &QAction::triggered, this, &HLineEdit::cut);
    }

    action = menu->addElaIconAction(ElaIconType::Copy, tr("复制"), QKeySequence::Copy);
    action->setEnabled(hasSelectedText() && echoMode() == QLineEdit::Normal);
    connect(action, &QAction::triggered, this, &HLineEdit::copy);

    if (!isReadOnly())
    {
        action = menu->addElaIconAction(ElaIconType::Paste, tr("粘贴"), QKeySequence::Paste);
        action->setEnabled(!isReadOnly() && !QGuiApplication::clipboard()->text().isEmpty());
        connect(action, &QAction::triggered, this, &HLineEdit::paste);
    }
#endif
    if (!isReadOnly())
    {
        action = menu->addElaIconAction(ElaIconType::DeleteLeft, tr("删除"));
        action->setEnabled(!isReadOnly() && !text().isEmpty() && hasSelectedText());
        connect(action, &QAction::triggered, this, [=](bool checked) {
            if (hasSelectedText())
            {
                int startIndex = selectionStart();
                int endIndex = selectionEnd();
                setText(text().remove(startIndex, endIndex - startIndex));
            }
        });
    }
    if (!menu->isEmpty())
    {
        menu->addSeparator();
    }
    action = menu->addAction(tr("全选"));
    action->setShortcut(QKeySequence::SelectAll);
    action->setEnabled(!text().isEmpty() && !(selectedText() == text()));
    connect(action, &QAction::triggered, this, &HLineEdit::selectAll);
    menu->popup(event->globalPos());
}
