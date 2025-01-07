#include "messageshowarea.h"

#include <QScrollBar>
#include <Qboxlayout>
#include <Qlabel>
#include <QPushButton>
#include <QPainter>
#include <QPainterPath>

/**
 * @brief 消息展示区域
 */
MessageShowArea::MessageShowArea()
{
    // 设置滚动区域属性
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setWidgetResizable(true); // 设置滚动区域是否自动调整大小
    // 垂直滚动条样式
    this->verticalScrollBar()->setStyleSheet("QScrollBar: { width: 2px; backgroud: rgb(240, 240, 240); }");
    // 水平滚动条样式，隐藏
    this->horizontalScrollBar()->setStyleSheet("QScrollBar: { height: 0; }");
    this->setStyleSheet("QScrollArea { border: none; }");
    // 添加容器
    container = new QWidget();
    this->setWidget(container);

    // 布局
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    container->setLayout(layout);
}

/**
 * @brief   表示一条消息
 * @details 消息的内容、发送者、接收者、发送时间等信息
 *          消息的类型：文本、图片、文件、语音等
 */
MessageItem::MessageItem(bool isMyself) : isMyself(isMyself)
{

}

/**
 * @brief          获取消息对象
 * @param isMyself 是否是自己发送的消息
 * @param msg      消息结构体
 * @return         消息对象
 */
MessageItem *MessageItem::getMessageItem(bool isMyself, const model::Message &msg)
{
    // 创建对象和布局管理器
    MessageItem *messageItem = new MessageItem(isMyself);
    QGridLayout *layout = new QGridLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    messageItem->setMinimumHeight(100); // 设置最小高度
    messageItem->setLayout(layout);

    // 头像
    QPushButton *avatarBtn = new QPushButton();
    avatarBtn->setFixedSize(40, 40);
    avatarBtn->setIconSize(QSize(40, 40));
    avatarBtn->setIcon(msg.sender.avatar);
    if (isMyself)
    {
        layout->addWidget(avatarBtn, 0, 1, 2, 1, Qt::AlignTop | Qt::AlignLeft);
    }
    else
    {
        layout->addWidget(avatarBtn, 0, 0, 2, 1, Qt::AlignTop | Qt::AlignLeft);
    }

    // 昵称和时间
    QLabel *nickNameLabel = new QLabel();
    nickNameLabel->setStyleSheet("QLabel { font-size: 12px; color: rgb(178, 178, 178); }");
    nickNameLabel->setAlignment(Qt::AlignBottom);
    nickNameLabel->setText(msg.sender.nickName + "|" + msg.sendTime);
    if (isMyself)
    {
        layout->addWidget(nickNameLabel, 0, 0, Qt::AlignRight);
    }
    else
    {
        layout->addWidget(nickNameLabel, 0, 1);
    }

    // 消息内容
    QWidget *msgContentWidget = nullptr;
    switch (msg.fileType)
    {
    case model::MessageType::Text:
        msgContentWidget = getTextMessageItem();
        break;
    case model::MessageType::Image:
        msgContentWidget = getImageMessageItem();
        break;
    case model::MessageType::File:
        msgContentWidget = getFileMessageItem();
        break;
    case model::MessageType::Voice:
        msgContentWidget = getVoiceMessageItem();
        break;
    case model::MessageType::Video:
        msgContentWidget = getVideoMessageItem();
        break;
    }

    if (isMyself)
    {
        layout->addWidget(msgContentWidget, 1, 0);
    }
    else
    {
        layout->addWidget(msgContentWidget, 1, 1);
    }
    return messageItem;
}

/**
 * @brief  获取文本消息对象
 * @return 消息对象
 */
MessageItem *MessageItem::getTextMessageItem()
{
    return nullptr;
}

/**
 * @brief  获取图片消息对象
 * @return 图片消息对象
 */
MessageItem *MessageItem::getImageMessageItem()
{
    return nullptr;
}

/**
 * @brief  获取文件消息对象
 * @return 文件消息对象
 */
MessageItem *MessageItem::getFileMessageItem()
{
    return nullptr;
}

/**
 * @brief  获取语音消息对象
 * @return 语音消息对象
 */
