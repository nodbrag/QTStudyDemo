#ifndef LOGINHANDLER_H
#define LOGINHANDLER_H
#include "BaseHandler.h"

/**
 * @brief 处理登陆请求应答
 */
class LoginHandler : public BaseHandler
{
    Q_OBJECT
public:
    LoginHandler(QNetworkAccessManager *manager);
    ~LoginHandler();

    virtual void runHandle();

protected:
    virtual void requestFinished(QNetworkReply *reply, const QByteArray& data, int statusCode);

};

#endif // LOGINHANDLER_H
