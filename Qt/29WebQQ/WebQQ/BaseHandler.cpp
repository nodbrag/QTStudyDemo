#include "BaseHandler.h"

#define USER_AGENT                  "Mozilla/5.0 (Windows NT 6.1; rv:57.0) Gecko/20100101 Firefox/57.0"
#define ACCEPT                      "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8"
#define ACCEPT_LANGUAGE             "zh-CN,zh;q=0.8,zh-TW;q=0.7,zh-HK;q=0.5,en-US;q=0.3,en;q=0.2"
#define ACCEPT_ENCODING             "gzip, deflate"
#define CONNECTION                  "keep-alive"
#define UPGRADE_INSECURE_REQUESTS   "1"
#define CACHE_CONTROL               "max-age=0"

BaseHandler::BaseHandler(QNetworkAccessManager *manager)
    : QObject(manager),
      _handler(NULL)
{
    httpRequest.setRawHeader("User-Agent", USER_AGENT);
    httpRequest.setRawHeader("Accept", ACCEPT);
    httpRequest.setRawHeader("Accept-Language", ACCEPT_LANGUAGE);
    httpRequest.setRawHeader("Accept-Encoding", ACCEPT_ENCODING);
    httpRequest.setRawHeader("Connection", CONNECTION);
    httpRequest.setRawHeader("Upgrade-Insecure-Requests", UPGRADE_INSECURE_REQUESTS);
    httpRequest.setRawHeader("Cache-Control", CACHE_CONTROL);
}

BaseHandler::~BaseHandler()
{

}

void BaseHandler::setNextHandler(BaseHandler *handler)
{
    _handler = handler;
}

void BaseHandler::setCookie(const QByteArray &cookie)
{
    httpRequest.setRawHeader("Set-Cookie", cookie);
}

void BaseHandler::setReferer(const QByteArray &referer)
{
    httpRequest.setRawHeader("Referer", referer);
}

void BaseHandler::get(const QUrl &url)
{
    httpRequest.setUrl(url);
    QNetworkReply* reply = ((QNetworkAccessManager*)parent())->get(httpRequest);
    connect(reply, SIGNAL(finished()), this, SLOT(serviceRequestFinished()));

#ifdef PRINT_REQUEST_HEADER
    printRequestHeader(&httpRequest);
#endif
}

void BaseHandler::post(const QUrl &url, const QByteArray &data)
{
    httpRequest.setUrl(url);
    QNetworkReply* reply = ((QNetworkAccessManager*)parent())->post(httpRequest, data);
    connect(reply, SIGNAL(finished()), this, SLOT(serviceRequestFinished()));

#ifdef PRINT_REQUEST_HEADER
    printRequestHeader(&httpRequest);
#endif
}

void BaseHandler::setTimeOut(int ms)
{

}

void BaseHandler::printRequestHeader(QNetworkRequest *request)
{
    QList<QByteArray> headerList = request->rawHeaderList();
    for (int i = 0; i < headerList.size(); i++)
    {
        QByteArray name = headerList.at(i);
        QByteArray value = request->rawHeader(name);
        qDebug() << QString("%1:%2").arg(QString(name)).arg(QString(value));
    }
}

void BaseHandler::printReplyHeader(QNetworkReply *reply)
{
    const QList<QNetworkReply::RawHeaderPair>& headerList = reply->rawHeaderPairs();
    for (int i = 0; i < headerList.size(); i++)
    {
        QString name = headerList.at(i).first;
        QString value = headerList.at(i).second;
        qDebug() << QString("%1:%2").arg(name).arg(value);
    }
}

void BaseHandler::serviceRequestFinished()
{
    QNetworkReply* reply = (QNetworkReply*)sender();
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

#ifdef PRINT_RESPONSE_HEADER
    printReplyHeader(reply);
#endif

    if(reply->error() == QNetworkReply::NoError) // ok
    {
        requestFinished(reply, reply->readAll(), statusCode);

        if (statusCode == 200)
        {
            // 执行下一条handler
            if (_handler != NULL)
            {
                _handler->runHandle();
            }
        }
    }
    else    // error
    {
        requestFinished(reply, "", statusCode);
        qDebug() << reply->errorString();
    }

    reply->deleteLater();
}

