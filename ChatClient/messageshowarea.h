#ifndef MESSAGESHOWAREA_H
#define MESSAGESHOWAREA_H

#include <QLabel>
#include <QScrollArea>
#include <QWidget>

#include "model/data.h"

/**
 * @brief 消息展示区域
 */
class MessageShowArea : public QScrollArea
{
    Q_OBJECT
private:
    QWidget *container; // 消息展示区域容器
public:
    MessageShowArea();

    /**
     * @brief          头插消息
     * @param isMine   是否是自己发送的消息
     * @param msg      消息结构体
     */
    void pushBackMessageItem(bool isMine, const model::Message &msg);

    /**
     * @brief          尾插消息
     * @param isMine   是否是自己发送的消息
     * @param msg      消息结构体
     */
    void pushFrontMessageItem(bool isMine, const model::Message &msg);

    /**
     * @brief 清空消息
     */
    void clearMessageItems();
};


/**
 * @brief   表示一条消息
 * @details 消息的内容、发送者、接收者、发送时间等信息
 *          消息的类型：文本、图片、文件、语音等
 */
class MessageItem : public QWidget
{
    Q_OBJECT
private:
    bool isMine; // 是否是自己发送的消息，用于区分左右两侧的消息
public:
    MessageItem(bool isMine);

    /**
     * @brief          获取消息对象(工厂模式)
     * @param isMine   是否是自己发送的消息
     * @param msg      消息结构体
     * @return         消息对象
     */
    static MessageItem *getMessageItem(bool isMine, const model::Message &msg);

    /**
     * @brief  获取文本消息对象
     * @return 消息对象
     */
    static QWidget *getTextMessageItem(bool isMine, const QString &msg);

    /**
     * @brief  获取图片消息对象
     * @return 消息对象
     */
    static QWidget *getImageMessageItem();

    /**
     * @brief  获取文件消息对象
     * @return 消息对象
     */
    static QWidget *getFileMessageItem();

    /**
     * @brief  获取语音消息对象
     * @return 消息对象
     */
    static QWidget *getVoiceMessageItem();

    /**
     * @brief  获取视频消息对象
     * @return 消息对象
     */
    static QWidget *getVideoMessageItem();
};

/**
 * @brief   消息正文内容
 * @details
 */
class MessageContentLabel : public QWidget
{
    Q_OBJECT
private:
    QLabel *contentLabel; // 消息内容标签
    bool isMine;          // 是否是自己发送的消息

public:
    MessageContentLabel(bool isMine, const QString &content);

    /**
     * @brief 重写绘图方法
     */
    void paintEvent(QPaintEvent *event) override;
};
#endif // MESSAGESHOWAREA_H
