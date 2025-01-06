#ifndef CONTACTSESSIONAREA_H
#define CONTACTSESSIONAREA_H

#include <QLabel>
#include <QScrollArea>
#include <QWidget>
#include "debug.h"
#include "model/data.h"

/**
 * @brief 会话列表(滚动)区域类
 */
class ContactSessionArea : public QScrollArea
{
    Q_OBJECT
private:
    QWidget *container; // 会话列表容器
public:
    explicit ContactSessionArea(QWidget *parent = nullptr);
public slots:
    /**
     * @brief 清空会话列表
     */
    void SLOT_clearSessionList();

    /**
     * @brief        添加一个会话对象(ContactSessionItem)到会话列表
     * @param type   项的类型
     * @param id     用户编号/会话编号
     * @param avatar 用户头像
     * @param name   用户名称
     * @param msg    用户消息
     */
    void SLOT_addItem(model::ItemType type, const QString &id, const QIcon &avatar,
                      const QString &name, const QString &msg);

    /**
     * @brief       选中会话列表中的某一项
     * @param index 会话列表索引
     */
    void SLOT_selectSessionItem(int index);


signals:
};

/**
 * @brief 项(Item)基类
 */
class ContactSessionItemBase : public QWidget
{
    Q_OBJECT
protected:
    QLabel *msgLabel;       // 用户消息标签
private:
    QWidget *onwer;         // 会话对象所在会话列表对象的指针
    bool isSelect = false;  // 当前会话是否选中
public:
    /**
     * @brief        会话项(Item)基类构造函数
     * @param owner  父组件指针 (会话列表滚动区域 ContactSessionArea 对象)
     * @param avatar 用户头像
     * @param name   用户名称
     * @param msg    用户消息
     */
    ContactSessionItemBase(QWidget *owner, const QIcon &avatar, const QString &name, const QString &msg);

    /**
     * @brief       重写绘图事件
     * @param event 事件对象
     * @note        用于绘制背景颜色
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief       重写鼠标点击事件
     * @note        点击会话对象，选中当前会话
     */
    void mousePressEvent(QMouseEvent *event) override;

    /**
     * @brief 选中当前会话
     */
    void select();

    /**
     * @brief       重写鼠标进入事件
     * @note        鼠标悬停，设置背景颜色
     */
    void enterEvent(QEnterEvent *event) override;

    /**
     * @brief       重写鼠标离开事件
     * @note        鼠标离开，恢复背景颜色
     */
    void leaveEvent(QEvent *event) override;

    /**
     * @brief       点击item，激活对应的操作
     */
    virtual void active() = 0;
};


/**
 * @brief 联系人项
 */
class ContactItem : public ContactSessionItemBase
{
    Q_OBJECT
private:
    QString userId;    // 联系人编号
public:
    /**
     * @brief          联系人项构造函数
     * @param userId   用户编号
     * @param avatar   用户头像
     * @param nickName 用户昵称
     * @param intro    用户简介
     */
    ContactItem(QWidget *owner, const QString &userId, const QIcon &avatar,
                const QString &nickName, const QString &intro);

    /**
     * @brief       点击项，加载联系人列表
     */
    void active() override;
};

/**
 * @brief 会话项
 */
class SessionItem : public ContactSessionItemBase
{
    Q_OBJECT
private:
    QString chatSessionId;    // 当前会话ID
public:
    /**
     * @brief                 会话项构造函数
     * @param chatSessionId   会话编号
     * @param avatar          用户头像
     * @param chatSessionName 会话名称
     * @param lastMsgContent  最后一条消息内容
     */
    SessionItem(QWidget *owner, const QString &chatSessionId, const QIcon &avatar,
                const QString &chatSessionName, const QString &lastMsgContent);

    /**
     * @brief       点击项，加载会话项列表
     */
    void active() override;
};

/**
 * @brief 申请项
 */
class ApplyItem : public ContactSessionItemBase
{
    Q_OBJECT
public:

private:
    QString userId;    // 申请人编号
public:
    /**
     * @brief          申请项构造函数
     * @param userId   用户编号
     * @param avatar   用户头像
     * @param nickName 用户昵称
     * @param remark   申请备注
     */
    ApplyItem(QWidget *owner, const QString &userId, const QIcon &avatar,
              const QString &nickName, const QString &remark = "");

    /**
     * @brief       点击项，加载申请人项列表
     */
    void active() override;
};

#endif // CONTACTSESSIONAREA_H
