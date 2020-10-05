#ifndef BASEHANDLER_H
#define BASEHANDLER_H
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

#define PRINT_REQUEST_HEADER
#define PRINT_RESPONSE_HEADER

class BaseHandler : public QObject
{
    Q_OBJECT
public:
    BaseHandler(QNetworkAccessManager *manager=0);
    ~BaseHandler();

    void setCookie(const QByteArray &cookie);
    void setReferer(const QByteArray &referer);

    void get(const QUrl& url);
    void post(const QUrl& url, const QByteArray& data);

    void setTimeOut(int ms);

private:
    void printRequestHeader(QNetworkRequest *request);
    void printReplyHeader(QNetworkReply *reply);

protected:
    virtual void requestFinished(QNetworkReply *reply, const QByteArray data, const int statusCode) = 0;

private slots:
    void serviceRequestFinished();

private:
    QNetworkRequest httpRequest;
};

#endif // BASEHANDLER_H
