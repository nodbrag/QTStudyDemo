#include "HASHCipher.h"
#include <openssl/evp.h>

/**
 * @brief HASHCipher::HASHCipher
 * @param mode HASH算法类型
 */
HASHCipher::HASHCipher(Mode mode)
    :_mode(mode)
{
}

/**
 * @brief HASHCipher::addData
 * 添加待加密数据
 * @param data 数据
 */
void HASHCipher::addData(const QByteArray &data)
{
    _data = data;
}

/**
 * @brief HASHCipher::result
 * 获取加密结果
 * @return 加密结果
 */
QByteArray HASHCipher::result()
{
    OpenSSL_add_all_digests();

    const EVP_MD *md = nullptr;
    md = EVP_get_digestbyname(modeToString(_mode).toStdString().c_str());
    if(!md) // 不支持的格式
    {
        return QByteArray();
    }

    unsigned char mdValue[EVP_MAX_MD_SIZE] = {0};
    unsigned int mdLen = 0;

    EVP_MD_CTX mdctx;
    EVP_MD_CTX_init(&mdctx);
    EVP_DigestInit_ex(&mdctx, md, nullptr);
    EVP_DigestUpdate(&mdctx, _data.data(), _data.size());
    EVP_DigestFinal_ex(&mdctx, mdValue, &mdLen);
    EVP_MD_CTX_cleanup(&mdctx);

    QByteArray out((const char *)mdValue, mdLen);
    return out;
}

/**
 * @brief HASHCipher::modeToString
 * Mode型枚举值转字符串
 * @param value 枚举值
 * @return 字符串
 */
QString HASHCipher::modeToString(HASHCipher::Mode value)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<Mode>();
    const char* key = metaEnum.valueToKey(value);
    Q_ASSERT(key != nullptr);
    return QString(key);
}
