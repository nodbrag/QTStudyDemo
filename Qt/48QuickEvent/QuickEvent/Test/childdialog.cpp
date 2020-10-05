#include "childdialog.h"
#include "ui_childdialog.h"
#include <QDateTime>
#include "quickapplication.h"
#include "student.h"

ChildDialog::ChildDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChildDialog)
{
    ui->setupUi(this);
}

ChildDialog::~ChildDialog()
{
    delete ui;
}

void ChildDialog::on_pushButton_clicked()
{
    auto time = QDateTime::currentDateTime();
    QuickApplication::publishEvent("show_time", Qt::AutoConnection, time);
}

void ChildDialog::on_pushButton_2_clicked()
{
    Student student;
    student.name_ = "xiaodong";
    student.id_ = "123";
    QuickApplication::publishEvent("student_event", Qt::AutoConnection, student);
}

void ChildDialog::on_pushButton_3_clicked()
{
    QuickApplication::publishEvent("cross_thread", Qt::AutoConnection, QString("test"));
}
