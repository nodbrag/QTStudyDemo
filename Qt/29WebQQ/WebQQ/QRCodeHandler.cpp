#include "QRCodeHandler.h"

QRCodeHandler::QRCodeHandler(QNetworkAccessManager *manager)
    :BaseHandler(manager)
{

}

QRCodeHandler::~QRCodeHandler()
{

}

void QRCodeHandler::runHandle()
{
    // 怎么获取qrsig值，这个值几分钟后就会过期
    QUrl url("https://ssl.ptlogin2.qq.com/ptqrshow?appid=501004106&e=2&l=M&s=3&d=72&v=4&t=0.2966802910064531&daid=164&pt_3rd_aid=0");
//    setCookie("qrsig=gZHc*2E1*KSpmhmsMB5GLozya5sfsUswZvZHHJjHmZCAM57AUfhOhT0QxHavQ3WQ; pgv_pvi=3103341568; pgv_si=s2790406144");
    get(url);
}

void QRCodeHandler::requestFinished(QNetworkReply *reply, const QByteArray& data, int statusCode)
{
    if (statusCode == 200)
    {
        emit signal_getQRCodeImageSucceed(QImage::fromData(data));
    }
}

