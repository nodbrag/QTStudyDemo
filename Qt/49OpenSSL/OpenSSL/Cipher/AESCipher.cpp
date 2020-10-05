#include "AESCipher.h"
#include <openssl/modes.h>

AESCipher::AESCipher()
{

}

/**
 * @brief AESCipher::cbc_encrypt
 * CBC模式加密，填充模式采用PKCS7Padding
 * @param in 输入数据
 * @param out 输出加密结果
 * @param key 密钥，长度必须是16/24/32位，否则加密失败
 * @param ivec 初始向量（一般为16字节全0）
 * @return 加密是否成功
 */
bool AESCipher::cbc_encrypt(const QByteArray &in, QByteArray &out, const QByteArray &key, const QByteArray &ivec)
{
    // 生成加密key
    AES_KEY aes;
    if (!generateEncryptKey(key, aes))
    {
        return false;
    }

    // 进行PKCS7Padding填充
    QByteArray inTemp = PKCS7Padding(in);

    // 调整输出buf大小
    out.resize(inTemp.size());

    // 执行CBC模式加密
    QByteArray ivecTemp = ivec; // ivecTemp会被修改，故需要临时变量来暂存。
    AES_cbc_encrypt((const unsigned char*)inTemp.data(),
                    (unsigned char*)out.data(),
                    inTemp.size(),
                    &aes,
                    (unsigned char*)ivecTemp.data(),
                    AES_ENCRYPT);
    return true;
}

/**
 * @brief AESCipher::cbc_decrypt
 * CBC模式解密，采用PKCS7Padding解除填充
 * @param in 输入数据
 * @param out 输出解密结果
 * @param key 密钥，长度必须是16/24/32位，否则加密失败
 * @param ivec 初始向量（一般为16字节全0）
 * @return 解密是否成功
 */
bool AESCipher::cbc_decrypt(const QByteArray& in, QByteArray& out, const QByteArray &key, const QByteArray &ivec)
{
    // 生成解密key
    AES_KEY aes;
    if (!generateDecryptKey(key, aes))
    {
        return false;
    }

    // 调整输出buf大小
    out.resize(in.size());

    // 执行CBC模式解密
    QByteArray ivecTemp = ivec; // ivecTemp会被修改，故需要临时变量来暂存。
    AES_cbc_encrypt((const unsigned char*)in.data(),
                    (unsigned char*)out.data(),
                    in.size(),
                    &aes,
                    (unsigned char*)ivecTemp.data(),
                    AES_DECRYPT);

    out = PKCS7UnPadding(out);
    return true;
}

/**
 * @brief AESCipher::ecb_encrypt
 * ECB模式加密，填充模式采用PKCS7Padding
 * @param in 输入数据
 * @param out 输出加密结果
 * @param key 密钥，长度必须是16/24/32位，否则加密失败
 * @return 加密是否成功
 */
bool AESCipher::ecb_encrypt(const QByteArray &in, QByteArray &out, const QByteArray &key)
{
    // 生成加密key
    AES_KEY aes;
    if (!generateEncryptKey(key, aes))
    {
        return false;
    }

    // 进行PKCS7Padding填充
    QByteArray inTemp = PKCS7Padding(in);

    // 调整输出buf大小
    out.resize(inTemp.size());

    // 执行加密
    for (int i = 0; i < inTemp.size() / AES_BLOCK_SIZE; i++)
    {
        AES_ecb_encrypt((const unsigned char*)inTemp.data() + AES_BLOCK_SIZE * i,
                        (unsigned char*)out.data() + AES_BLOCK_SIZE * i,
                        &aes,
                        AES_ENCRYPT);
    }
    return true;
}

/**
 * @brief AESCipher::ecb_decrypt
 * ECB模式解密，采用PKCS7Padding解除填充
 * @param in 输入数据
 * @param out 输出解密结果
 * @param key 密钥，长度必须是16/24/32位，否则加密失败
 * @return 解密是否成功
 */
bool AESCipher::ecb_decrypt(const QByteArray &in, QByteArray &out, const QByteArray &key)
{
    // 生成解密key
    AES_KEY aes;
    if (!generateDecryptKey(key, aes))
    {
        return false;
    }

    // 调整输出buf大小
    out.resize(in.size());

    // 执行解密
    for (int i = 0; i < in.size() / AES_BLOCK_SIZE; i++)
    {
        AES_ecb_encrypt((const unsigned char*)in.data() + AES_BLOCK_SIZE * i,
                        (unsigned char*)out.data() + AES_BLOCK_SIZE * i,
                        &aes,
                        AES_DECRYPT);
    }
    out = PKCS7UnPadding(out);
    return true;
}

