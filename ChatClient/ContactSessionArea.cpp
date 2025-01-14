#include "ContactSessionArea.h"

#include <QLabel>
#include <QPainter>
#include <QScrollBar>
#include <QStyleOption>
#include <qboxlayout.h>
#include <qpushbutton.h>

ContactSessionArea::ContactSessionArea(QWidget *parent)
    : QScrollArea{parent}
{
    // 自动调整子组件大小，才能开启滚动条
    this->setWidgetResizable(true);
    // 设置滚动条样式
    this->verticalScrollBar()->setStyleSheet("QScrollBar:vertical { \
                                              width: 10px; \
                                              background-color: rgb(80, 80, 80); }");
    this->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal { \
                                                height: 0px; }");
    // 去除边框
    this->setStyleSheet("QWidget { border: none; }");

    container = new QWidget(this);
    container->setFixedWidth(300); // 宽度和左侧窗口一致
    this->setWidget(container);

    // 布局
    QVBoxLayout *layout = new QVBoxLayout(container);   // 垂直布局
    layout->setContentsMargins(0, 0, 0, 0);             // 布局边距四个方向的边距都为0
    layout->setSpacing(0);                              // 子组件的间距为0
    layout->setAlignment(Qt::AlignTop);                 // 向上对齐
    container->setLayout(layout);

    // for test
    // for (int i = 0; i < 20; --i)
    // {
    //     QPushButton *btn = new QPushButton("会话" + QString::number(i), container);
    //     btn->setFixedHeight(50);
    //     layout->addWidget(btn);
    // }
#if TEST_UI
    QIcon icon(":/resource/image/defaultAvatar.png");
    for (int i = 0; i <=20; ++i)
    {
        this->SLOT_addItem(model::ItemType::ApplyItem, QString::number(i), icon, "用户" + QString::number(i), "最后一条消息" + QString::number(i));
    }
#endif
}

/**
 * @brief 清空会话列表
 * @note
 *          1. QLayout是上面ContactSessionArea中layout的父类(25行)，原则上需要进行类型转换
 *             但是这里可以不强求，因为itemAt()是QLayout中的虚函数，返回的是QLayoutItem类型的指针
 *
 *          2. 从最后一个子组件开始删除，是因为删除一个子组件后，后面的子组件会前移
 *             手动删除子组件，防止内存泄漏
 */
void ContactSessionArea::SLOT_clearSessionList()
{
    QLayout *layout = container->layout();
    for (int i = layout->count() - 1; i >= 0; --i)
    {
        QLayoutItem *item = layout->itemAt(i);
        if (item->widget())
        {
            delete item->widget();
        }
        layout->removeItem(item);
        delete item;
    }
}

/**
 * @brief        添加一个项到会话列表
 * @param type   项的类型
 * @param id     用户编号/会话编号
 * @param avatar 用户头像
 * @param name   用户名称
 * @param msg    用户消息/用户简介/用户申请理由
 */
void ContactSessionArea::SLOT_addItem(model::ItemType type, const QString &id, const QIcon &avatar,
                                      const QString &name, const QString &msg)
{
    ContactSessionItemBase *item = nullptr;
    switch (type)
    {
    case model::ItemType::ContactItem:
        item = new ContactItem(this, id, avatar, name, msg);
        break;
    case model::ItemType::SessionItem:
        item = new SessionItem(this, id, avatar, name, msg);
        break;
    case model::ItemType::ApplyItem:
        item = new ApplyItem(this, id, avatar, name, msg);
        break;
    default:
        break;
    }
    if (item == nullptr)
    {
        LOG << "会话项为空";
        return;
    }
    // 添加到会话列表
    container->layout()->addWidget(item);
}

/**
 * @brief       选中会话列表中的某一项
 * @param index 会话列表索引
 */
void ContactSessionArea::SLOT_selectSessionItem(int index)
{
    if (index < 0 || index >= container->layout()->count())
    {
        LOG << "会话列表索引越界, index: " << index;
        return;
    }
    QLayoutItem *layoutItem = container->layout()->itemAt(index);
    if (layoutItem == nullptr || layoutItem->layout() == nullptr) // 项为空或者项的布局为空
    {
        LOG << "会话列表项为空, index:" << index;
        return;
    }
    // 从布局项中获取会话对象
    ContactSessionItemBase *item = dynamic_cast<ContactSessionItemBase *>(layoutItem->widget());
    item->select(); // 选中当前会话
}

/**
 * @brief        会话项(Item)基类构造函数
 * @param owner  父组件指针 (会话列表滚动区域 ContactSessionArea 对象)
 * @param avatar 用户头像
 * @param name   用户名称
 * @param msg    用户消息
 */
