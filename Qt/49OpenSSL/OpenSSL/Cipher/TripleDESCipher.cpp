#include "TripleDESCipher.h"
#include <openssl/des.h>
#include "Padding.h"

void setKey(const QByteArray& key, DES_key_schedule& sch1, DES_key_schedule& sch2, DES_key_schedule& sch3)
{
    const_DES_cblock key1, key2, key3;
    memcpy(key1, key.data(), 8);
    memcpy(key2, key.data() + 8, 8);
    memcpy(key3, key.data() + 16, 8);

    DES_set_key_unchecked(&key1, &sch1);
    DES_set_key_unchecked(&key2, &sch2);
    DES_set_key_unchecked(&key3, &sch3);
}

TripleDESCipher::TripleDESCipher()
{

}

/**
 * @brief TripleDESCipher::ecb3_encrypt
 * ecb模式加密
 * @param in 输入数据（明文）
 * @param out 输出数据（密文）
 * @param key 秘钥
 * @return 加密是否成功
 */
bool TripleDESCipher::ecb3_encrypt(const QByteArray &in, QByteArray &out, const QByteArray &key)
{
    // 按8字节对齐，填充明文数据
    QByteArray inTemp = Padding::PKCS7Padding(in, DES_BLOCK_SIZE);
    return ecb3_encrypt(inTemp, out, key, DES_ENCRYPT);
}

/**
 * @brief TripleDESCipher::ecb3_decrypt
 * ecb模式解密
 * @param in 输入数据（密文）
 * @param out 输出数据（明文）
 * @param key 秘钥
 * @return 解密是否成功
 */
bool TripleDESCipher::ecb3_decrypt(const QByteArray &in, QByteArray &out, const QByteArray &key)
{
    bool ret = ecb3_encrypt(in, out, key, DES_DECRYPT);
    out = Padding::PKCS7UnPadding(out);
    return ret;
}

/**
 * @brief TripleDESCipher::ede3_cbc_encrypt
 * cbc模式加密
 * @param in 输入数据（明文）
 * @param out 输出数据（密文）
 * @param key 秘钥
 * @param ivec 初始向量
 * @return 加密是否成功
 */
bool TripleDESCipher::ede3_cbc_encrypt(const QByteArray &in, QByteArray &out, const QByteArray &key, const QByteArray &ivec)
{
    // 按8字节对齐，填充明文数据
    QByteArray inTemp = Padding::PKCS7Padding(in, DES_BLOCK_SIZE);
    return ede3_cbc_encrypt(inTemp, out, key, ivec, DES_ENCRYPT);
}

/**
 * @brief TripleDESCipher::ede3_cbc_decrypt
 * cbc模式解密
 * @param in 输入数据（密文）
 * @param out 输出数据（明文）
 * @param key 秘钥
 * @param ivec 初始向量
 * @return 解密是否成功
 */
bool TripleDESCipher::ede3_cbc_decrypt(const QByteArray &in, QByteArray &out, const QByteArray &key, const QByteArray &ivec)
{
    bool ret = ede3_cbc_encrypt(in, out, key, ivec, DES_DECRYPT);
    out = Padding::PKCS7UnPadding(out);
    return ret;
}

/**
 * @brief TripleDESCipher::ede3_cfb_encrypt
 * cfb模式加密
 * @param in 输入数据（明文）
 * @param out 输出数据（密文）
 * @param key 秘钥
 * @param ivec 初始向量
 * @return 加密是否成功
 */
bool TripleDESCipher::ede3_cfb_encrypt(const QByteArray &in, QByteArray &out, const QByteArray &key, const QByteArray &ivec)
{
    // 按8字节对齐，填充明文数据
    QByteArray inTemp = Padding::PKCS7Padding(in, DES_BLOCK_SIZE);
    return ede3_cfb_encrypt(inTemp, out, key, ivec, DES_ENCRYPT);
}

/**
 * @brief TripleDESCipher::ede3_cfb_decrypt
 * cfb模式解密
 * @param in 输入数据（密文）
 * @param out 输出数据（明文）
 * @param key 秘钥
 * @param ivec 初始向量
 * @return 解密是否成功
 */
bool TripleDESCipher::ede3_cfb_decrypt(const QByteArray &in, QByteArray &out, const QByteArray &key, const QByteArray &ivec)
{
    bool ret = ede3_cfb_encrypt(in, out, key, ivec, DES_DECRYPT);
    out = Padding::PKCS7UnPadding(out);
    return ret;
}

/**
 * @brief TripleDESCipher::ede3_cfb64_encrypt
 * cfb64模式加密
 * @param in 输入数据（明文）
 * @param out 输出数据（密文）
 * @param key 秘钥
 * @param ivec 初始向量
 * @return 加密是否成功
 */
bool TripleDESCipher::ede3_cfb64_encrypt(const QByteArray &in, QByteArray &out, const QByteArray &key, const QByteArray &ivec)
{
    // 按8字节对齐，填充明文数据
    QByteArray inTemp = Padding::PKCS7Padding(in, DES_BLOCK_SIZE);
    return ede3_cfb64_encrypt(inTemp, out, key, ivec, DES_ENCRYPT);
}

/**
 * @brief TripleDESCipher::ede3_cfb64_decrypt
 * cfb64模式解密
 * @param in 输入数据（密文）
 * @param out 输出数据（明文）
 * @param key 秘钥
 * @param ivec 初始向量
 * @return 解密是否成功
 */
