#include <QCoreApplication>
#include <QDebug>
#include "AESCipher.h"
#include "TripleDESCipher.h"
#include "RSACipher.h"
#include "HASHCipher.h"

void testAES()
{
    QByteArray plainText = "life's a struggle";
    QByteArray cipherText;
    QByteArray decipherText;

    QByteArray key = QByteArray::fromHex("8cc72b05705d5c46f412af8cbed55aad");
    QByteArray ivec = QByteArray::fromHex("667b02a85c61c786def4521b060265e8");

    // AES cbc模式加密验证
    AESCipher aescipher;
    aescipher.cbc_encrypt(plainText, cipherText,
                          key, ivec);
    aescipher.cbc_decrypt(cipherText, decipherText,
                          key, ivec);
    qDebug() << "AES cbc is"
             << ((decipherText == plainText) ? "succeeded" : "failed");
    cipherText.clear();
    decipherText.clear();

    // AES ecb模式加密验证
    aescipher.ecb_encrypt(plainText, cipherText,
                          key);
    aescipher.ecb_decrypt(cipherText, decipherText,
                          key);
    qDebug() << "AES ecb is"
             << ((decipherText == plainText) ? "succeeded" : "failed");
    cipherText.clear();
    decipherText.clear();

    // AES ofb128模式加密验证
//    aescipher.ofb128_encrypt(plainText, cipherText,
//                             key, ivec);
//    aescipher.ofb128_decrypt(cipherText, decipherText,
//                             key, ivec);
//    qDebug() << "AES ofb128 is"
//             << ((decipherText == plainText) ? "succeeded" : "failed");
//    cipherText.clear();
//    decipherText.clear();

    // AES cfb128模式加密验证
    aescipher.cfb128_encrypt(plainText, cipherText,
                          key, ivec);
    aescipher.cfb128_decrypt(cipherText, decipherText,
                          key, ivec);
    qDebug() << "AES cfb128 is"
             << ((decipherText == plainText) ? "succeeded" : "failed");
    cipherText.clear();
    decipherText.clear();

    // AES cfb8模式加密验证
    aescipher.cfb8_encrypt(plainText, cipherText,
                          key, ivec);
    aescipher.cfb8_decrypt(cipherText, decipherText,
                          key, ivec);
    qDebug() << "AES cfb8 is"
             << ((decipherText == plainText) ? "succeeded" : "failed");
    cipherText.clear();
    decipherText.clear();

    // AES cfb1模式加密验证
    aescipher.cfb1_encrypt(plainText, cipherText,
                          key, ivec);
    aescipher.cfb1_decrypt(cipherText, decipherText,
                          key, ivec);
    qDebug() << "AES cfb1 is"
             << ((decipherText == plainText) ? "succeeded" : "failed");
    cipherText.clear();
    decipherText.clear();

    // AES ctr128模式加密验证
//    aescipher.ctr128_encrypt(plainText, cipherText,
//                          key, ivec);
//    aescipher.ctr128_decrypt(cipherText, decipherText,
//                          key, ivec);
//    qDebug() << "AES ctr128 is"
//             << ((decipherText.contains(plainText)) ? "succeeded" : "failed");
//    cipherText.clear();
//    decipherText.clear();
}

