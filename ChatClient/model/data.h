#pragma once

#include <QString>
#include <QIcon>

namespace model {

/**
 * @brief 用户信息
 */
class UserInfo
{
public:
    QString userId;           // 用户编号
    QString nickName;         // 用户昵称
    QIcon avatar;             // 用户头像
    QString intro;            // 用户简介
    // QString email;            //  用户邮箱
    QString phone;            // 用户电话
};

enum MessageType
{
    Text = 0,            // 文本
    Image = 1,           // 图片
    File = 2,            // 文件
    Voice = 3,           // 语音
    Video = 4,           // 视频
    Location = 5         // 位置
};

/**
 * @brief 消息信息
 */
class Message
{
public:
    QString messageId;        // 消息编号
    QString chatSessionId;    // 会话编号

    UserInfo sender;          // 发送者
    UserInfo receiver;        // 接收者
    QByteArray content;       // 消息内容
    QString sendTime;         // 发送时间
    // bool isRead;              // 是否已读

    QString fileName;         // 文件名称
    QString fileType;         // 文件类型

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
            return makeFileMessage(chatSessionId, sender, content);
        }
        else if (MessageType::Voice == messageType)
        {
            return makeVoiceMessage(chatSessionId, sender, content);
        }
        else
        {
            return Message();
        }
    }

private:
    /**
     * @brief
     * @param
     * @return
     */
    static QString createUuid()
    {
        return "";
    }

    static Message makeTextMessage(const QString &chatSessionId, const UserInfo &sender, const QByteArray &content)
    {
        Message msg;
        msg.messageId = createUuid();
        msg.chatSessionId = chatSessionId;
        msg.sender = sender;
        msg.content = content;
        msg.sendTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        return msg;
    }

    static Message makeImageMessage(const QString &chatSessionId, const UserInfo &sender, const QByteArray &content)
    {
        Message msg;
        msg.messageId = createUuid();
        msg.chatSessionId = chatSessionId;
        msg.sender = sender;
        msg.content = content;
        msg.sendTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        return msg;
    }

    static Message makeFileMessage(const QString &chatSessionId, const UserInfo &sender, const QByteArray &content)
    {
        Message msg;
        msg.messageId = createUuid();
        msg.chatSessionId = chatSessionId;
        msg.sender = sender;
        msg.content = content;
        msg.sendTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        return msg;
    }

    static Message makeVoiceMessage(const QString &chatSessionId, const UserInfo &sender, const QByteArray &content)
    {
        Message msg;
        msg.messageId = createUuid();
        msg.chatSessionId = chatSessionId;
        msg.sender = sender;
        msg.content = content;
        msg.sendTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        return msg;
    }

};


/**
 * @brief 用户信息
 */
class ChatSessionInfo
{
public:
    QString chatSessionId;        // 会话编号
    QString chatSessionName;      // 会话名称
    // QIcon sessionIcon;            // 会话图标
    // QString sessionDesc;          // 会话描述

    // int unreadCount;              // 未读消息数
    Message lastMsgTime;          // 最后一条消息时间
    QString lastMsgContent;       // 最后一条消息内容
};




} // end model


