#ifndef DOWNLOADLISTDEMO_H
#define DOWNLOADLISTDEMO_H

#include <QDialog>

class DownloadListConfig;

namespace Ui {
class DownloadListDemo;
}

class DownloadListDemo : public QDialog
{
    Q_OBJECT

public:
    explicit DownloadListDemo(QWidget *parent = 0);
    ~DownloadListDemo();

private:
    void addRow(const QString& fileName, int progress, bool succeed);
    void loadList();

    void xmlConfigTest();

private:
    Ui::DownloadListDemo *ui;
    DownloadListConfig* xmlConfig;
};

#endif // DOWNLOADLISTDEMO_H