void testTripleDES()
{
    QByteArray plainText = "life's a struggle";
    QByteArray cipherText;
    QByteArray decipherText;

    QByteArray key = QByteArray::fromHex("8cc72b05705d5c46f412af8cbed55aad8cc72b05705d5c46");
    QByteArray ivec = QByteArray::fromHex("667b02a85c61c786");

    // TripleDES ecb模式加密验证
    TripleDESCipher tripleDESCipher;
    tripleDESCipher.ecb3_encrypt(plainText, cipherText, key);
    tripleDESCipher.ecb3_decrypt(cipherText, decipherText, key);
    qDebug() << "TripleDES ecb is"
             << ((decipherText == plainText) ? "succeeded" : "failed");
    cipherText.clear();
    decipherText.clear();

    // TripleDES cbc模式加密验证
    tripleDESCipher.ede3_cbc_encrypt(plainText, cipherText, key, ivec);
    tripleDESCipher.ede3_cbc_decrypt(cipherText, decipherText, key, ivec);
    qDebug() << "TripleDES cbc is"
             << ((decipherText == plainText) ? "succeeded" : "failed");
    cipherText.clear();
    decipherText.clear();

    // TripleDES cfb1模式加密验证
    tripleDESCipher.ede3_cfb_encrypt(plainText, cipherText, key, ivec);
    tripleDESCipher.ede3_cfb_decrypt(cipherText, decipherText, key, ivec);
    qDebug() << "TripleDES cfb1 is"
             << ((decipherText == plainText) ? "succeeded" : "failed");
    cipherText.clear();
    decipherText.clear();

    // TripleDES cfb64模式加密验证
    tripleDESCipher.ede3_cfb64_encrypt(plainText, cipherText, key, ivec);
    tripleDESCipher.ede3_cfb64_decrypt(cipherText, decipherText, key, ivec);
    qDebug() << "TripleDES cfb64 is"
             << ((decipherText == plainText) ? "succeeded" : "failed");
    cipherText.clear();
    decipherText.clear();

    // TripleDES ofb64模式加密验证
    tripleDESCipher.ede3_ofb64_encrypt(plainText, cipherText, key, ivec);
    tripleDESCipher.ede3_ofb64_decrypt(cipherText, decipherText, key, ivec);
    qDebug() << "TripleDES ofb64 is"
             << ((decipherText == plainText) ? "succeeded" : "failed");
    cipherText.clear();
    decipherText.clear();
}

void testRSA()
{
    // RSA密钥对生成验证
    RSACipher cipher;
    cipher.generateKeyPair("./prikey.pem", "./pubkey.pem", 1024);

    // RSA加解密验证
    QByteArray plainText = "life's a struggle";
    QByteArray cipherText;
    QByteArray decipherText;
    RSA * rsa = cipher.generateKeyPair(1024);
    cipher.public_encrypt(plainText, cipherText, rsa);
    cipher.private_decrypt(cipherText, decipherText, rsa);
    cipher.freeRSA(rsa);
    qDebug() << "RSA encrypt is"
             << ((decipherText == plainText) ? "succeeded" : "failed");
    cipherText.clear();
    decipherText.clear();

    // RSA签名、验签
    QByteArray msg = "life's a struggle";
    HASHCipher cipher6(HASHCipher::MD5); // 生成文件md5摘要
    cipher6.addData(msg);
    QByteArray md5 = cipher6.result();

    QByteArray signMsg;
    rsa = cipher.generateKeyPair(1024);
    cipher.sign(md5, signMsg, rsa);  // 签名
    bool ret = cipher.verify(md5, signMsg, rsa); // 验签
    cipher.freeRSA(rsa);
    qDebug() << "RSA sign is"
             << (ret ? "succeeded" : "failed");
}

void print(const QString title, const QByteArray& array)
{
    qDebug() << title << ":";
    for(int i = 0; i < array.size(); i++)
    {
        printf("%02X", (unsigned char)array[i]);
    }
    printf("\n");
}

void testHash()
{
    // Sha1
    HASHCipher cipher1(HASHCipher::SHA1);
    cipher1.addData("testOpenssl");
    print("SHA1", cipher1.result());

    // Sha224
    HASHCipher cipher2(HASHCipher::SHA224);
    cipher2.addData("testOpenssl");
    print("SHA224", cipher2.result());

    // Sha256
    HASHCipher cipher3(HASHCipher::SHA256);
    cipher3.addData("testOpenssl");
    print("SHA256", cipher3.result());

    // Sha384
    HASHCipher cipher4(HASHCipher::SHA384);
    cipher4.addData("testOpenssl");
    print("SHA384", cipher4.result());

    // Sha512
    HASHCipher cipher5(HASHCipher::SHA512);
    cipher5.addData("testOpenssl");
    print("SHA512", cipher5.result());

    // Ripemd160
    HASHCipher cipher6(HASHCipher::RIPEMD160);
    cipher6.addData("testOpenssl");
    print("RIPEMD160", cipher6.result());

    // Md5
    HASHCipher cipher7(HASHCipher::MD5);
    cipher7.addData("testOpenssl");
    print("MD5", cipher7.result());
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    testAES();

    testTripleDES();

    testRSA();

    testHash();

    return a.exec();
}
