#ifndef CONTACTSESSIONAREA_H
#define CONTACTSESSIONAREA_H

#include <QScrollArea>
#include <QWidget>
#include "debug.h"

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
    void SLOT_clear();

    /**
     * @brief 添加一个会话对象(ContactSessionItem)到会话列表
     * @param avatar 用户头像
     * @param name   用户名称
     * @param msg    用户消息
     */
    void SLOT_addSessionItem(const QIcon &avatar, const QString &name, const QString &msg);

signals:
};

/**
 * @brief 会话类
 */
class ContactSessionItem : public QWidget
{
    Q_OBJECT
private:
    QWidget *onwer;         // 会话对象所在会话列表对象的指针
    bool isSelect = false;  // 当前会话是否选中
public:
    /**
     * @brief 构造函数
     * @param owner  父组件指针 (会话列表滚动区域 ContactSessionArea 对象)
     * @param avatar 用户头像
     * @param name   用户名称
     * @param msg    用户消息
     */
    ContactSessionItem(QWidget *owner, const QIcon &avatar, const QString &name, const QString &msg);

    /**
     * @brief 重写绘图事件
     * @param event 事件对象
     */
    void paintEvent(QPaintEvent *event) override;

};
#endif // CONTACTSESSIONAREA_H