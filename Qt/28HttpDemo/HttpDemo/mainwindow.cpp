#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _networkAccessManager = new QNetworkAccessManager(this);
    _networkAccessManager->setCookieJar(new QNetworkCookieJar(this));
    connect(_networkAccessManager,SIGNAL(finished(QNetworkReply*)),this,SLOT(slot_requestFinished(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sendGetRequest(const QUrl &url)
{
    mUrl = url;
    QNetworkRequest r(url);
    r.setRawHeader("Cookie", "ew=123");
    _networkAccessManager->get(r);

    printRequestData(&r);
}

void MainWindow::printRequestData(QNetworkRequest* request)
{
    QList<QByteArray> headerList = request->rawHeaderList();
    qDebug() << headerList;
}

void MainWindow::printReplyData(QNetworkReply *reply)
{
    const QList<QNetworkReply::RawHeaderPair>& headerList = reply->rawHeaderPairs();
    for (int i = 0; i < headerList.size(); i++)
    {
        QString name = headerList.at(i).first;
        QString value = headerList.at(i).second;
        qDebug() << QString("%1:%2").arg(name).arg(value);
    }
}

void MainWindow::slot_requestFinished(QNetworkReply *reply)
{
    if (reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "ERROR:" << reply->errorString();
        return;
    }

    QList<QNetworkCookie>  cookies = _networkAccessManager->cookieJar()->cookiesForUrl(mUrl);
    qDebug() << "COOKIES for" << mUrl.host() << cookies;

    printReplyData(reply);

//    QVariant xxx = reply->header(QNetworkRequest::SetCookieHeader);
//    QList<QNetworkCookie> cookies1 = xxx.value< QList<QNetworkCookie> >();

    QString str = reply->readAll();

    ui->textEdit->setPlainText(str);

    reply->deleteLater();
}

void MainWindow::on_pushButton_clicked()
{
    sendGetRequest(QUrl(ui->lineEdit->text()));
}
