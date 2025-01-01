#include "contactsessionarea.h"

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
        this->SLOT_addSessionItem(icon, "用户" + QString::number(i), "最后一条消息" + QString::number(i));
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
void ContactSessionArea::SLOT_clear()
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

void ContactSessionArea::SLOT_addSessionItem(const QIcon &avatar, const QString &name, const QString &msg)
{
    ContactSessionItem *item = new ContactSessionItem(this, avatar, name, msg);
    container->layout()->addWidget(item);
}

/**
 * @brief 构造函数
 * @param owner  父组件指针 (会话列表滚动区域 ContactSessionArea 对象)
 * @param avatar 用户头像
 * @param name   用户名称
 * @param msg    用户消息
 */
ContactSessionItem::ContactSessionItem(QWidget *owner, const QIcon &avatar, const QString &name, const QString &msg)
{
    this->setFixedHeight(70); // 设置固定高度
    this->setStyleSheet("QWidget { background-color: rgb(230, 230, 230); }"); // 设置背景颜色

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
    QLabel *msgLabel = new QLabel(msg);
    msgLabel->setStyleSheet("QLabel { font-size: 12px; color: rgb(46, 46, 46); }");
    msgLabel->setFixedHeight(25);
    msgLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); // 大小策略：水平方向扩展，垂直方向固定

    // 添加子组件
    layout->addWidget(avatarBtn, 0, 0, 2, 2); // 头像，在第0行0列，占2行2列
    layout->addWidget(nameLabel, 0, 2, 1, 1); // 用户名，在第0行2列，占1行1列
    layout->addWidget(msgLabel, 1, 2, 1, 1);  // 消息，在第1行2列，占1行1列
}

void ContactSessionItem::paintEvent(QPaintEvent *event)
{
    (void)event;
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

