#ifndef QRCODEHANDLER_H
#define QRCODEHANDLER_H
#include <QImage>
#include "BaseHandler.h"

/**
 * @brief 获取登陆二维码
 */
class QRCodeHandler : public BaseHandler
{
    Q_OBJECT
public:
    QRCodeHandler(QNetworkAccessManager *manager);
    ~QRCodeHandler();

    virtual void runHandle();

protected:
    virtual void requestFinished(QNetworkReply *reply, const QByteArray& data, int statusCode);

signals:
    // 获取二维码成功
    void signal_getQRCodeImageSucceed(const QImage& img);
};

#endif // QRCODEHANDLER_H
