#include "FramelessWindow.h"
#include <QMouseEvent>
#include <QPainter>
#include <QtMath>
#include <QLayout>

#ifdef Platform_Win
#include <windows.h>
#include <windowsx.h>

// 检测是否改变窗口大小的边框范围
#define    BoardStartPix                     (1)       // 检测外边框与窗口边缘的距离
#define    BoardEndPix                       (8)       // 检测内边框与窗口边缘的距离
#endif

// 边框阴影区域宽度
#define    BoardShadeWidth                   (6)

FramelessWindow::FramelessWindow(QWidget *parent) :
    QDialog(parent)
#ifdef Platform_Win
    ,_resizeEnabled(true)
#else
    ,_drag(false)
#endif
    ,_shadeEnabled(true)
    ,_shadeRoundEnabled(true)
    ,_doubleClickedMaxEnabled(true)
    ,_doubleClickHeight(20)
{
    setWindowFlags(Qt::Dialog|Qt::FramelessWindowHint|Qt::WindowTitleHint|Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint);
    setAttribute(Qt::WA_TranslucentBackground);

#ifdef UseShadePictureMode
    shadowPixmapList.append(QPixmap(":/Resource/shadow_left.png"));
    shadowPixmapList.append(QPixmap(":/Resource/shadow_left_top.png"));
    shadowPixmapList.append(QPixmap(":/Resource/shadow_top.png"));
    shadowPixmapList.append(QPixmap(":/Resource/shadow_right_top.png"));
    shadowPixmapList.append(QPixmap(":/Resource/shadow_right.png"));
    shadowPixmapList.append(QPixmap(":/Resource/shadow_right_bottom.png"));
    shadowPixmapList.append(QPixmap(":/Resource/shadow_bottom.png"));
    shadowPixmapList.append(QPixmap(":/Resource/shadow_left_bottom.png"));
#endif

#ifndef Platform_Win
    setMouseTracking(true);
#endif
}

FramelessWindow::~FramelessWindow()
{
#ifdef UseShadePictureMode
    shadowPixmapList.clear();
#endif
}

#ifdef Platform_Win
void FramelessWindow::setResize(bool enabled)
{
    _resizeEnabled = enabled;
}
#endif

void FramelessWindow::setShadeEnable(bool enabled)
{
    _shadeEnabled = enabled;
}

void FramelessWindow::setShadeRounded(bool enabled)
{
    _shadeRoundEnabled = enabled;
}

void FramelessWindow::setDoubleClickMaxsize(bool enabled, int height)
{
    _doubleClickedMaxEnabled = enabled;
    _doubleClickHeight = height;
}

