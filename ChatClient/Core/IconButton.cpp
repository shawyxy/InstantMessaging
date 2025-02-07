#include "iconbutton.h"

#include <QDebug>
#include <QDrag>
#include <QMimeData>
#include <QUrl>

IconButton::IconButton(const QString& normalIcon, const QString& pressIcon, QWidget* parent) : QPushButton {parent}, _normalIconPath {new QString(normalIcon)}, _pressIconPath {new QString(pressIcon)}
{
    this->setFlat(true);
    this->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored));
    this->setIcon(QIcon(*this->_normalIconPath));
}

IconButton::~IconButton()
{
    delete this->_normalIconPath;
    delete this->_pressIconPath;
}

void IconButton::mousePressEvent(QMouseEvent* event)
{
    if (this->_pressIconPath->isEmpty())
        return;
    if (event->button() == Qt::LeftButton)
    {
        this->setIcon(QIcon(*this->_pressIconPath));
        this->setIconSize(this->size());
    }
}

void IconButton::mouseReleaseEvent(QMouseEvent* event)
{
    if (this->_normalIconPath->isEmpty())
        return;
    if (event->button() == Qt::LeftButton)
    {
        this->setIcon(QIcon(*this->_normalIconPath));
        this->setIconSize(this->size());
        emit this->released();
    }
}

void IconButton::resizeEvent(QResizeEvent* event)
{
    this->setIconSize(this->size());
}