/**
 * @brief AESCipher::cfb128_encrypt
 * CFB128模式加密
 * @param in 输入数据
 * @param out 输出加密结果
 * @param key 密钥，长度必须是16/24/32位，否则加密失败
 * @param ivec 初始向量（一般为16字节全0）
 * @return 加密是否成功
 */
bool AESCipher::cfb128_encrypt(const QByteArray &in, QByteArray &out, const QByteArray &key, const QByteArray &ivec)
{
    // 生成加密key
    AES_KEY aes;
    if (!generateEncryptKey(key, aes))
    {
        return false;
    }

    // 调整输出buf大小
    out.resize(in.size());

    // 执行cfb模式加密
    int num = 0;
    QByteArray ivecTemp = ivec; // ivecTemp会被修改，故需要临时变量来暂存。
    AES_cfb128_encrypt((const unsigned char*)in.data(),
                    (unsigned char*)out.data(),
                    in.size(),
                    &aes,
                    (unsigned char*)ivecTemp.data(),
                    &num,
                    AES_ENCRYPT);
    return true;
}

/**
 * @brief AESCipher::cfb128_decrypt
 * CFB128模式解密
 * @param in 输入数据
 * @param out 输出解密结果
 * @param key 密钥，长度必须是16/24/32位，否则加密失败
 * @param ivec 初始向量（一般为16字节全0）
 * @return 解密是否成功
 */
bool AESCipher::cfb128_decrypt(const QByteArray &in, QByteArray &out, const QByteArray &key, const QByteArray &ivec)
{
    // 生成加密key
    AES_KEY aes;
    if (!generateEncryptKey(key, aes))
    {
        return false;
    }

    // 调整输出buf大小
    out.resize(in.size());

    // 执行cfb模式解密
    int num = 0;
    QByteArray ivecTemp = ivec; // ivecTemp会被修改，故需要临时变量来暂存。
    AES_cfb128_encrypt((const unsigned char*)in.data(),
                    (unsigned char*)out.data(),
                    in.size(),
                    &aes,
                    (unsigned char*)ivecTemp.data(),
                    &num,
                    AES_DECRYPT);
    return true;
}

/**
 * @brief AESCipher::cfb8_encrypt
 * CFB8模式加密
 * @param in 输入数据
 * @param out 输出加密结果
 * @param key 密钥，长度必须是16/24/32位，否则加密失败
 * @param ivec 初始向量（一般为16字节全0）
 * @return 加密是否成功
 */
bool AESCipher::cfb8_encrypt(const QByteArray &in, QByteArray &out, const QByteArray &key, const QByteArray &ivec)
{
    // 生成加密key
    AES_KEY aes;
    if (!generateEncryptKey(key, aes))
    {
        return false;
    }

    // 调整输出buf大小
    out.resize(in.size());

    // 执行cfb模式加密
    int num = 0;
    QByteArray ivecTemp = ivec; // ivecTemp会被修改，故需要临时变量来暂存。
    AES_cfb8_encrypt((const unsigned char*)in.data(),
                    (unsigned char*)out.data(),
                    in.size(),
                    &aes,
                    (unsigned char*)ivecTemp.data(),
                    &num,
                    AES_ENCRYPT);
    return true;
}

/**
 * @brief AESCipher::cfb8_decrypt
 * CFB8模式解密
 * @param in 输入数据
 * @param out 输出解密结果
 * @param key 密钥，长度必须是16/24/32位，否则加密失败
 * @param ivec 初始向量（一般为16字节全0）
 * @return 解密是否成功
 */
bool AESCipher::cfb8_decrypt(const QByteArray &in, QByteArray &out, const QByteArray &key, const QByteArray &ivec)
{
    // 生成加密key
    AES_KEY aes;
    if (!generateEncryptKey(key, aes))
    {
        return false;
    }

    // 调整输出buf大小
    out.resize(in.size());

    // 执行cfb模式解密
    int num = 0;
    QByteArray ivecTemp = ivec; // ivecTemp会被修改，故需要临时变量来暂存。
    AES_cfb8_encrypt((const unsigned char*)in.data(),
                    (unsigned char*)out.data(),
                    in.size(),
                    &aes,
                    (unsigned char*)ivecTemp.data(),
                    &num,
                    AES_DECRYPT);
    return true;
}

/**
 * @brief AESCipher::cfb1_encrypt
 * CFB1模式加密
 * @param in 输入数据
 * @param out 输出加密结果
 * @param key 密钥，长度必须是16/24/32位，否则加密失败
 * @param ivec 初始向量（一般为16字节全0）
 * @return 加密是否成功
 */
