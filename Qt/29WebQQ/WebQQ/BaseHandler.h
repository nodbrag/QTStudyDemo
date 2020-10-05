#ifndef BASEHANDLER_H
#define BASEHANDLER_H
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

//#define PRINT_REQUEST_HEADER
//#define PRINT_RESPONSE_HEADER

class BaseHandler : public QObject
{
    Q_OBJECT
public:
    BaseHandler(QNetworkAccessManager *manager);
    ~BaseHandler();

    void setNextHandler(BaseHandler* handler);

    virtual void runHandle() = 0;

protected:
    void setCookie(const QByteArray &cookie);
    void setReferer(const QByteArray &referer);

    void get(const QUrl& url);
    void post(const QUrl& url, const QByteArray& data);

    void setTimeOut(int ms);

private:
    void printRequestHeader(QNetworkRequest *request);
    void printReplyHeader(QNetworkReply *reply);

protected:
    virtual void requestFinished(QNetworkReply *reply, const QByteArray& data, int statusCode) = 0;

private slots:
    void serviceRequestFinished();

private:
    QNetworkRequest httpRequest;
    BaseHandler* _handler;
};

#endif // BASEHANDLER_H

/*
// 易语言精易模块封装方式
// 阻塞访问后返回服务器的response网页内容
QString webVisitObject(QString url,                 // 网址
                       int style,                   // get,post,head,...
                       QString param,               // style=post时有效
                       QString commitCookie,        // 提交Cookie
                       QString returnCookie,        // 返回Cookie，一般不填写
                       QString AddHeader,           // 附加协议头
                       QString returnHeader,        // 返回协议头
                       int returnStatusCode,        // 返回状态码
                       bool forbidenRedirect,       // 禁止重定向
                       QByteArray content,          // 字节集提交
                       QString proxyAddr,           // 代理地址
                       int timeOut,                 // 超时
                       QString user,                // 用户名
                       QString password,            // 密码
                       QString proxyFlag,           // 代理标识
                       );
*/


