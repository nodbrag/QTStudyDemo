#ifndef CHILDDIALOG_H
#define CHILDDIALOG_H

#include <QDialog>

namespace Ui {
class ChildDialog;
}

class ChildDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChildDialog(QWidget *parent = nullptr);
    ~ChildDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ChildDialog *ui;
};

#endif // CHILDDIALOG_H
