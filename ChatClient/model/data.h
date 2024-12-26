#pragma once

#include <QString>
#include <QIcon>
#include <QUuid>
#include <QDateTime>
#include <QFile>
#include <iostream>

#define LOG std::cout << __FILE__ << ":" << __LINE__ << " "

namespace model {

/**
 * @brief 工具函数(内联函数，避免重复定义)
 */

/**
 * @brief 格式化时间
 * @param timestamp 时间戳
 * @return 格式化后的时间
 */
static inline QString formatTime(int64_t timestamp)
{
    // 转换时间戳为对象
    QDateTime time = QDateTime::fromMSecsSinceEpoch(timestamp);
    // 格式化
    return time.toString("MM-dd hh:mm:ss");
}

/**
 * @brief 获取当前时间
 * @return 当前秒级时间戳
 */
static inline int64_t getTime()
{
    return QDateTime::currentSecsSinceEpoch();
}

/**
 * @brief 将QByteArray(二进制)转换为QIcon(图标)
 * @param byteArray 二进制数据
 * @return 图标
 */
static inline QIcon byteArrayToIcon(const QByteArray &byteArray)
{
    QPixmap pixmap;
    pixmap.loadFromData(byteArray);
    QIcon icon(pixmap);
    return icon;
    // return QIcon(QPixmap::fromImage(QImage::fromData(byteArray)));
}

/**
 * @brief 读取文件
 * @param 二进制文件路径
 * @return QByteArray 二进制文件数据
 */
static inline QByteArray loadFileToByteArray(const QString &path)
{
    QFile file(path);
    bool ok = file.open(QFile::ReadOnly);
    if (!ok)
    {
        LOG << "文件打开失败" << std::endl;
        return QByteArray();
    }
    QByteArray byteArray = file.readAll();
    file.close();

    return byteArray;
}

/**
 * @brief 保存文件
 * @param 二进制文件数据，文件路径
 */
static inline void saveByteArrayToFile(const QByteArray &byteArray, const QString &path)
{
    QFile file(path);
    bool ok = file.open(QFile::WriteOnly);
    if (!ok)
    {
        LOG << "文件打开失败" << std::endl;
        return;
    }
    file.write(byteArray);
    file.flush(); // 刷新缓冲区(关键操作)
    file.close();
}



/**
 * @brief 用户信息
 */
class UserInfo
{
public:
    QString userId   = "";    // 用户编号
    QString nickName = "";    // 用户昵称
    QIcon avatar;             // 用户头像
    QString intro    = "";    // 用户简介
    // QString email    = "";    // 用户邮箱
    QString phone    = "";    // 用户电话
};

enum MessageType
{
    Text     = 0,             // 文本
    Image    = 1,             // 图片
    File     = 2,             // 文件
    Voice    = 3,             // 语音
    Video    = 4,             // 视频
    Location = 5              // 位置
};

/**
 * @brief 消息信息
 */
class Message
{
public:
    QString messageId     = "";                 // 消息编号
    QString chatSessionId = "";                 // 会话编号

    UserInfo sender;                            // 发送者
    UserInfo receiver;                          // 接收者
    QByteArray content;                         // 消息内容
    QString sendTime      = "";                 // 发送时间
    bool isRead = false;                        // 是否已读

