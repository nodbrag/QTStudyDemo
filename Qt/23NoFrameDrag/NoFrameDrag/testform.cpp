#include "testform.h"
#include "ui_testform.h"

TestForm::TestForm(QWidget *parent) :
    FramelessWindow(parent),
    ui(new Ui::TestForm)
{
    ui->setupUi(this);

    connect(ui->pushButton_max, SIGNAL(clicked()), this, SLOT(showMaximized()));
    connect(ui->pushButton_normal, SIGNAL(clicked()), this, SLOT(showNormal()));
    connect(ui->pushButton_min, SIGNAL(clicked()), this, SLOT(showMinimized()));
}

TestForm::~TestForm()
{
    delete ui;
}
