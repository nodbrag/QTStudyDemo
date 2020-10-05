#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QFile>

class MyLineEdit : public QLineEdit
{
public:
    MyLineEdit(QWidget *parent = nullptr)
        :QLineEdit(parent)
    {}
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //1类型选择器
    //qApp->setStyleSheet("QLineEdit { background-color: yellow; }");

    //2通用选择器
    //qApp->setStyleSheet("* { background-color: yellow; }");

    //3-1类选择器
//    QLineEdit* lineEdit = new QLineEdit(ui->centralWidget);
//    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
//    lineEdit->setGeometry(QRect(50, 60, 113, 20));
//    lineEdit->setText("QLineEdit");
//    MyLineEdit* myLineEdit = new MyLineEdit(ui->centralWidget);
//    myLineEdit->setObjectName(QString::fromUtf8("myLineEdit"));
//    myLineEdit->setGeometry(QRect(180, 60, 113, 20));
//    myLineEdit->setText("MyLineEdit");
//    qApp->setStyleSheet("QLineEdit { background-color: yellow; }");

    //3-2类选择器
//    QLineEdit* lineEdit = new QLineEdit(ui->centralWidget);
//    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
//    lineEdit->setGeometry(QRect(50, 60, 113, 20));
//    lineEdit->setText("QLineEdit");
//    qApp->setStyleSheet(".test { background-color: yellow; }");
//    lineEdit->setProperty("class",  "test");

    //4ID选择器
//    QLineEdit* lineEdit1 = new QLineEdit(ui->centralWidget);
//    lineEdit1->setObjectName(QString::fromUtf8("lineEdit1"));
//    lineEdit1->setGeometry(QRect(50, 60, 113, 20));
//    lineEdit1->setText("LineEdit1");
//    QLineEdit* lineEdit2 = new QLineEdit(ui->centralWidget);
//    lineEdit2->setObjectName(QString::fromUtf8("lineEdit2"));
//    lineEdit2->setGeometry(QRect(180, 60, 113, 20));
//    lineEdit2->setText("lineEdit2");
//    qApp->setStyleSheet("#lineEdit1, #lineEdit2 { background-color: green; }");
//    qApp->setStyleSheet("#lineEdit1 { background-color: yellow; }"
//                        "#lineEdit2 { background-color: red; }");

    //5属性选择器
//    QLineEdit* lineEdit1 = new QLineEdit(ui->centralWidget);
//    lineEdit1->setObjectName(QString::fromUtf8("lineEdit1"));
//    lineEdit1->setGeometry(QRect(50, 60, 113, 20));
//    lineEdit1->setText("lineEdit1");
//    QLineEdit* lineEdit2 = new QLineEdit(ui->centralWidget);
//    lineEdit2->setObjectName(QString::fromUtf8("lineEdit2"));
//    lineEdit2->setGeometry(QRect(180, 60, 113, 20));
//    lineEdit2->setText("lineEdit2");
//    qApp->setStyleSheet("QLineEdit[bkColor='red'] { background-color: red; }"
//                        "QLineEdit[bkColor='green'] { background-color: green; }");
//    lineEdit1->setProperty("bkColor", "red");
//    lineEdit2->setProperty("bkColor", "green");

    //6包含选择器
//    QLineEdit* lineEdit1 = new QLineEdit(ui->centralWidget);
//    lineEdit1->setObjectName(QString::fromUtf8("lineEdit1"));
//    lineEdit1->setGeometry(QRect(50, 60, 113, 20));
//    lineEdit1->setText("lineEdit1");
//    QWidget* widget = new QWidget(ui->centralWidget);
//    QLineEdit* lineEdit2 = new QLineEdit(widget);
//    lineEdit2->setObjectName(QString::fromUtf8("lineEdit2"));
//    lineEdit2->setGeometry(QRect(180, 60, 113, 20));
//    lineEdit2->setText("lineEdit2");
//    ui->centralWidget->setStyleSheet("QWidget QLineEdit { background-color: red; }");

    //7子元素选择器
//    QLineEdit* lineEdit1 = new QLineEdit(ui->centralWidget);
//    lineEdit1->setObjectName(QString::fromUtf8("lineEdit1"));
//    lineEdit1->setGeometry(QRect(50, 60, 113, 20));
//    lineEdit1->setText("lineEdit1");
//    QLineEdit* lineEdit2 = new QLineEdit(this);
//    lineEdit2->setObjectName(QString::fromUtf8("lineEdit2"));
//    lineEdit2->setGeometry(QRect(180, 60, 113, 20));
//    lineEdit2->setText("lineEdit2");
//    this->setStyleSheet("QMainWindow > QLineEdit { background-color: red; }");

    //8伪类选择器
//    QPushButton* btn = new QPushButton("test1", ui->centralWidget);
//    btn->setStyleSheet("QPushButton:pressed { color: red; }"
//                       "QPushButton:!pressed { color: green; }");
//    btn->setStyleSheet("QPushButton:focus:pressed { color: yellow; }");

    //9Subcontrol选择器
//    QCheckBox* check = new QCheckBox("test", ui->centralWidget);
//    check->setStyleSheet("QCheckBox::indicator:checked { image: url(:/res/check.png); }"
//                         "QCheckBox::indicator:unchecked { image: url(:/res/uncheck.png); }");

    //10qss文件加载
    loadQssFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadQssFile()
{
    QFile file(":/res/test.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qApp->setStyleSheet(file.readAll());
        file.close();
    }
}
