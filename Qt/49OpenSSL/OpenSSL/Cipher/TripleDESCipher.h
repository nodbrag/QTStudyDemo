#ifndef TRIPLEDESCIPHER_H
#define TRIPLEDESCIPHER_H

#include <QByteArray>

/**
 * @brief The TripleDESCipher class
 * TripleDES算法相关实现
 * key必须是24字节
 * ivec必须是8字节
 */
class TripleDESCipher
{
public:
    TripleDESCipher();

public:
    // ecb模式
    bool ecb3_encrypt(const QByteArray& in, QByteArray& out, const QByteArray& key);
    bool ecb3_decrypt(const QByteArray& in, QByteArray& out, const QByteArray& key);

    // cbc模式
    bool ede3_cbc_encrypt(const QByteArray& in, QByteArray& out, const QByteArray& key, const QByteArray& ivec);
    bool ede3_cbc_decrypt(const QByteArray& in, QByteArray& out, const QByteArray& key, const QByteArray& ivec);

    // cfb1模式
    bool ede3_cfb_encrypt(const QByteArray& in, QByteArray& out, const QByteArray& key, const QByteArray& ivec);
    bool ede3_cfb_decrypt(const QByteArray& in, QByteArray& out, const QByteArray& key, const QByteArray& ivec);

    // cfb64模式
    bool ede3_cfb64_encrypt(const QByteArray& in, QByteArray& out, const QByteArray& key, const QByteArray& ivec);
    bool ede3_cfb64_decrypt(const QByteArray& in, QByteArray& out, const QByteArray& key, const QByteArray& ivec);

    // ofb64模式
    bool ede3_ofb64_encrypt(const QByteArray& in, QByteArray& out, const QByteArray& key, const QByteArray& ivec);
    bool ede3_ofb64_decrypt(const QByteArray& in, QByteArray& out, const QByteArray& key, const QByteArray& ivec);

private:
    bool ecb3_encrypt(const QByteArray& in, QByteArray& out, const QByteArray& key, int enc);
    bool ede3_cbc_encrypt(const QByteArray& in, QByteArray& out, const QByteArray& key, const QByteArray& ivec, int enc);
    bool ede3_cfb_encrypt(const QByteArray& in, QByteArray& out, const QByteArray& key, const QByteArray& ivec, int enc);
    bool ede3_cfb64_encrypt(const QByteArray& in, QByteArray& out, const QByteArray& key, const QByteArray& ivec, int enc);
    bool ede3_ofb64_encrypt(const QByteArray& in, QByteArray& out, const QByteArray& key, const QByteArray& ivec, int enc);

public:
    const static int DES_BLOCK_SIZE = 8;
};

#endif // TRIPLEDESCIPHER_H
