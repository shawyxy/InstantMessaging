#include "mainwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

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

    // 初始化窗口布局
    initMaindow();
    initLeftWindow();
    initMidWindow();
    initRightWindow();
}

MainWidget::~MainWidget() {}

void MainWidget::initMaindow()
{
    QHBoxLayout *layout = new QHBoxLayout();
    layout->setSpacing(0);                      // 设置子组件的间隔
    layout->setContentsMargins(0, 0, 0, 0);     // 设置布局的边距
    this->setLayout(layout);

    windowLeft = new QWidget();
    windowMid = new QWidget();
    windowRight = new QWidget();

    windowLeft->setFixedWidth(80);              // 左侧工具栏固定宽度
    windowMid->setFixedWidth(300);              // 中间会话列表固定宽度
    windowRight->setMinimumWidth(600);          // 右侧聊天界面最小宽度

    // windowLeft->setStyleSheet("QWidget { background-color: rgb(46, 46, 46); }");
    // windowMid->setStyleSheet("QWidget { background-color: rgb(247, 247, 247); }");
    // windowRight->setStyleSheet("QWidget { background-color: rgb(245, 245, 245); }");


    // 将组件添加到布局中
    layout->addWidget(windowLeft);
    layout->addWidget(windowMid);
    layout->addWidget(windowRight);

}

void MainWidget::initLeftWindow()
{

}

void MainWidget::initMidWindow()
{

}

void MainWidget::initRightWindow()
{

}
