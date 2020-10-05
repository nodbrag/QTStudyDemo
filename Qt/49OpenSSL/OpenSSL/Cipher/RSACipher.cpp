#include "RSACipher.h"
#include <QDataStream>

RSACipher::RSACipher()
{
}

/**
 * @brief RSACipher::generateKeyPair
 * 生成密钥对，并分别保存为文件
 * @param privateKeyFile 私钥文件名
 * @param publicKeyFile 公钥文件名
 * @param bits 秘钥长度
 */
void RSACipher::generateKeyPair(const QString &privateKeyFile, const QString &publicKeyFile, int bits)
{
    // 生成公钥
    RSA* rsa = RSA_generate_key(bits, RSA_F4, nullptr, nullptr);
    BIO *bp = BIO_new(BIO_s_file());
    BIO_write_filename(bp, (void*)publicKeyFile.toStdString().c_str());
    PEM_write_bio_RSAPublicKey(bp, rsa);
    BIO_free_all(bp);

    // 生成私钥
    bp = BIO_new(BIO_s_file());
    BIO_write_filename(bp, (void*)privateKeyFile.toStdString().c_str());
    PEM_write_bio_RSAPrivateKey(bp, rsa, nullptr, nullptr, 0, nullptr, nullptr);
    CRYPTO_cleanup_all_ex_data();
    BIO_free_all(bp);
    RSA_free(rsa);
}

/**
 * @brief RSACipher::generateKeyPair
 * 生成密钥对
 * @param privateKey 用于保存私钥内容的缓存
 * @param publicKey 用于保存公钥内容的缓存
 * @param bits 秘钥长度
 */
void RSACipher::generateKeyPair(QByteArray &privateKey, QByteArray &publicKey, int bits)
{
    // 生成密钥对
    RSA *keyPair = RSA_generate_key(bits, RSA_F4, nullptr, nullptr);

    BIO *pri = BIO_new(BIO_s_mem());
    BIO *pub = BIO_new(BIO_s_mem());

    PEM_write_bio_RSAPrivateKey(pri, keyPair, nullptr, nullptr, 0, nullptr, nullptr);
    PEM_write_bio_RSAPublicKey(pub, keyPair);

    // 获取长度
    int pri_len = BIO_pending(pri);
    int pub_len = BIO_pending(pub);

    privateKey.resize(pri_len);
    publicKey.resize(pub_len);

    BIO_read(pri, privateKey.data(), pri_len);
    BIO_read(pub, publicKey.data(), pub_len);

    // 内存释放
    RSA_free(keyPair);
    BIO_free_all(pub);
    BIO_free_all(pri);
}

RSA *RSACipher::generateKeyPair(int bits)
{
    return RSA_generate_key(bits, RSA_F4, nullptr, nullptr);
}

RSA *RSACipher::readPrivateKey(const QString &privateKeyFile)
{
    // 读取私钥文件
    BIO* pBio = BIO_new_file(privateKeyFile.toStdString().c_str(), "r");
    if (pBio == nullptr)
    {
        return nullptr;
    }
    RSA* rsa = PEM_read_bio_RSAPrivateKey(pBio, nullptr, nullptr, nullptr);
    BIO_free_all(pBio);
    return rsa;
}

RSA *RSACipher::readPublicKey(const QString &publicKeyFile)
{
    // 读取公钥文件
    BIO* pBio = BIO_new_file(publicKeyFile.toStdString().c_str(), "r");
    if (pBio == nullptr)
    {
        return nullptr;
    }
    RSA* rsa = PEM_read_bio_RSAPublicKey(pBio, nullptr, nullptr, nullptr);
    BIO_free_all(pBio);
    return rsa;
}

void RSACipher::freeRSA(RSA *rsa)
{
    RSA_free(rsa);
}

/**
 * @brief RSACipher::public_encrypt
 * RSA公钥加密函数，读取公钥文件内容，并进行加密，其输出加密内容使用私钥进行解密
 * @param in 输入数据（明文）
 * @param out 输出数据（密文）
 * @param publicKey 公钥
 * @return
 */
bool RSACipher::public_encrypt(const QByteArray &in, QByteArray &out, RSA* publicKey)
{
    // 对任意长度数据进行加密，超长时，进行分段加密
    int keySize = RSA_size(publicKey);
    int dataLen = in.size();
    const unsigned char *from = (const unsigned char *)in.data();
    QByteArray to(keySize, 0);
    int readLen = 0;
    do
    {
        int select = (keySize - 11) > dataLen ? dataLen : (keySize - 11);
        RSA_public_encrypt(select, (from + readLen), (unsigned char *)to.data(), publicKey, RSA_PKCS1_PADDING);

        dataLen -= select;
        readLen += select;
        out.append(to);
    }while (dataLen > 0);
    return true;
}

/**
 * @brief RSACipher::private_decrypt
 * RSA私钥解密函数。读取私钥文件内容，并进行解密。
 * @param in 输入数据（密文）
 * @param out 输出数据（解密后的内容）
 * @param privateKey 私钥
 * @return
 */
bool RSACipher::private_decrypt(const QByteArray &in, QByteArray &out, RSA* privateKey)
{
    // 对任意长度数据进行解密，超长时，进行分段解密
    int keySize = RSA_size(privateKey);
    int dataLen = in.size();
    const unsigned char *from = (const unsigned char *)in.data();
    QByteArray to(keySize, 0);
    int readLen = 0;
    do
    {
        int size = RSA_private_decrypt(keySize, (from + readLen), (unsigned char *)to.data(), privateKey, RSA_PKCS1_PADDING);

        dataLen -= keySize;
        readLen += keySize;

        out.append(to.data(), size);
    }while (dataLen > 0);
    return true;
}

/**
 * @brief RSACipher::sign
 * 使用私钥对消息数据进行签名
 * @param msg 明文数据
 * @param signMsg 签名后的数据
 * @param privateKey 私钥
 * @return
 */
bool RSACipher::sign(const QByteArray &msg, QByteArray &signMsg, RSA* privateKey)
{
    // 对msg进行签名
    unsigned int siglen = 0;
    QByteArray temp(RSA_size(privateKey), 0);
    RSA_sign(NID_sha1, (const unsigned char*)msg.data(), msg.size(),
             (unsigned char*)temp.data(), &siglen, privateKey);

    signMsg.append(temp.data(), siglen);
    return true;
}

/**
 * @brief RSACipher::verify
 * 使用公钥对消息数据进行验签
 * @param msg 明文数据
 * @param signMsg 签名后的数据
 * @param publicKey 公钥
 * @return
 */
bool RSACipher::verify(const QByteArray &msg, QByteArray &signMsg, RSA* publicKey)
{
    // 对msg、signMsg进行验签
    int ret = RSA_verify(NID_sha1, (const unsigned char*)msg.data(), msg.size(),
               (const unsigned char *)signMsg.data(), signMsg.size(), publicKey);
    return (ret == 1);
}
