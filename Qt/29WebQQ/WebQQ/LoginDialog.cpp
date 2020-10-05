#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include <QNetworkCookieJar>
#include "QRCodeHandler.h"
#include "LoginHandler.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    mainwindow = new MainWindow(this);

    _networkAccessManager = new QNetworkAccessManager(this);
    _networkAccessManager->setCookieJar(new QNetworkCookieJar(this));

    QRCodeHandler* handler = new QRCodeHandler(_networkAccessManager);
    connect(handler, SIGNAL(signal_getQRCodeImageSucceed(QImage)),
            this, SLOT(slot_getQRCodeImageSucceed(QImage)));
    handler->runHandle();

    connect(&_timer, SIGNAL(timeout()), this, SLOT(slot_detectLoginStatus()));
    _timer.setInterval(1000);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::slot_getQRCodeImageSucceed(const QImage &img)
{
    ui->label_img->setPixmap(QPixmap::fromImage(img));
//    _timer.start();
}

void LoginDialog::slot_detectLoginStatus()
{
    LoginHandler* handler = new LoginHandler(_networkAccessManager);
    handler->runHandle();
}