MessageItem *MessageItem::getVoiceMessageItem()
{
    return nullptr;
}

/**
 * @brief  获取视频消息对象
 * @return 视频消息对象
 */
MessageItem *MessageItem::getVideoMessageItem()
{
    return nullptr;
}

/**
 * @brief   消息正文内容
 * @details
 */
MessageContentLabel::MessageContentLabel(bool isMyself, const QString &content)
    : isMyself(isMyself)
{
    QFont font;
    font.setFamily("微软雅黑");
    font.setPixelSize(14);

    this->contentLabel = new QLabel();
    this->contentLabel->setText(content);
    this->contentLabel->setFont(font);
    this->contentLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    this->contentLabel->setWordWrap(true); // 自动换行
    this->contentLabel->setStyleSheet("QLabel { padding: 0 10px; line-height: 1.2; }");
}


void MessageContentLabel::paintEvent(QPaintEvent *event)
{
    (void)event;
    // 1. 获取父元素的宽度
    QObject* object = this->parent();
    if (!object->isWidgetType())
    {
        LOG << "父元素为空";
        return;
    }
    QWidget *parent = dynamic_cast<QWidget *>(object);
    int width = parent->width() * 0.6; // 宽度上限为聊天界面的60%

    // 2. 计算消息文本的所有内容排成一行所占的总宽度
    QFontMetrics metrics(this->contentLabel->font());
    int totalWidth = metrics.horizontalAdvance(this->contentLabel->text());

    // 3. 计算消息文本所占行数
    int rows = (totalWidth / (width - 40)) + 1; // 除去文本两边的边距，以及向上取整
    if (rows == 1) // 如果文本只占1行，那么需要重新加上文本两边的边距
    {
        width = totalWidth + 40;
    }

    // 4. 计算消息文本所占高度
    int height = rows * (this->contentLabel->font().pixelSize() * 1.2) + 20; // 包含上下10px间距，1.2是行高

    // 5. 绘制消息气泡的圆角矩形和三角形
    QPainter painter(this);
    QPainterPath painterPath;
    painter.setRenderHint(QPainter::Antialiasing); // 打开抗锯齿，使画面更清晰
    if (isMyself)
    {
        painter.setPen(QPen(QColor(137, 217, 97))); // 画笔颜色
        painter.setBrush(QColor(137, 217, 97)); // 笔刷颜色

        // 气泡(圆角矩形)左侧横坐标位置
        int leftX = this->width() - width - 10; // 消息内容宽度-消息宽度-右侧边距
        int leftY = 0;
        // 气泡(圆角矩形)右侧横坐标位置
        int rightX = this->width() - 10; // 消息内容宽度-右侧边距
        // 绘制气泡(圆角矩形)
        painter.drawRoundedRect(leftX, leftY, width, height, 10, 10); // 圆角为10px
        // 绘制气泡(三角形)
        painterPath.moveTo(rightX, 15);
        painterPath.lineTo(rightX + 10, 20);
        painterPath.lineTo(rightX, 25);
        painterPath.closeSubpath();
        painter.drawPath(painterPath); // 绘制闭合曲线
        // 设置三角形所在的位置
        this->contentLabel->setGeometry(leftX, leftY, width, height);
    }
    else
    {
        painter.setPen(QPen(QColor(255, 255, 255))); // 画笔颜色
        painter.setBrush(QColor(255, 255, 255)); // 笔刷颜色

        // 气泡(圆角矩形)左侧横坐标位置
        int leftX = 10; // 左侧边距
        int leftY = 0;
        // 绘制气泡(圆角矩形)
        painter.drawRoundedRect(leftX, leftY, width, height, 10, 10); // 圆角为10px
        // 绘制气泡(三角形)
        painterPath.moveTo(leftX, 15);
        painterPath.lineTo(leftY, 20);
        painterPath.lineTo(leftX, 25);
        painterPath.closeSubpath();
        painter.drawPath(painterPath); // 绘制闭合曲线
        // 设置三角形所在的位置
        this->contentLabel->setGeometry(leftX, leftY, width, height);
    }
    // 6. 重新设置消息项(父组件)的高度，确保能容纳消息气泡的内容，并且留有冗余空间
    parent->setFixedHeight(height + 50);
}
