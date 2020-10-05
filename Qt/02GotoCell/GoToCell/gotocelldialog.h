#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QDialog>

namespace Ui {
class GoToCellDialog;
}

class GoToCellDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GoToCellDialog(QWidget *parent = 0);
    ~GoToCellDialog();

private slots:
	void on_lineEdit_textChanged();

private:
    Ui::GoToCellDialog *ui;
};

#endif // GOTOCELLDIALOG_H
