#ifndef PADDING_H
#define PADDING_H

#include <QByteArray>

/**
 * @brief The Padding class
 * 算法数据填充模式，提供对数据进行PKCS7填充和去除填充的相关函数。
 */
class Padding
{
public:
    static int getPKCS7PaddedLength(int dataLen, int alignSize);
    static QByteArray PKCS7Padding(const QByteArray &in, int alignSize);
    static QByteArray PKCS7UnPadding(const QByteArray &in);
};

#endif // PADDING_H
