#include "PersonListBuddy.h"
#include <QPainter>
#include <QLabel>
#include <QEvent>

PersonListBuddy::PersonListBuddy(QWidget *parent) :
    QWidget(parent)
{
    initUi();
}

//初始化Ui
void PersonListBuddy::initUi()
{
    //初始化
    _headWidget = new QWidget(this);
    _nameLabel = new QLabel(this);
    _signLabel = new QLabel(this);

    //设置头像大小
    _headWidget->setFixedSize(40, 40);

    //设置个性签名字体为灰色
    QPalette color;
    color.setColor(QPalette::Text,Qt::gray);
    _signLabel->setPalette(color);

    //布局
    _headWidget->move(7,7);
    _nameLabel->move(54,10);
    _signLabel->move(54,27);

    //装载事件过滤器
    _headWidget->installEventFilter(this);
}

QString PersonListBuddy::getName() const
{
    return _nameLabel->text();
}

void PersonListBuddy::setName(const QString& str)
{
    _nameLabel->setText(str);
}

QString PersonListBuddy::getSign() const
{
    return _signLabel->text();
}

void PersonListBuddy::setSign(const QString& str)
{
    _signLabel->setText(str);
}

QPixmap PersonListBuddy::headPixmap() const
{
    return _headPixmap;
}

void PersonListBuddy::setHeadPixmap(const QPixmap &headPixmap)
{
    _headPixmap = headPixmap;
}

//事件过滤器，主要是为了让图片能够全部填充在head里面
bool PersonListBuddy::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == _headWidget)
    {
        if(event->type() == QEvent::Paint)
        {
            QPainter painter(_headWidget);
            painter.drawPixmap(_headWidget->rect(), _headPixmap);
        }
    }
    return QWidget::eventFilter(obj, event);
}
