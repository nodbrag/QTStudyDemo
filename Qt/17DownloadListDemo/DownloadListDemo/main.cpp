/*
 * 说明：使用tinyxml封装下载列表配置类DownloadListConfig.h；
 * 将xml记录的文件数据载入tabwidget下载列表中；
*/

#include "DownloadListDemo.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DownloadListDemo w;
    w.show();

    return a.exec();
}
