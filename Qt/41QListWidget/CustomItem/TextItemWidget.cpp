#include "TextItemWidget.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

const QString BTN_QSS = "QPushButton{"
                            "border-image: url(:/res/close_normal.png);"
                        "}"
                        "QPushButton::hover{"
                           "border-image: url(:/res/close_hover.png);"
                        "}"
                        "QPushButton::pressed{"
                            "border-image: url(:/res/close_hover.png);"
                        "}";

TextItemWidget::TextItemWidget(QWidget *parent)
    : QWidget(parent)
{
    label = new QLabel();
    btn = new QPushButton(this);
    btn->setFixedSize(48, 48);
    btn->setStyleSheet(BTN_QSS);

    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(btn);

    connect(btn, &QPushButton::clicked, this, &TextItemWidget::deleteBtnClicked);
}

QString TextItemWidget::getText() const
{
    return label->text();
}

void TextItemWidget::setText(const QString &value)
{
    label->setText(value);
}