bool TripleDESCipher::ede3_cfb64_decrypt(const QByteArray &in, QByteArray &out, const QByteArray &key, const QByteArray &ivec)
{
    bool ret = ede3_cfb64_encrypt(in, out, key, ivec, DES_DECRYPT);
    out = Padding::PKCS7UnPadding(out);
    return ret;
}

/**
 * @brief TripleDESCipher::ede3_ofb64_encrypt
 * ofb64模式加密
 * @param in 输入数据（明文）
 * @param out 输出数据（密文）
 * @param key 秘钥
 * @param ivec 初始向量
 * @return 加密是否成功
 */
bool TripleDESCipher::ede3_ofb64_encrypt(const QByteArray &in, QByteArray &out, const QByteArray &key, const QByteArray &ivec)
{
    // 按8字节对齐，填充明文数据
    QByteArray inTemp = Padding::PKCS7Padding(in, DES_BLOCK_SIZE);
    return ede3_ofb64_encrypt(inTemp, out, key, ivec, DES_ENCRYPT);
}

/**
 * @brief TripleDESCipher::ede3_ofb64_decrypt
 * ofb64模式解密
 * @param in 输入数据（密文）
 * @param out 输出数据（明文）
 * @param key 秘钥
 * @param ivec 初始向量
 * @return 解密是否成功
 */
bool TripleDESCipher::ede3_ofb64_decrypt(const QByteArray &in, QByteArray &out, const QByteArray &key, const QByteArray &ivec)
{
    bool ret = ede3_ofb64_encrypt(in, out, key, ivec, DES_DECRYPT);
    out = Padding::PKCS7UnPadding(out);
    return ret;
}

bool TripleDESCipher::ecb3_encrypt(const QByteArray &in, QByteArray &out, const QByteArray &key, int enc)
{
    // 设置key
    DES_key_schedule sch1, sch2, sch3;
    setKey(key, sch1, sch2, sch3);

    // 调整输出buf大小
    out.resize(in.size());

    // 进行加解密
    for (int i = 0; i < in.size() / DES_BLOCK_SIZE; i++)
    {
        DES_ecb3_encrypt((const_DES_cblock*)(in.constData() + i * DES_BLOCK_SIZE),
                         (DES_cblock *)(out.data() + i * DES_BLOCK_SIZE),
                         &sch1, &sch2, &sch3, enc);
    }
    return true;
}

bool TripleDESCipher::ede3_cbc_encrypt(const QByteArray &in, QByteArray &out, const QByteArray &key, const QByteArray &ivec, int enc)
{
    // 设置key
    DES_key_schedule sch1, sch2, sch3;
    setKey(key, sch1, sch2, sch3);

    // 调整输出buf大小
    out.resize(in.size());

    // 进行加解密
    QByteArray ivecTemp = ivec; // 此参数被自动修改，故使用局部变量传递
    DES_ede3_cbc_encrypt((const unsigned char *)in.constData(),
                         (unsigned char *)out.data(),
                         in.size(), &sch1, &sch2, &sch3,
                         (DES_cblock *)ivecTemp.data(), enc);
    return true;
}

bool TripleDESCipher::ede3_cfb_encrypt(const QByteArray &in, QByteArray &out, const QByteArray &key, const QByteArray &ivec, int enc)
{
    // 设置key
    DES_key_schedule sch1, sch2, sch3;
    setKey(key, sch1, sch2, sch3);

    // 调整输出buf大小
    out.resize(in.size());

    // 进行加解密
    QByteArray ivecTemp = ivec; // 此参数被自动修改，故使用局部变量传递
    DES_ede3_cfb_encrypt((const unsigned char *)in.constData(),
                         (unsigned char *)out.data(),
                         8, in.size(), &sch1, &sch2, &sch3,
                         (DES_cblock *)ivecTemp.data(), enc);
    return true;
}

bool TripleDESCipher::ede3_cfb64_encrypt(const QByteArray &in, QByteArray &out, const QByteArray &key, const QByteArray &ivec, int enc)
{
    // 设置key
    DES_key_schedule sch1, sch2, sch3;
    setKey(key, sch1, sch2, sch3);

    // 调整输出buf大小
    out.resize(in.size());

    // 进行加解密
    int num = 0;
    QByteArray ivecTemp = ivec; // 此参数被自动修改，故使用局部变量传递
    DES_ede3_cfb64_encrypt((const unsigned char *)in.constData(),
                         (unsigned char *)out.data(),
                         in.size(), &sch1, &sch2, &sch3,
                         (DES_cblock *)ivecTemp.data(), &num, enc);
    return true;
}

bool TripleDESCipher::ede3_ofb64_encrypt(const QByteArray &in, QByteArray &out, const QByteArray &key, const QByteArray &ivec, int enc)
{
    Q_UNUSED(enc)

    // 设置key
    DES_key_schedule sch1, sch2, sch3;
    setKey(key, sch1, sch2, sch3);

    // 调整输出buf大小
    out.resize(in.size());

    // 进行加解密
    int num = 0;
    QByteArray ivecTemp = ivec; // 此参数被自动修改，故使用局部变量传递
    DES_ede3_ofb64_encrypt((const unsigned char *)in.constData(),
                         (unsigned char *)out.data(),
                         in.size(), &sch1, &sch2, &sch3,
                         (DES_cblock *)ivecTemp.data(), &num);
    return true;
}
