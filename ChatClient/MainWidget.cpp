#include "MainWidget.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "ContactSessionArea.h"
#include "Debug.h"

// 初始化静态成员变量
MainWidget* MainWidget::_instance = nullptr;

MainWidget *MainWidget::getInstance()
{
    if (_instance == nullptr)
    {
        // 不指定父对象，以桌面为父窗口，默认是桌面
        _instance = new MainWidget();
    }
    return _instance;
}

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    // 设置窗口属性
    this->setWindowTitle("聊天室");
    this->setWindowIcon(QIcon(":/resource/image/logo.png"));
    this->setGeometry({100, 100, 1000, 600});  // 设置窗口位置和大小
    this->setMinimumSize({1000, 600});         // 设置窗口最小大小
    // 初始化窗口布局
    initMaindow();
    initLeftWindow();
    initMidWindow();
    initRightWindow();
    // 连接槽函数
    initSignalSlot();
}

MainWidget::~MainWidget() {}

void MainWidget::initMaindow()
{
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing(0);                      // 设置子组件之间的间隔
    layout->setContentsMargins(0, 0, 0, 0);     // 设置布局的边距
    this->setLayout(layout);

    windowLeft = new QWidget();
    windowMid = new QWidget();
    windowRight = new QWidget();

    windowLeft->setFixedWidth(80);              // 左侧工具栏固定宽度
    windowMid->setFixedWidth(300);              // 中间会话列表固定宽度
    windowRight->setMinimumWidth(600);          // 右侧聊天界面最小宽度

    windowLeft->setStyleSheet(R"(
        QWidget {
            background-color: rgb(46, 46, 46);
        }
    )");
    windowMid->setStyleSheet(R"(
        QWidget {
            background-color: rgb(234, 231, 230);
        }
    )");
    windowRight->setStyleSheet(R"(
        QWidget {
            background-color: rgb(245, 245, 245);
        }
    )");


    // 将组件添加到布局中
    layout->addWidget(windowLeft);
    layout->addWidget(windowMid);
    layout->addWidget(windowRight);

}

void MainWidget::initLeftWindow()
{
    QVBoxLayout *layout = new QVBoxLayout();
    windowLeft->setLayout(layout);
    layout->setSpacing(20);
    layout->setContentsMargins(0, 50, 0, 0); // 设置布局上方的边距

    // 用户头像
    userAvatar = new QPushButton();
    userAvatar->setFixedSize(45, 45);
    userAvatar->setIcon(QIcon(":/resource/image/defaultAvatar.png"));
    userAvatar->setIconSize(QSize(30, 30));
    userAvatar->setStyleSheet(R"(
        QPushButton {
            background-color: transparent; border: none
        }
    )");
    layout->addWidget(userAvatar, 1, Qt::AlignCenter | Qt::AlignTop);

    // 会话标签按钮
    sessionTabBtn = new QPushButton();
    sessionTabBtn->setFixedSize(45, 45);
    sessionTabBtn->setIcon(QIcon(":/resource/image/session_active.png"));
    sessionTabBtn->setIconSize(QSize(30, 30));
    sessionTabBtn->setStyleSheet(R"(
        QPushButton {
            background-color: transparent;
            border: none
        }
    )");
    layout->addWidget(sessionTabBtn, 1, Qt::AlignCenter | Qt::AlignTop);

    // 联系人标签按钮
    contactTabBtn = new QPushButton();
    contactTabBtn->setFixedSize(45, 45);
    contactTabBtn->setIcon(QIcon(":/resource/image/contact_inactive.png"));
    contactTabBtn->setIconSize(QSize(30, 30));
    contactTabBtn->setStyleSheet(R"(
        QPushButton {
            background-color: transparent;
            border: none
        }
    )");
    layout->addWidget(contactTabBtn, 1, Qt::AlignCenter | Qt::AlignTop);

    // 申请标签按钮
    applyTabBtn = new QPushButton();
    applyTabBtn->setFixedSize(45, 45);
    applyTabBtn->setIcon(QIcon(":/resource/image/apply_inactive.png"));
    applyTabBtn->setIconSize(QSize(30, 30));
    applyTabBtn->setStyleSheet(R"(
        QPushButton {
            background-color: transparent;
            border: none
        }
    )");
    layout->addWidget(applyTabBtn, 1, Qt::AlignCenter | Qt::AlignTop);

    layout->addStretch(20);

}

void MainWidget::initMidWindow()
{
    QGridLayout *layout = new QGridLayout();
    layout->setContentsMargins(0, 20, 0, 0); // 设置布局上方的边距
    layout->setHorizontalSpacing(0);         // 设置水平方向间距
    layout->setVerticalSpacing(10);          // 设置垂直方向间距
    windowMid->setLayout(layout);

    searchEdit = new QLineEdit();
    searchEdit->setFixedHeight(30);
    searchEdit->setPlaceholderText("搜索");
    searchEdit->setStyleSheet(R"(
        QLineEdit {
            background-color: rgb(226, 226, 226);
            border-radius: 5px;
        }
    )");

    addContactBtn = new QPushButton();
    addContactBtn->setFixedSize(30, 30);
    addContactBtn->setIcon(QIcon(":/resource/image/cross.png"));
    QString style = R"(
        QPushButton {
            background-color: rgb(226, 226, 226);
            border-radius: 5px;
        }
    )";
    style += R"(
        QPushButton:pressed {
            background-color: rgb(240, 240, 240);
        }
    )";
    addContactBtn->setStyleSheet(style);

    // 用空白控件填充搜索框布局
    QWidget *spacer1 = new QWidget();
    spacer1->setFixedWidth(10);
    QWidget *spacer2 = new QWidget();
    spacer2->setFixedHeight(10);
    QWidget *spacer3 = new QWidget();
    spacer3->setFixedHeight(10);

    ContactSessionArea *contactSessionArea = new ContactSessionArea(); // 会话列表区域

    layout->addWidget(spacer1, 0, 0);
    layout->addWidget(searchEdit, 0, 1);
    layout->addWidget(spacer2, 0, 2);
    layout->addWidget(addContactBtn, 0, 3);
    layout->addWidget(spacer3, 0, 4);
    layout->addWidget(contactSessionArea, 1, 0, 1, 5); // 设置宽度占满
}

