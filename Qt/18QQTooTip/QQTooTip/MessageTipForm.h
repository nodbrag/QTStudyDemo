#ifndef MESSAGETIPFORM_H
#define MESSAGETIPFORM_H

#include <QDialog>

namespace Ui {
class MessageTipForm;
}
class QListWidgetItem;

class MessageTipForm : public QDialog
{
    Q_OBJECT

public:
    explicit MessageTipForm(QWidget *parent = 0);
    ~MessageTipForm();

    // 添加收到消息至提示框
    void addToTipList(const QString& name, const QString &text);

    // 获取收到消息的用户数量
    int getUserCount();

    // 设置固定的左下角坐标，必须在构造函数之后，马上调用，设置固定位置
    void setFixedLeftBottom(const QPoint& leftBottom);

private slots:
    void slot_itemClicked(QListWidgetItem* item);

    void slot_ignoreAll();

    void slot_openAll();

signals:
    // 没有消息了
    void signal_NoMessage();

private:
    // 保证窗口左下角位置始终固定
    void resizeHeight(int h);

private:
    Ui::MessageTipForm *ui;

    // 消息盒子窗口最初高度
    int    _orignalHeight;

    // 消息盒子的最初左下角的位置，由于消息盒子只会改变高度，不会改变宽度，所以此位置固定
    QPoint    _orignalPoint;
};

#endif // MESSAGETIPFORM_H
