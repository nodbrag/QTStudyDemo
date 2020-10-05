#ifndef AESCIPHER_H
#define AESCIPHER_H

#include <QByteArray>
#include <openssl/aes.h>

/**
 * @brief The AESCipher class
 * AES加密算法，包括AES下多种加密模式的实现，底层调用openssl。
 */
class AESCipher
{
public:
    AESCipher();

    bool cbc_encrypt(const QByteArray& in, QByteArray& out,
                     const QByteArray &key, const QByteArray& ivec = QByteArray(16, 0));
    bool cbc_decrypt(const QByteArray& in, QByteArray& out,
                     const QByteArray &key, const QByteArray& ivec = QByteArray(16, 0));

    bool ecb_encrypt(const QByteArray& in, QByteArray& out,
                     const QByteArray &key);
    bool ecb_decrypt(const QByteArray& in, QByteArray& out,
                     const QByteArray &key);

    bool cfb128_encrypt(const QByteArray& in, QByteArray& out,
                        const QByteArray &key, const QByteArray& ivec);
    bool cfb128_decrypt(const QByteArray& in, QByteArray& out,
                        const QByteArray &key, const QByteArray& ivec);

    bool cfb8_encrypt(const QByteArray& in, QByteArray& out,
                      const QByteArray &key, const QByteArray& ivec);
    bool cfb8_decrypt(const QByteArray& in, QByteArray& out,
                      const QByteArray &key, const QByteArray& ivec);

    bool cfb1_encrypt(const QByteArray& in, QByteArray& out,
                      const QByteArray &key, const QByteArray& ivec);
    bool cfb1_decrypt(const QByteArray& in, QByteArray& out,
                      const QByteArray &key, const QByteArray& ivec);

    static int getPKCS7PaddedLength(int dataLen);

private:
    bool keyIsLegal(const QByteArray& key);
    bool generateEncryptKey(const QByteArray &key, AES_KEY& aes_key);
    bool generateDecryptKey(const QByteArray &key, AES_KEY& aes_key);
    QByteArray PKCS7Padding(const QByteArray &in);
    QByteArray PKCS7UnPadding(const QByteArray &in);
};

#endif // AESCIPHER_H
