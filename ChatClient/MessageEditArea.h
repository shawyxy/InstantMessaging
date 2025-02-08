#ifndef MESSAGEEDITAREA_H
#define MESSAGEEDITAREA_H

#include <QPlainTextEdit>
#include <QWidget>
#include "Core/IconButton.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollBar>


class MessageEditArea : public QWidget
{
    Q_OBJECT
public:
    MessageEditArea(QWidget *parent = nullptr);

private:
    IconButton *sendImageBtn;        // 发送图片按钮
    IconButton *sendFileBtn;         // 发送文件按钮
    IconButton *sendVoiceBtn;        // 发送语音按钮
    IconButton *showHistoryBtn;      // 显示历史消息按钮

    QPlainTextEdit *messageEdit;     // 消息编辑框

    QPushButton *sendBtn;             // 发送消息按钮

};

#endif // MESSAGEEDITAREA_H