    MessageType fileType  = MessageType::Text;  // 文件类型
    QString fileId        = "";                 // 文件编号：当消息类型为文件、图片或语音时，为文件编号；当消息类型为文本时，为空
    QString fileName      = "";                 // 文件名称


public:
    /**
     * @brief 创建消息       工厂模式
     * @param messageType   消息类型
     * @param chatSessionId 会话编号
     * @param sender        发送者
     * @param content       消息内容
     * @param extraInfo     额外信息: 当消息类型为文件时，extraInfo为文件名和文件类型
     */
    static Message makeMessage(MessageType messageType, const QString &chatSessionId, const UserInfo &sender,
                               const QByteArray &content, const QString &extraInfo)
    {
        if (MessageType::Text == messageType)
        {
            return makeTextMessage(chatSessionId, sender, content);
        }
        else if (MessageType::Image == messageType)
        {
            return makeImageMessage(chatSessionId, sender, content);
        }
        else if (MessageType::File == messageType)
        {
            return makeFileMessage(chatSessionId, sender, content, extraInfo);
        }
        else if (MessageType::Voice == messageType)
        {
            return makeVoiceMessage(chatSessionId, sender, content);
        }
        else // 未知消息类型，返回空消息对象
        {
            return Message();
        }
    }

private:
    /**
     * @brief 创建唯一编号，用于标识消息，会话等对象
     * @return 唯一编号，前缀'M'表示消息类型的编号
     */
    static QString createUuid()
    {
        QString uuid = QUuid::createUuid().toString();
        int pos = uuid.lastIndexOf("-");
        QString preFix = "M";
        return preFix + uuid.mid(pos); // sliced?
    }
    /**
     * @brief 创建文本消息
     * @param chatSessionId 会话编号，sender 发送者，content 消息内容
     * @return 消息对象
     */
    static Message makeTextMessage(const QString &chatSessionId, const UserInfo &sender, const QByteArray &content)
    {
        Message msg;
        msg.messageId = createUuid();
        msg.chatSessionId = chatSessionId;

        msg.sender = sender;
        msg.content = content;
        msg.sendTime = model::formatTime(model::getTime());

        msg.fileType = MessageType::Text;
        // 文本消息的编号和名称为空
        msg.fileId = "";
        msg.fileName = "";

        return msg;
    }
    /**
     * @brief 创建图片消息
     * @param chatSessionId 会话编号，sender 发送者，content 消息内容
     * @return 消息对象
     */
    static Message makeImageMessage(const QString &chatSessionId, const UserInfo &sender, const QByteArray &content)
    {
        Message msg;
        msg.messageId = Message::createUuid();
        msg.chatSessionId = chatSessionId;

        msg.sender = sender;
        msg.content = content;
        msg.sendTime = model::formatTime(model::getTime());

        msg.fileType = MessageType::Image;
        msg.fileId = "";        // TODO
        msg.fileName = "";      // 图片消息的文件名暂不需要

        return msg;
    }
    /**
     * @brief 创建文件消息
     * @param chatSessionId 会话编号，sender 发送者，content 消息内容，fileName 文件名
     * @return 消息对象
     */
    static Message makeFileMessage(const QString &chatSessionId, const UserInfo &sender, const QByteArray &content, const QString& fileName)
    {
        Message msg;
        msg.messageId = Message::createUuid();
        msg.chatSessionId = chatSessionId;

        msg.sender = sender;
        msg.content = content;
        msg.sendTime = model::formatTime(model::getTime());

        msg.fileType = MessageType::File;
        msg.fileId = "";        // TODO
        msg.fileName = fileName;

        return msg;
    }
    /**
     * @brief
     * @param
     * @return
     */
    static Message makeVoiceMessage(const QString &chatSessionId, const UserInfo &sender, const QByteArray &content)
    {
        Message msg;
        msg.messageId = Message::createUuid();
        msg.chatSessionId = chatSessionId;

        msg.sender = sender;
        msg.content = content;
        msg.sendTime = model::formatTime(model::getTime());

        msg.fileType = MessageType::Voice;
        msg.fileId = "";        // TODO
        msg.fileName = "";      // 语音消息的文件名暂不需要

        return msg;
    }

};


/**
 * @brief 用户信息
 */
class ChatSessionInfo
{
public:
    QString chatSessionId   = "";        // 会话编号
    QString chatSessionName = "";        // 会话名称
    // QIcon sessionIcon;            // 会话图标
    // QString sessionDesc;          // 会话描述

    // int unreadCount;              // 未读消息数
    Message lastMsgTime;                // 最后一条消息时间
    QString lastMsgContent  = "";       // 最后一条消息内容
};




} // end model


