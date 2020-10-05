#include <QCoreApplication>
#include <QFile>
#include <QDebug>
#include <QDir>

void testWriteFile(const QString& fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly))
    {
        file.write("123");
    }
    else
    {
        qDebug() << fileName << ":file open failed!";
    }
}

void testMakeDir(const QString& path)
{
    QDir dir;
    if (!dir.mkpath(path))
    {
        qDebug() << path << ":mkdir failed!";
    }
}

/* 在带中文和空格路径下，进行路径相关测试 */
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 1.路径分割符使用\\，测试新建文件
    testWriteFile("D:\\测试\\test 123 900\\test1.txt");

    // 2.路径分割符使用\\，测试创建目录
    testMakeDir("D:\\测试\\test 123 900\\testdir1");

    // 3.路径分割符使用\\，测试创建路径
    testMakeDir("D:\\测试\\test 123 900\\path 1\\目录 1_1");

    // 4.路径分割符使用/，测试新建文件
    testWriteFile("D:/测试/test 123 900/test2.txt");

    // 5.路径分割符使用/，测试创建目录
    testMakeDir("D:/测试/test 123 900/testdir2");

    // 6.路径分割符使用/，测试创建路径
    testMakeDir("D:/测试/test 123 900/path 2/目录 2_2");

    //testWriteFile("D:\测试\test 123 900\test1.txt"); // is error
    //testMakeDir("D:\测试\test 123 900\testdir2"); // is error

    return a.exec();
}
