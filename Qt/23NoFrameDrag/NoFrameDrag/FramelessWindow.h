#ifndef FRAMELESSWINDOW_H
#define FRAMELESSWINDOW_H

/*
 *说明：
 *此类实现无标题栏窗口的拖拽移动、调节窗口大小以及边框阴影效果。
 * 实现双击伪窗口标题栏切换窗口大小
 *使用时直接继承此基类即可。
 * 缺点：调节窗口大小时偶尔出现窗口闪烁的问题
 */

#include <QDialog>

// 此类实现有2种方案
// 1.定义Platform_Win，此类仅支持windows系统，可以移动和改变大小；无法跨平台，效率高；
// 2.非定义Platform_Win，支持跨平台，但是仅能实现移动，无法改变大小，效率低；
#define     Platform_Win

// 定义使用图片阴影的方式；不定义默认使用软件绘制的方式；
//#define     UseShadePictureMode

class QMouseEvent;
class FramelessWindow :
        public QDialog
{
    Q_OBJECT
public:
    explicit FramelessWindow(QWidget *parent = 0);
    ~FramelessWindow();

#ifdef Platform_Win
    // 设置是否允许调节窗口大小
    void setResize(bool enabled);
#endif

    // 设置是否允许窗口边框阴影
    // 若允许阴影，则内部控件布局上下左右均要预留阴影的宽度
    void setShadeEnable(bool enabled);

    // 设置窗口边框阴影圆角矩形(允许阴影才有效)，true - 圆角，false - 直角
    void setShadeRounded(bool enabled);

    // 设置是否允许双击伪标题栏，切换窗口大小，height - 标题栏高度(不包含阴影的宽度)
    void setDoubleClickMaxsize(bool enabled, int height=20);

protected:
    virtual void mousePressEvent(QMouseEvent *event);

    virtual void mouseMoveEvent(QMouseEvent *event);

    virtual void mouseReleaseEvent(QMouseEvent *event);

    virtual void mouseDoubleClickEvent(QMouseEvent* event);

    // 重写实现调节窗口大小
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result);

    // 重写实现窗口边框阴影效果
    virtual void paintEvent(QPaintEvent *event);

private:
#ifdef Platform_Win
    // 使能调节窗口大小
    bool    _resizeEnabled;
#else
    // 是否按下鼠标
    bool    _drag;
    // 拖动位置
    QPoint    _dragPosition;
#endif

    // 使能边框显示阴影
    bool    _shadeEnabled;

    // 使能阴影圆角
    bool    _shadeRoundEnabled;

    // 使能双击切换窗口大小
    bool    _doubleClickedMaxEnabled;

    // 双击区域高度
    int    _doubleClickHeight;

#ifdef UseShadePictureMode
    QList<QPixmap> shadowPixmapList;
#endif
};

#endif // FRAMELESSWINDOW_H
