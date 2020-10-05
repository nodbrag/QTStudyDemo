#include "sortdialog.h"

SortDialog::SortDialog(QWidget *parent)
	: QDialog(parent)
{
	setupUi(this);

	SecondaryGroupBox->hide();
	TertiaryGroupBox->hide();

	// 根据控件布局自动调整大小
	layout()->setSizeConstraint(QLayout::SetFixedSize);

	setColumnRange('A', 'Z');
}

SortDialog::~SortDialog()
{

}

void SortDialog::setColumnRange(QChar first, QChar last)
{
	primaryColumnCombo->clear();
	secondarColumnCombo->clear();
	tertiaryColumnCombo->clear();

	secondarColumnCombo->addItem(tr("None"));
	tertiaryColumnCombo->addItem(tr("None"));
	primaryColumnCombo->setMinimumSize(secondarColumnCombo->sizeHint());

	QChar ch = first;
	while (ch < last)
	{
		primaryColumnCombo->addItem(QString(ch));
		secondarColumnCombo->addItem(QString(ch));
		tertiaryColumnCombo->addItem(QString(ch));
		ch = ch.unicode() + 1;
	}
}