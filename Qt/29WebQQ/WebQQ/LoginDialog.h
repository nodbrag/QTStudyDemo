#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QTimer>
#include "mainwindow.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private slots:
    void slot_getQRCodeImageSucceed(const QImage& img);

    void slot_detectLoginStatus();

private:
    Ui::LoginDialog *ui;
    MainWindow* mainwindow;

    QNetworkAccessManager* _networkAccessManager;

    QTimer _timer;
};

#endif // LOGINDIALOG_H
