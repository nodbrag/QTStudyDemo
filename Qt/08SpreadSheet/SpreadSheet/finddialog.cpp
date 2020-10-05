#include "finddialog.h"
#include <QtWidgets>

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    // 创建控件
    label = new QLabel(tr("Find &what:"));
    lineEdit = new QLineEdit();
    label->setBuddy(lineEdit);

    caseCheckBox = new QCheckBox(tr("Match &case"));
    backwardCheckBox = new QCheckBox(tr("Search &backward"));

    findButton = new QPushButton(tr("&Find"));
    findButton->setDefault(true);
    findButton->setEnabled(false);

    closeButton = new QPushButton(tr("Close"));

    // 定义信号与消息响应
    connect(lineEdit, SIGNAL(textChanged(const QString&)),
            this, SLOT(onEnableFindButton(const QString&)));
    connect(findButton, SIGNAL(clicked()),
            this, SLOT(onFindClicked()));
    connect(closeButton, SIGNAL(clicked()),
            this, SLOT(close()));

    // 定义界面布局
    QHBoxLayout* topLeftLayout = new QHBoxLayout();
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);

    QVBoxLayout* leftLayout = new QVBoxLayout();
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(caseCheckBox);
    leftLayout->addWidget(backwardCheckBox);

    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch();

    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("Find"));
    setFixedHeight(sizeHint().height());
}

FindDialog::~FindDialog()
{

}

void FindDialog::onEnableFindButton(const QString& text)
{
    findButton->setEnabled(!text.isEmpty());
}

void FindDialog::onFindClicked()
{
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs = caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;
    if (backwardCheckBox->isChecked())
    {
        emit findPrevious(text, cs);
    }
    else
    {
        emit findNext(text, cs);
    }
}
