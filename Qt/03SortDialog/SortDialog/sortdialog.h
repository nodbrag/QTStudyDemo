#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <QtWidgets/QDialog>
#include "ui_sortdialog.h"

class SortDialog : public QDialog
{
	Q_OBJECT

public:
	SortDialog(QWidget *parent = 0);
	~SortDialog();

private:
	void setColumnRange(QChar first, QChar last);

private:
	Ui::SortDialogClass ui;
};

#endif // SORTDIALOG_H
