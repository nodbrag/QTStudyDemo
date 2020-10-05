#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    ui->horizontalLayout_3->setSizeConstraint(QLayout::SetFixedSize);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    if (ui->widget->isVisible())
    {
        ui->widget->setVisible(false);
    }
    else
        ui->widget->setVisible(true);
}
