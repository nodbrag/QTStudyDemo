#include "Padding.h"

/**
 * @brief Padding::getPKCS7PaddedLength
 * 根据原始数据长度，计算进行PKCS7填充后的数据长度
 * @param dataLen 原始数据长度
 * @return 返回填充后的数据长度
 */
int Padding::getPKCS7PaddedLength(int dataLen, int alignSize)
{
    // 计算填充的字节数（按alignSize字节对齐进行填充）
    int remainder = dataLen % alignSize;
    int paddingSize = (remainder == 0) ? alignSize : (alignSize - remainder);
    return (dataLen + paddingSize);
}

/**
 * @brief Padding::PKCS7Padding
 * 采用PKCS7Padding方式，将in数据进行alignSize字节对齐填充。
 * 此函数用于加密前，对明文进行填充。
 * @param in 源数据
 * @param alignSize 对齐字节数
 * @return 返回填充后的数据
 */
QByteArray Padding::PKCS7Padding(const QByteArray &in, int alignSize)
{
    // 计算需要填充字节数（按alignSize字节对齐进行填充）
    int remainder = in.size() % alignSize;
    int paddingSize = (remainder == 0) ? alignSize : (alignSize - remainder);

    // 进行填充
    QByteArray temp(in);
    temp.append(paddingSize, paddingSize);
    return temp;
}

/**
 * @brief Padding::PKCS7UnPadding
 * 采用PKCS7Padding方式，将in数据按16字节对齐，去除填充。
 * 此函数用于解密后，对解密结果进一步去除填充，以得到原始数据。
 * @param in 源数据
 * @return 返回去除填充后的数据
 */
QByteArray Padding::PKCS7UnPadding(const QByteArray &in)
{
    char paddingSize = in.at(in.size() - 1);
    return in.left(in.size() - paddingSize);
}
