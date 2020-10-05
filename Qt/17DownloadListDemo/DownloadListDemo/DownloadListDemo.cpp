#include "DownloadListDemo.h"
#include "ui_DownloadListDemo.h"
#include "DownloadListConfig.h"
#include <QDir>

DownloadListDemo::DownloadListDemo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DownloadListDemo)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(3);
    QString str = tr("文件名称,下载进度,下载状态");
    QStringList header = str.simplified().split(",");
    ui->tableWidget->setHorizontalHeaderLabels(header);

    QString xmlFile = QApplication::applicationDirPath();
    xmlFile += "/downListconfig.xml";
    xmlConfig = new DownloadListConfig(xmlFile.toStdString().c_str());

    loadList();

//    xmlConfigTest();
}

DownloadListDemo::~DownloadListDemo()
{
    if (xmlConfig != NULL)
    {
        delete xmlConfig;
        xmlConfig = NULL;
    }
    delete ui;
}

void DownloadListDemo::addRow(const QString& fileName, int progress, bool succeed)
{
    int row = ui->tableWidget->rowCount();
    ui->tableWidget->setRowCount(row + 1);

    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(fileName));
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(progress) + "%"));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(succeed?"下载完毕":"下载失败"));
}

void DownloadListDemo::loadList()
{
    std::list<FileInfo> infoList;
    xmlConfig->getAllInfo(&infoList);

    for (std::list<FileInfo>::iterator it = infoList.begin(); it != infoList.end(); it++)
    {
        addRow(it->name.c_str(), it->progress, it->succeed);
    }

//    addRow("文件1", 100, true);
//    addRow("文件2", 100, false);
//    addRow("文件3", 100, true);
//    addRow("文件4", 100, true);
//    addRow("文件5", 100, true);
//    addRow("文件6", 100, true);
//    addRow("文件7", 100, true);
//    addRow("文件8", 100, true);
}

void DownloadListDemo::xmlConfigTest()
{
    FileInfo info;
    info.name = "文件4";
    info.path = "D:/xmlFile.xml";
    info.progress = 50;
    info.succeed = false;

//    xmlConfig->addInfo(info);
//    xmlConfig->addInfo(info);
//    xmlConfig->addInfo(info);
//    xmlConfig->addInfo(info);
//    xmlConfig->addInfo(info);
//    xmlConfig->addInfo(info);

    xmlConfig->deleteInfo("文件3");

    xmlConfig->modifyInfo(info);

    FileInfo getInfo;
    xmlConfig->getInfo(info.name.c_str(), &getInfo);

    int count = xmlConfig->getCount();

    xmlConfig->saveFile();
}
