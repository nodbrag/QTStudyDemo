#include "HexSpinbox.h"

HexSpinbox::HexSpinbox(QWidget *parent)
    : QSpinBox(parent)
{
    setRange(0, 0xff);
    validator = new QRegExpValidator(QRegExp("[0-9A-Fa-f]{1,8}"), this);
}

HexSpinbox::~HexSpinbox()
{

}

QValidator::State HexSpinbox::validate(QString& text, int& pos) const
{
    return validator->validate(text, pos);
}

int HexSpinbox::valueFromText(const QString &text) const
{
    bool ok;
    return text.toInt(&ok, 16);
}

QString HexSpinbox::textFromValue(int val) const
{
    return QString::number(val, 16).toUpper();
}
