#ifndef RSACIPHER_H
#define RSACIPHER_H

#include <QByteArray>
#include <QString>
#include <openssl/rsa.h>
#include <openssl/pem.h>

/**
 * @brief The RSACipher class
 * RSA算法相关实现，包括密钥对生成，加密与解密，签名与验签。
 */
class RSACipher
{
public:
    RSACipher();

    void generateKeyPair(const QString& privateKeyFile, const QString &publicKeyFile, int bits = 1024);
    void generateKeyPair(QByteArray& privateKey, QByteArray& publicKey, int bits = 1024);

    RSA* generateKeyPair(int bits);

    RSA* readPrivateKey(const QString& privateKeyFile);
    RSA* readPublicKey(const QString& publicKeyFile);
    void freeRSA(RSA* rsa);

    bool public_encrypt(const QByteArray& in, QByteArray& out, RSA* publicKey);
    bool private_decrypt(const QByteArray& in, QByteArray& out, RSA* privateKey);

    bool sign(const QByteArray& msg, QByteArray& signMsg, RSA* privateKey);
    bool verify(const QByteArray& msg, QByteArray& signMsg, RSA* publicKey);
};

#endif // RSACIPHER_H
