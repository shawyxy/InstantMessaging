#include "MessageEditArea.h"

MessageEditArea::MessageEditArea(QWidget *parent) : QWidget(parent)
{
    // 1. 属性
    this->setFixedHeight(200);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    // 2. 垂直布局管理器（整体）
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setSpacing(0);
    vLayout->setContentsMargins(20, 0, 20, 10);
    this->setLayout(vLayout);

    // 3. 水平布局管理器（按钮）
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setSpacing(10);
    hLayout->setContentsMargins(10, 0, 0, 0);
    hLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    vLayout->addLayout(hLayout);

    // 4. 将按钮添加到水平布局
    sendImageBtn = new IconButton(":/resource/image/image-normal.png", ":/resource/image/image-press.png", this);
    sendFileBtn = new IconButton(":/resource/image/file-normal.png", ":/resource/image/file-press.png", this);
    sendVoiceBtn = new IconButton(":/resource/image/voice-normal.png", ":/resource/image/voice-press.png", this);
    showHistoryBtn = new IconButton(":/resource/image/history-normal.png", ":/resource/image/history-press.png", this);

    sendImageBtn->setFixedSize(20, 20);
    sendFileBtn->setFixedSize(20, 20);
    sendVoiceBtn->setFixedSize(20, 20);
    showHistoryBtn->setFixedSize(20, 20);

    hLayout->addWidget(sendImageBtn);
    hLayout->addWidget(sendFileBtn);
    hLayout->addWidget(sendVoiceBtn);
    hLayout->addWidget(showHistoryBtn);

    // 5. 消息编辑框
    messageEdit = new QPlainTextEdit();
    messageEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    messageEdit->setStyleSheet(R"(
        QPlainTextEdit {
            border: none;
            background-color: transparent;
            font-size: 12px;
            border-radius: 5px;
            padding: 10px;
        }
    )");
    messageEdit->verticalScrollBar()->setStyleSheet(R"(
        QScrollBar:vertical {
            width: 10px;
            backgroud-color: rgb(240, 240, 240);
        }
    )");
    vLayout->addWidget(messageEdit);

    // 6. 发送按钮
    sendBtn = new QPushButton("发送");
    sendBtn->setFixedSize(80, 35);
    sendBtn->setStyleSheet(R"(
        QPushButton {
            font-size: 12px;
            color: rgb(7, 193, 96);
            border: none;
            background-color: rgb(233, 233, 233);
            border-radius: 7px;
        }
        QPushButton:hover {
            background-color: rgb(210, 210, 210);
        }
        QPushButton:pressed {
            background-color: rgb(190, 190, 190);
        }
    )");
    vLayout->addWidget(sendBtn, 0, Qt::AlignRight | Qt::AlignVCenter);
}
