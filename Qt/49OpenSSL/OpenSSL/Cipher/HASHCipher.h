#ifndef HASHCIPHER_H
#define HASHCIPHER_H

#include <QObject>
#include <QMetaEnum>
#include <QString>
#include <QByteArray>
#include <openssl/sha.h>

/**
 * @brief The HASHCipher class
 * HASH加密算法实现类，包括Sha、Sha1、Sha224等。
 */
class HASHCipher : public QObject
{
    Q_OBJECT

public:
    enum Mode
    {
        SHA1,
        SHA224,
        SHA256,
        SHA384,
        SHA512,
        RIPEMD160,
        MD5
    };
    Q_ENUM(Mode)

    HASHCipher(Mode mode);

    void addData(const QByteArray &data);
    QByteArray result();

private:
    QString modeToString(Mode value);

private:
    Mode _mode;   ///<HASH算法类型
    QByteArray _data;   ///<待加密数据
};

#endif // HASHCIPHER_H