bool AESCipher::cfb1_encrypt(const QByteArray &in, QByteArray &out, const QByteArray &key, const QByteArray &ivec)
{
    // 生成加密key
    AES_KEY aes;
    if (!generateEncryptKey(key, aes))
    {
        return false;
    }

    // 调整输出buf大小
    out.resize(in.size());

    // 执行cfb模式加密
    int num = 0;
    QByteArray ivecTemp = ivec; // ivecTemp会被修改，故需要临时变量来暂存。
    AES_cfb1_encrypt((const unsigned char*)in.data(),
                    (unsigned char*)out.data(),
                    in.size() * 8,
                    &aes,
                    (unsigned char*)ivecTemp.data(),
                    &num,
                    AES_ENCRYPT);
    return true;
}

/**
 * @brief AESCipher::cfb1_decrypt
 * CFB1模式解密
 * @param in 输入数据
 * @param out 输出解密结果
 * @param key 密钥，长度必须是16/24/32位，否则加密失败
 * @param ivec 初始向量（一般为16字节全0）
 * @return 解密是否成功
 */
bool AESCipher::cfb1_decrypt(const QByteArray &in, QByteArray &out, const QByteArray &key, const QByteArray &ivec)
{
    // 生成加密key
    AES_KEY aes;
    if (!generateEncryptKey(key, aes))
    {
        return false;
    }

    // 调整输出buf大小
    out.resize(in.size());

    // 执行cfb模式解密
    int num = 0;
    QByteArray ivecTemp = ivec; // ivecTemp会被修改，故需要临时变量来暂存。
    AES_cfb1_encrypt((const unsigned char*)in.data(),
                    (unsigned char*)out.data(),
                    in.size() * 8,
                    &aes,
                    (unsigned char*)ivecTemp.data(),
                    &num,
                    AES_DECRYPT);
    return true;
}

/**
 * @brief AESCipher::keyIsLegal
 * 检查key是否合法
 * @param key 密钥
 * @return 是否合法
 */
bool AESCipher::keyIsLegal(const QByteArray &key)
{
    // 判断密码的长度合法性(只能是16、24、32字节)
    int bits = key.size() * 8;
    return (bits == 128 || bits == 192 || bits == 256);
}

/**
 * @brief AESCipher::generateEncryptKey
 * 生成加密密钥
 * @param key 密钥数据
 * @param aes_key 生成的密钥
 * @return 是否成功
 */
bool AESCipher::generateEncryptKey(const QByteArray &key, AES_KEY &aes_key)
{
    // 检查密钥合法性
    if (!keyIsLegal(key))
    {
        return false;
    }

    // 生成加密key
    int ret = AES_set_encrypt_key((const unsigned char*)key.data(),
                                   key.size() * 8,
                                   &aes_key);
    return (ret == 0);
}

/**
 * @brief AESCipher::generateDecryptKey
 * 生成解密密钥
 * @param key 密钥数据
 * @param aes_key 生成的密钥
 * @return 是否成功
 */
bool AESCipher::generateDecryptKey(const QByteArray &key, AES_KEY &aes_key)
{
    // 检查密钥合法性
    if (!keyIsLegal(key))
    {
        return false;
    }

    // 生成解密key
    int ret = AES_set_decrypt_key((const unsigned char*)key.data(),
                                    key.size() * 8,
                                    &aes_key);
    return (ret == 0);
}

/**
 * @brief AESCipher::getPKCS7PaddedLength
 * 根据原始数据长度，计算进行PKCS7填充后的数据长度
 * @param dataLen 原始数据长度
 * @return 返回填充后的数据长度
 */
int AESCipher::getPKCS7PaddedLength(int dataLen)
{
    // 计算填充的字节数（按16字节对齐进行填充）
    int remainder = dataLen % AES_BLOCK_SIZE;
    int paddingSize = (remainder == 0) ? AES_BLOCK_SIZE : (AES_BLOCK_SIZE - remainder);
    return (dataLen + paddingSize);
}

/**
 * @brief AESCipher::PKCS7Padding
 * 采用PKCS7Padding方式，将in数据进行16字节对齐填充。
 * 此函数用于加密前，对明文进行填充。
 * @param in 源数据
 * @return 返回填充后的数据
 */
QByteArray AESCipher::PKCS7Padding(const QByteArray &in)
{
    // 计算需要填充字节数（按16字节对齐进行填充）
    int remainder = in.size() % AES_BLOCK_SIZE;
    int paddingSize = (remainder == 0) ? AES_BLOCK_SIZE : (AES_BLOCK_SIZE - remainder);

    // 进行填充
    QByteArray temp(in);
    temp.append(paddingSize, paddingSize);
    return temp;
}

/**
 * @brief AESCipher::PKCS7UnPadding
 * 采用PKCS7Padding方式，将in数据按16字节对齐，去除填充。
 * 此函数用于解密后，对解密结果进一步去除填充，以得到原始数据。
 * @param in 源数据
 * @return 返回去除填充后的数据
 */
QByteArray AESCipher::PKCS7UnPadding(const QByteArray &in)
{
    char paddingSize = in.at(in.size() - 1);
    return in.left(in.size() - paddingSize);
}
