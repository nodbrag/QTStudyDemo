#include "LoginHandler.h"
#include <QNetworkCookieJar>
#include <QNetworkCookie>

LoginHandler::LoginHandler(QNetworkAccessManager *manager)
    :BaseHandler(manager)
{

}

LoginHandler::~LoginHandler()
{

}

void LoginHandler::runHandle()
{
    // "https://ssl.ptlogin2.qq.com/ptqrlogin?u1=http%3A%2F%2Fw.qq.com%2Fproxy.html&ptqrtoken=903846213&ptredirect=0&h=1&t=1&g=1&from_ui=1&ptlang=2052&action=1-0-1516111834067&js_ver=10233&js_type=1&login_sig=Khk*pa814SqKMOSgKkq1A5o7HYEdsd4Wxxp4EsjyAa3AmiRZf*HTclmO3Kzk2k7k&pt_uistyle=40&aid=501004106&daid=164&mibao_css=m_webqq&"
    QString url = "https://ssl.ptlogin2.qq.com/ptqrlogin?u1=http%3A%2F%2Fw.qq.com%2Fproxy.html&ptqrtoken=";
    url += "903846213";       // 变化
    url += "&ptredirect=0&h=1&t=1&g=1&from_ui=1&ptlang=2052&action=";
    url += "1-0-1516111834067";  // 变化
    url += "&js_ver=10233&js_type=1&login_sig=";
    url += "Khk*pa814SqKMOSgKkq1A5o7HYEdsd4Wxxp4EsjyAa3AmiRZf*HTclmO3Kzk2k7k";   // 变化
    url += "&pt_uistyle=40&aid=501004106&daid=164&mibao_css=m_webqq&";
    get(url);
    return;



    // 获得cookie中qrsig的值
    QString qrsig;
    QList<QNetworkCookie> cookies = ((QNetworkAccessManager*)parent())->cookieJar()->cookiesForUrl(QUrl("https://ssl.ptlogin2.qq.com/ptqrshow?appid=501004106&e=2&l=M&s=3&d=72&v=4&t=0.2966802910064531&daid=164&pt_3rd_aid=0"));
    for (int i = 0; i < cookies.size(); i++)
    {
        if (cookies.at(i).name() == "qrsig")
        {
            qrsig = cookies.at(i).value();
            break;
        }
    }

    QString setCookieStr;
    setCookieStr = QString("pgv_pvi=3103341568; pgv_si=s2790406144; qrsig=%1").arg(qrsig);

    // "pgv_pvi=3103341568; pgv_si=s2790406144; qrsig=2Xozbb6caOcs7ZBAfWXSUbyUa-z5IeV1yYfV3eh-trN25j2eZxHn9BF9HXCDEIX9"
    QByteArray strTemp;
    setCookie(strTemp.append(setCookieStr));
    get(url);
}

void LoginHandler::requestFinished(QNetworkReply *reply, const QByteArray &data, int statusCode)
{
    if (statusCode == 200)
    {
        qDebug() << data;
    }
}

