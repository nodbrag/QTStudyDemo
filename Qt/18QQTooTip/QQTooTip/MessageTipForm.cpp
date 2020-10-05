#include "MessageTipForm.h"
#include "ui_MessageTipForm.h"
#include <QResizeEvent>
#include <QMessageBox>

#define  MessageCountRole       (Qt::UserRole+0x01)
#define  MessageTextRole        (Qt::UserRole+0x02)

MessageTipForm::MessageTipForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageTipForm)
{
    ui->setupUi(this);

    _orignalHeight = this->height();

    ui->listWidget_msg->setFocusPolicy(Qt::NoFocus);       // 去除item选中时的虚线边框

    setWindowFlags(Qt::Window|Qt::FramelessWindowHint|Qt::WindowTitleHint|Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint);

    connect(ui->listWidget_msg, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slot_itemClicked(QListWidgetItem*)));

    connect(ui->pushButton_ignoreAll, SIGNAL(clicked()), this, SLOT(slot_ignoreAll()));
    connect(ui->pushButton_openAll, SIGNAL(clicked()), this, SLOT(slot_openAll()));
}

MessageTipForm::~MessageTipForm()
{
    delete ui;
}

void MessageTipForm::addToTipList(const QString &name, const QString& text)
{
    QListWidgetItem* item = new QListWidgetItem(ui->listWidget_msg);
    item->setText(QString("  %1").arg(name));  // 前面空格占位
    item->setData(MessageTextRole, text);
    ui->listWidget_msg->addItem(item);

    // 显示收到消息用户数量
    ui->label_msgTotal->setText(QString("新消息(%1)").arg(getUserCount()));

    // 修改消息盒子的长度，每增加一条消息，增加34pix
    this->resizeHeight(this->height() + 34);
}

int MessageTipForm::getUserCount()
{
    return ui->listWidget_msg->count();
}

void MessageTipForm::setFixedLeftBottom(const QPoint &leftBottom)
{
    _orignalPoint = leftBottom;
}

void MessageTipForm::slot_itemClicked(QListWidgetItem *item)
{
    if (item == NULL)
        return;

    QString text = item->data(MessageTextRole).toString();

    ui->listWidget_msg->removeItemWidget(item);
    delete item;

    // 修改消息盒子的长度，每阅读一条消息，减少34pix
    this->resizeHeight(this->height() - 34);

    QMessageBox::warning(NULL, "消息", text);

    if (getUserCount() == 0)
        emit signal_NoMessage();
}

void MessageTipForm::slot_ignoreAll()
{
    for (int i = ui->listWidget_msg->count()-1; i >= 0; i--)
    {
        QListWidgetItem* item = ui->listWidget_msg->item(i);
        ui->listWidget_msg->removeItemWidget(item);
        delete item;
    }

    // 修改消息盒子的长度，恢复最初的高度
    this->resizeHeight(_orignalHeight);
    emit signal_NoMessage();
}

void MessageTipForm::slot_openAll()
{
    for (int i = ui->listWidget_msg->count()-1; i >= 0; i--)
    {
        QListWidgetItem* item = ui->listWidget_msg->item(i);
        slot_itemClicked(item);
    }
    emit signal_NoMessage();
}

void MessageTipForm::resizeHeight(int h)
{
    this->resize(this->width(), h);
    // 根据新的大小移动窗口至原始位置
    QPoint leftTop = QPoint(_orignalPoint.x(),
                            _orignalPoint.y() - h + 1);
    this->move(leftTop);
}
