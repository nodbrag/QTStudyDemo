#include "QDateTimeEditTest.h"
#include "ui_qdatetimeedittest.h"
#include "QToolTip/qtooltip.h"

QDateTimeEditTest::QDateTimeEditTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QDateTimeEditTest)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(slot_showToolTip()));
    connect(ui->dateTimeEdit, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(slot_showToolTip()));
}

QDateTimeEditTest::~QDateTimeEditTest()
{
    delete ui;
}

void QDateTimeEditTest::slot_showToolTip()
{
    MY_NAMESPACE::QToolTip::showText(QCursor::pos(), "this is a tip!", NULL, QRect(), 1000);
}
