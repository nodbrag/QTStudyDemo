#ifndef PERSONLISTBUDDY_H
#define PERSONLISTBUDDY_H

#include <QWidget>
#include <QPixmap>

class QLabel;
class QEvent;

//自定义信息Item类
class PersonListBuddy :
        public QWidget
{
    Q_OBJECT
public:
    explicit PersonListBuddy(QWidget *parent = 0);

    QString getName() const;
    void setName(const QString& str);

    QString getSign() const;
    void setSign(const QString& str);

    QPixmap headPixmap() const;
    void setHeadPixmap(const QPixmap &headPixmap);

protected:
    bool eventFilter(QObject *obj, QEvent *event);//事件过滤器
    
private:
    void initUi();//初始化Ui

private:
    QWidget*    _headWidget;  //头像
    QPixmap    _headPixmap;  // 头像数据
    QLabel*    _nameLabel;  //用户名
    QLabel*    _signLabel;  //个性签名
};

#endif // PERSONLISTBUDDY_H
