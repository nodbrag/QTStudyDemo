#include <QCoreApplication>
#include <QTimer>
#include <iostream>
/*
struct Msg
{
    int type;       // 消息类型
    char* content;  // 消息内容
};

struct Package // 包结构
{
    const unsigned int head = 0xFFFFFFFF;  // 包头
    int len;       // 消息长度(type+content)
    Msg msg;     // 消息
};

void dealLogin()
{
    // ...
    std::cout << "received login info, do somthing" << std::endl;
}

void dealLogout()
{
    // ...
    std::cout << "received logout info, do somthing" << std::endl;
}

void recv(char* data)
{
    Package* pack = (Package*)data;
    if (pack->msg.type == 1) // login
    {
        dealLogin();
    }
    else if (pack->msg.type == 2) // logout
    {
        dealLogout();
    }
//    else if (...) // 大量if语句
//    {
//       ...
//    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // 定时器模拟接收数据执行流程
    QTimer timer;
    QTimer::connect(&timer, &QTimer::timeout, [=] () {
        static bool reverse = true;
        static char type1Str[] = "login:user=admin,passwd=123";
        static char type2Str[] = "logout:user=admin";

        Package pack;
        if (reverse)
        {
            pack.msg.type = 1;
            pack.msg.content = type1Str;
            pack.len = strlen(pack.msg.content) + sizeof (pack.msg.type);
        }
        else
        {
            pack.msg.type = 2;
            pack.msg.content = type2Str;
            pack.len = strlen(pack.msg.content) + sizeof (pack.msg.type);
        }
        reverse = !reverse;

        recv((char*)(&pack));
    });
    timer.start(1000);

    return a.exec();
}
*/