ContactSessionItemBase::ContactSessionItemBase(QWidget *owner, const QIcon &avatar, const QString &name, const QString &msg)
{
    this->setFixedHeight(70); // 设置固定高度
    this->setStyleSheet("QWidget { background-color: rgb(229, 228, 228); }"); // 设置背景颜色

    // 网格布局管理器
    QGridLayout *layout = new QGridLayout();
    layout->setContentsMargins(20, 0, 0, 0); // 左边距20，其他方向边距为0
    layout->setHorizontalSpacing(10);        // 水平方向间距为10
    layout->setVerticalSpacing(0);           // 垂直方向间距为0
    this->setLayout(layout);

    // 头像
    QPushButton *avatarBtn = new QPushButton();
    avatarBtn->setIcon(avatar);
    avatarBtn->setIconSize(QSize(50, 50));
    avatarBtn->setFixedSize(50, 50);
    avatarBtn->setStyleSheet("QPushButton { background-color: transparent; border: none; }");
    avatarBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed); // 大小策略：水平方向扩展，垂直方向扩展

    // 用户名
    QLabel *nameLabel = new QLabel(name);
    nameLabel->setStyleSheet("QLabel { font-size: 16px; font-weight: 600; color: rgb(46, 46, 46); }");
    nameLabel->setFixedHeight(35);
    nameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); // 大小策略：水平方向扩展，垂直方向固定

    // 消息预览
    msgLabel = new QLabel(msg);
    msgLabel->setStyleSheet("QLabel { font-size: 12px; color: rgb(46, 46, 46); }");
    msgLabel->setFixedHeight(25);
    msgLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); // 大小策略：水平方向扩展，垂直方向固定

    // 添加子组件
    layout->addWidget(avatarBtn, 0, 0, 2, 8); // 头像，在第0行0列，占2行8列
    layout->addWidget(nameLabel, 0, 2, 1, 8); // 用户名，在第0行2列，占1行8列
    layout->addWidget(msgLabel, 1, 2, 1, 1);  // 消息，在第1行2列，占1行8列
}

/**
 * @brief       重写绘图事件
 * @param event 事件对象
 * @note        用于绘制背景颜色
 */
void ContactSessionItemBase::paintEvent(QPaintEvent *event)
{
    (void)event;
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

/**
 * @brief       重写鼠标点击事件
 * @param event 事件对象
 * @note        点击会话对象，选中当前会话
 */
void ContactSessionItemBase::mousePressEvent(QMouseEvent *event)
{
    (void)event;
    select();
}

/**
 * @brief 选中当前会话
 */
void ContactSessionItemBase::select()
{
    this->setStyleSheet("QWidget { background-color: rgb(199, 197, 197); }"); // 设置背景颜色
    this->isSelect = true;                                                    // 选中当前会话
    const QObjectList children = this->parentWidget()->children();            // 将其他会话取消选中
    for (QObject *child : children)
    {
        if (child != this)                                                    // 不是当前选中的会话
        {
            ContactSessionItemBase *item = dynamic_cast<ContactSessionItemBase *>(child);
            if (item)                                                         // 如果是会话对象
            {
                item->setStyleSheet("QWidget { background-color: rgb(229, 228, 228); }");
                item->isSelect = false;
            }
        }
    }
    active(); // 激活当前item对应
}

/**
 * @brief       重写鼠标进入事件
 * @param event 事件对象
 * @note        鼠标悬停，设置背景颜色
 */
void ContactSessionItemBase::enterEvent(QEnterEvent *event)
{
    (void)event;
    if (!isSelect) // 如果当前会话未选中
    {
        this->setStyleSheet("QWidget { background-color: rgb(217, 216, 216); }");
    }
}

/**
 * @brief       重写鼠标离开事件
 * @param event 事件对象
 * @note        鼠标离开，恢复背景颜色
 */
void ContactSessionItemBase::leaveEvent(QEvent *event)
{
    (void)event;
    if (!isSelect) // 如果当前会话未选中
    {
        this->setStyleSheet("QWidget { background-color: rgb(229, 228, 228); }");
    }
}

/**
 * @brief          联系人项构造函数
 * @param userId   用户编号
 * @param avatar   用户头像
 * @param nickName 用户昵称
 * @param intro    用户简介
 */
ContactItem::ContactItem(QWidget *owner, const QString &userId, const QIcon &avatar,
                         const QString &nickName, const QString &intro)
    : ContactSessionItemBase(owner, avatar, nickName, intro)
    , userId(userId)
{

}

/**
 * @brief       点击项，加载联系人列表
 */
void ContactItem::active()
{
    qDebug() << "ContactItem::active()";
}

/**
 * @brief                 会话项构造函数
 * @param chatSessionId   会话编号
 * @param avatar          用户头像
 * @param chatSessionName 会话名称
 * @param lastMsgContent  最后一条消息内容
 */
SessionItem::SessionItem(QWidget *owner, const QString &chatSessionId, const QIcon &avatar,
                         const QString &chatSessionName, const QString &lastMsgContent)
    : ContactSessionItemBase(owner, avatar, chatSessionName, lastMsgContent)
    , chatSessionId(chatSessionId)
{

}

/**
 * @brief       点击项，加载会话项列表
 */
void SessionItem::active()
{
    qDebug() << "SessionItem::active()";
}

/**
 * @brief          申请项构造函数
 * @param userId   用户编号
 * @param avatar   用户头像
 * @param nickName 用户昵称
 * @param remark   申请备注
 */
ApplyItem::ApplyItem(QWidget *owner, const QString &userId, const QIcon &avatar,
                     const QString &nickName, const QString &remark)
    : ContactSessionItemBase(owner, avatar, nickName, remark)
    , userId(userId)
{
    // 移除基类中布局管理器中的msgLabel
    QGridLayout *layout = dynamic_cast<QGridLayout *>(this->layout());
    layout->removeWidget(msgLabel);
    delete msgLabel;

    // 添加同意和拒绝按钮
    QPushButton *agreeBtn = new QPushButton("同意");
    QPushButton *rejectBtn = new QPushButton("拒绝");
    // 添加到布局管理器中
    layout->addWidget(agreeBtn, 1, 2, 1, 1);
    layout->addWidget(rejectBtn, 1, 3, 1, 1);
}

/**
 * @brief       点击项，加载申请人项列表
 */
void ApplyItem::active()
{
    qDebug() << "ApplyItem::active()";
}