void MainWidget::initRightWindow()
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setAlignment(Qt::AlignTop);
    windowRight->setLayout(layout);

    // 上方标题栏
    QWidget *titleWidget = new QWidget();
    titleWidget->setFixedHeight(62); // 固定高度
    titleWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); // 水平方向扩展，垂直方向固定
    titleWidget->setObjectName("titleWidget");
    titleWidget->setStyleSheet(R"(
        #titleWidget {
            border-bottom: 1px solid rgb(231, 231, 231);
            border-left: 1px solid rgb(231, 231, 231);
        }
    )");
    layout->addWidget(titleWidget);
    // 设置标题栏的布局
    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->setSpacing(0);
    titleLayout->setContentsMargins(10, 0, 0, 10); // 设置左边距和上边距
    titleWidget->setLayout(titleLayout);
    // 会话标题
    QLabel *sessionTitleLabel = new QLabel();
    sessionTitleLabel->setStyleSheet(R"(
        QLabel {
            font-size: 18px;
        }
    )");
#if TEST_UI
    sessionTitleLabel->setText("会话标题");
#endif
    titleLayout->addWidget(sessionTitleLabel);
    // 设置标题栏的右侧详细信息按钮
    QPushButton *detailBtn = new QPushButton();
    detailBtn->setFixedSize(30, 30);
    detailBtn->setIconSize(QSize(30, 30));
    detailBtn->setIcon(QIcon(":/resource/image/more.png"));
    detailBtn->setStyleSheet(R"(
        QPushButton {
            border:none;
            background-color: rgb(245, 245, 245);
        }
        QPushButton:pressed {
            background-color: rgb(220, 220, 220);
        }
    )");
    titleLayout->addWidget(detailBtn);

    // 聊天消息区域
    messageShowArea = new MessageShowArea();
    layout->addWidget(messageShowArea);

    // 输入框
    messageEditArea = new MessageEditArea();
    layout->addWidget(messageEditArea, 0, Qt::AlignBottom); // 底部对齐，伸缩系数为0，表示默认不主动占用额外空间
}

/**
 * @brief 连接信号槽，用于标签页切换
 */
void MainWidget::initSignalSlot()
{
    connect(sessionTabBtn, &QPushButton::clicked, this, &MainWidget::SLOT_onSessionTabBtnClicked);
    connect(contactTabBtn, &QPushButton::clicked, this, &MainWidget::SLOT_onContactTabBtnClicked);
    connect(applyTabBtn, &QPushButton::clicked, this, &MainWidget::SLOT_onApplyTabBtnClicked);
}

/**
 * @brief 加载会话列表
 */
void MainWidget::loadSessionList()
{

}

/**
 * @brief 加载联系人列表
 */
void MainWidget::loadContactList()
{

}

/**
 * @brief 加载申请列表
 */
void MainWidget::loadApplyList()
{

}

void MainWidget::SLOT_onSessionTabBtnClicked()
{
    qDebug() << "会话标签按钮点击事件";
    activeTab = ActiveTab::SessionList;                                                // 更改当前标签状态，并更改其他标签图标
    sessionTabBtn->setIcon(QIcon(":/resource/image/session_active.png"));
    contactTabBtn->setIcon(QIcon(":/resource/image/contact_inactive.png"));
    applyTabBtn->setIcon(QIcon(":/resource/image/apply_inactive.png"));
    this->loadSessionList();                                                // 加载会话列表
}

void MainWidget::SLOT_onContactTabBtnClicked()
{
    qDebug() << "联系人标签按钮点击事件";
    activeTab = ActiveTab::ContactList;                                                // 更改当前标签状态，并更改其他标签图标
    sessionTabBtn->setIcon(QIcon(":/resource/image/session_inactive.png"));
    contactTabBtn->setIcon(QIcon(":/resource/image/contact_active.png"));
    applyTabBtn->setIcon(QIcon(":/resource/image/apply_inactive.png"));
    this->loadContactList();                                                // 加载联系人列表
}

void MainWidget::SLOT_onApplyTabBtnClicked()
{
    qDebug() << "申请标签按钮点击事件";
    activeTab = ActiveTab::ApplyList;                                                  // 更改当前标签状态，并更改其他标签图标
    sessionTabBtn->setIcon(QIcon(":/resource/image/session_inactive.png"));
    contactTabBtn->setIcon(QIcon(":/resource/image/contact_inactive.png"));
    applyTabBtn->setIcon(QIcon(":/resource/image/apply_active.png"));
    this->loadApplyList();                                                  // 加载申请列表
}
