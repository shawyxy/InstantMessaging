#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

#include "messageshowarea.h"
#include "messageeditarea.h"

class MainWidget : public QWidget
{
    Q_OBJECT

private:
    static MainWidget* _instance;

    QWidget *windowLeft;         // 左侧窗口
    QWidget *windowMid;          // 中间窗口
    QWidget *windowRight;        // 右侧窗口

    QPushButton *userAvatar;     // 用户头像
    QPushButton *sessionTabBtn;  // 会话标签按钮
    QPushButton *contactTabBtn;  // 联系人标签按钮
    QPushButton *applyTabBtn;    // 申请标签按钮
    QLineEdit *searchEdit;       // 搜索框
    QPushButton *addContactBtn;  // 添加联系人按钮

    enum class ActiveTab               // 标签页的类型
    {
        SessionList,
        ContactList,
        ApplyList
    };
    ActiveTab activeTab = ActiveTab::SessionList;

    MessageShowArea *messageShowArea; // 消息展示区域
    MessageEditArea *messageEditArea; // 消息编辑区域

public:
    void initMaindow();          // 初始化主窗口
    void initLeftWindow();       // 初始化左侧窗口
    void initMidWindow();        // 初始化中间窗口
    void initRightWindow();      // 初始化右侧窗口

    void initSignalSlot();       // 连接标签页按钮信号槽

    void loadSessionList();      // 加载会话列表
    void loadContactList();      // 加载联系人列表
    void loadApplyList();        // 加载申请列表


public slots:
    void SLOT_onSessionTabBtnClicked();  // 会话标签按钮点击事件
    void SLOT_onContactTabBtnClicked();  // 联系人标签按钮点击事件
    void SLOT_onApplyTabBtnClicked();    // 申请标签按钮点击事件

public:
    static MainWidget* getInstance();
    ~MainWidget();
private:
    MainWidget(QWidget *parent = nullptr);
};
#endif // MAINWIDGET_H
