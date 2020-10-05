#include "sortdialog.h"

SortDialog::SortDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	ui.SecondaryGroupBox->hide();
	ui.TertiaryGroupBox->hide();

	// 根据控件布局自动调整大小
	layout()->setSizeConstraint(QLayout::SetFixedSize);

	setColumnRange('A', 'Z');
}

SortDialog::~SortDialog()
{

}

void SortDialog::setColumnRange(QChar first, QChar last)
{
	ui.primaryColumnCombo->clear();
	ui.secondarColumnCombo->clear();
	ui.tertiaryColumnCombo->clear();

	ui.secondarColumnCombo->addItem(tr("None"));
	ui.tertiaryColumnCombo->addItem(tr("None"));
	ui.primaryColumnCombo->setMinimumSize(ui.secondarColumnCombo->sizeHint());

	QChar ch = first;
	while (ch < last)
	{
		ui.primaryColumnCombo->addItem(QString(ch));
		ui.secondarColumnCombo->addItem(QString(ch));
		ui.tertiaryColumnCombo->addItem(QString(ch));
		ch = ch.unicode() + 1;
	}
}