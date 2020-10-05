#ifndef HEXSPINBOX_H
#define HEXSPINBOX_H

#include <QSpinBox>

class HexSpinbox : public QSpinBox
{
    Q_OBJECT

public:
    HexSpinbox(QWidget *parent = 0);
    ~HexSpinbox();

protected:
    QValidator::State validate(QString& text, int& pos) const;
    int valueFromText(const QString &text) const;
    QString textFromValue(int val) const;

private:
    QRegExpValidator* validator;
};

#endif // HEXSPINBOX_H