void FramelessWindow::mousePressEvent(QMouseEvent *event)
{
#ifdef Platform_Win
    if (ReleaseCapture())
        SendMessage(HWND(this->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
    event->ignore();
#else
    if (event->button() == Qt::LeftButton)
    {
        _drag = true;
        _dragPosition = event->globalPos() - this->pos();
        event->accept();
    }
#endif
}

void FramelessWindow::mouseMoveEvent(QMouseEvent *event)
{
#ifdef Platform_Win
    QDialog::mouseMoveEvent(event);
#else
    if (_drag && (event->buttons() && Qt::LeftButton))
    {
        move(event->globalPos() - _dragPosition);
        event->accept();
    }
#endif
}

void FramelessWindow::mouseReleaseEvent(QMouseEvent *event)
{
#ifdef Platform_Win
    QDialog::mouseReleaseEvent(event);
#else
    _drag = false;
#endif
}

void FramelessWindow::mouseDoubleClickEvent(QMouseEvent *event)
{
    // 判断是否允许双击切换窗口最大化和普通
    if (!_doubleClickedMaxEnabled)
    {
        QDialog::mouseDoubleClickEvent(event);
        return;
    }

    // 检测允许双击的区域
    QRect rect = this->rect();
    if (this->isMaximized())
    {
        rect.setHeight(_doubleClickHeight);
        if (rect.contains(event->pos()))
        {
            this->showNormal();
        }
    }
    else
    {
        rect.setHeight(_doubleClickHeight+BoardShadeWidth);
        if (rect.contains(event->pos()))
        {
            this->showMaximized();
        }
    }
}

bool FramelessWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
#ifdef Platform_Win
    if (!_resizeEnabled)
    {
        return QDialog::nativeEvent(eventType, message, result);
    }

    Q_UNUSED(eventType);
    MSG* msg = reinterpret_cast<MSG*>(message);
    switch(msg->message)
    {
    case WM_NCHITTEST:
        int xPos = GET_X_LPARAM(msg->lParam) - this->frameGeometry().x();
        int yPos = GET_Y_LPARAM(msg->lParam) - this->frameGeometry().y();
        if(this->childAt(xPos,yPos) != NULL)  // 鼠标位置上有控件
        {
            return false;
        }

        // 鼠标位置上没有控件，先判断是否位于伪标题栏
        QRect rect = this->rect();
        rect.setHeight(_doubleClickHeight);
        if (rect.contains(QPoint(xPos, yPos)))  // 鼠标位置位于伪标题栏区域内
        {
            *result = HTCAPTION;
        }

        if(xPos > BoardStartPix && xPos < BoardEndPix)
            *result = HTLEFT;
        if(xPos > (this->width() - BoardEndPix) && xPos < (this->width() - BoardStartPix))
            *result = HTRIGHT;
        if(yPos > BoardStartPix && yPos < BoardEndPix)
            *result = HTTOP;
        if(yPos > (this->height() - BoardEndPix) && yPos < (this->height() - BoardStartPix))
            *result = HTBOTTOM;
        if(xPos > BoardStartPix && xPos < BoardEndPix && yPos > BoardStartPix && yPos < BoardEndPix)
            *result = HTTOPLEFT;
        if(xPos > (this->width() - BoardEndPix) && xPos < (this->width() - BoardStartPix) && yPos > BoardStartPix && yPos < BoardEndPix)
            *result = HTTOPRIGHT;
        if(xPos > BoardStartPix && xPos < BoardEndPix && yPos > (this->height() - BoardEndPix) && yPos < (this->height() - BoardStartPix))
            *result = HTBOTTOMLEFT;
        if(xPos > (this->width() - BoardEndPix) && xPos < (this->width() - BoardStartPix) && yPos > (this->height() - BoardEndPix) && yPos < (this->height() - BoardStartPix))
            *result = HTBOTTOMRIGHT;
        return true;
    }
    return false;
#else
    return QDialog::nativeEvent(eventType, message, result);
#endif
}

void FramelessWindow::paintEvent(QPaintEvent *event)
{
    QDialog::paintEvent(event);
    if (!_shadeEnabled)
    {
        return;
    }

#ifdef UseShadePictureMode
    // 先将窗口背景刷新为白色
    if (this->isMaximized() || this->isFullScreen()) // 最大化或全屏下刷新整个窗口为白色，且让子窗口填充满
    {
        QLayout* layout = this->layout();
        if (layout != NULL)
        layout->setContentsMargins(0, 0, 0, 0);

        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(this->rect());
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.fillPath(path, QBrush(Qt::white));
        return;
    }
    else // 正常大小显示，让主窗口布局四周空出阴影所需宽度。
    {
        QLayout* layout = this->layout();
        if (layout != NULL)
        layout->setContentsMargins(BoardShadeWidth, BoardShadeWidth, BoardShadeWidth, BoardShadeWidth);

        QSize verticalShadowSize   = QSize(BoardShadeWidth, this->height() - BoardShadeWidth*2);
        QSize horizontalShadowSize = QSize(this->width() - BoardShadeWidth*2, BoardShadeWidth);
        QSize cornerShadowSize     = QSize(BoardShadeWidth, BoardShadeWidth);

        QRect leftRectangle        = QRect(QPoint(0, BoardShadeWidth), verticalShadowSize);
        QRect leftTopRectangle     = QRect(QPoint(0, 0), cornerShadowSize);
        QRect topRectangle         = QRect(QPoint(BoardShadeWidth, 0), horizontalShadowSize);
        QRect rightTopRectangle    = QRect(QPoint(this->width() - BoardShadeWidth, 0), cornerShadowSize);
        QRect rightRectangle       = QRect(QPoint(this->width() - BoardShadeWidth, BoardShadeWidth), verticalShadowSize);
        QRect rightBottomRectangle = QRect(QPoint(this->width() - BoardShadeWidth, this->height() - BoardShadeWidth), cornerShadowSize);
        QRect bottomRectangle      = QRect(QPoint(BoardShadeWidth, this->height() - BoardShadeWidth), horizontalShadowSize);
        QRect leftBottomRectangle  = QRect(QPoint(0, this->height() - BoardShadeWidth), cornerShadowSize);

        QPainter painter(this);
        painter.drawPixmap(leftRectangle,        shadowPixmapList[0].scaled(verticalShadowSize));
        painter.drawPixmap(leftTopRectangle,     shadowPixmapList[1].scaled(cornerShadowSize));
        painter.drawPixmap(topRectangle,         shadowPixmapList[2].scaled(horizontalShadowSize));
        painter.drawPixmap(rightTopRectangle,    shadowPixmapList[3].scaled(cornerShadowSize));
        painter.drawPixmap(rightRectangle,       shadowPixmapList[4].scaled(verticalShadowSize));
        painter.drawPixmap(rightBottomRectangle, shadowPixmapList[5].scaled(cornerShadowSize));
        painter.drawPixmap(bottomRectangle,      shadowPixmapList[6].scaled(horizontalShadowSize));
        painter.drawPixmap(leftBottomRectangle,  shadowPixmapList[7].scaled(cornerShadowSize));

        painter.setPen(Qt::NoPen);
        painter.setBrush(Qt::white);
        painter.drawRect(QRect(BoardShadeWidth, BoardShadeWidth, this->width()-2*BoardShadeWidth, this->height()-2*BoardShadeWidth));
    }

#else

    // 先将窗口背景刷新为白色
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    if (this->isMaximized() || this->isFullScreen()) // 最大化或全屏下刷新整个窗口为白色，且让子窗口填充满
    {
        QLayout* layout = this->layout();
        if (layout != NULL)
        layout->setContentsMargins(0, 0, 0, 0);

        path.addRect(this->rect());
        painter.fillPath(path, QBrush(Qt::white));
        return;
    }
    else // 正常大小显示，让主窗口布局四周空出阴影所需宽度。
    {
        QLayout* layout = this->layout();
        if (layout != NULL)
        layout->setContentsMargins(BoardShadeWidth, BoardShadeWidth, BoardShadeWidth, BoardShadeWidth);

        path.addRect(BoardShadeWidth, BoardShadeWidth,
                     this->width()-BoardShadeWidth*2,
                     this->height()-BoardShadeWidth*2);
        painter.fillPath(path, QBrush(Qt::white));
    }

    // 再绘制边框阴影效果
    QColor color(100, 100, 100, 50);
    for(int i=0; i<BoardShadeWidth; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);

        if (_shadeRoundEnabled)  // 绘制圆角矩形
        {
            path.addRoundedRect(BoardShadeWidth-i,
                                BoardShadeWidth-i,
                                this->width()-(BoardShadeWidth-i)*2,
                                this->height()-(BoardShadeWidth-i)*2,
                                2,
                                2);
        }
        else   // 绘制直角矩形
        {
            path.addRect(BoardShadeWidth-i,
                         BoardShadeWidth-i,
                         this->width()-(BoardShadeWidth-i)*2,
                         this->height()-(BoardShadeWidth-i)*2);
        }

        color.setAlpha(145 - qSqrt(i)*60);
        painter.setPen(color);
        painter.drawPath(path);
    }
#endif
}
