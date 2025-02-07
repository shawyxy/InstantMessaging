#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QDrag>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QMouseEvent>
#include <QPoint>
#include <QPushButton>

class IconButton : public QPushButton
{
    Q_OBJECT
public:
    IconButton(const QString& normalIcon, const QString& pressIcon, QWidget* parent = nullptr);
    ~IconButton();

protected:
    /**
     * @brief mousePressEvent 鼠标点击事件
     * @param event
     */
    virtual void mousePressEvent(QMouseEvent* event);

    /**
     * @brief mouseReleaseEvent 鼠标释放事件
     * @param event
     */
    virtual void mouseReleaseEvent(QMouseEvent* event);

    /**
     * @brief resizeEvent 缩放事件
     * @param event
     */
    virtual void resizeEvent(QResizeEvent* event);

private:
    QString* _normalIconPath;
    QString* _pressIconPath;
};

#endif // ICONBUTTON_H
