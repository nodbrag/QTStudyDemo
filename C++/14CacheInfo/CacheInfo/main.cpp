#include <QCoreApplication>
#include <QDebug>
#include "Processor.h"

void printLevelInfo(CacheLevelInfo levelInfo)
{
    qDebug() << "--------------------------------";
    qDebug() << "Level:" << levelInfo.getLevel();
    qDebug() << "Type:" << levelInfo.getType();
    qDebug() << "CacheSize:" << levelInfo.getSize();
    qDebug() << "CacheLineSize:" << levelInfo.getLineSize();
    qDebug() << "Ways:" << levelInfo.getWaysOfAssociativity();
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Processor processor;
    CacheInfo info = processor.getCacheInfo();
    CacheLevelInfo l1IInfo = info.getCacheInformation(L1, INSTRUCTION_CACHE);
    CacheLevelInfo l1DInfo = info.getCacheInformation(L1, DATA_CACHE);
    CacheLevelInfo l2Info = info.getCacheInformation(L2, DATA_CACHE);
    CacheLevelInfo l3Info = info.getCacheInformation(L3, DATA_CACHE);

    printLevelInfo(l1IInfo);
    printLevelInfo(l1DInfo);
    printLevelInfo(l2Info);
    printLevelInfo(l3Info);

    return a.exec();
}

