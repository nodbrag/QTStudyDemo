#ifndef SORTDIALOG_H
#define SORTDIALOG_H

#include <QtWidgets/QDialog>
#include "ui_sortdialog.h"

class SortDialog : public QDialog, public Ui::SortDialogClass
{
	Q_OBJECT

public:
	SortDialog(QWidget *parent = 0);
	~SortDialog();

	void setColumnRange(QChar first, QChar last);
};

#endif // SORTDIALOG_H
