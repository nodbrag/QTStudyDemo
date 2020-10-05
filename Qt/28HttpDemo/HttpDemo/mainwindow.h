#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QUrl>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void sendGetRequest(const QUrl &url);


    void printRequestData(QNetworkRequest* request);
    void printReplyData(QNetworkReply *reply);

private slots:
    void slot_requestFinished(QNetworkReply *reply);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    QNetworkAccessManager* _networkAccessManager;

    QUrl mUrl;

};

#endif // MAINWINDOW_H
