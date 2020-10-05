#ifndef TESTFORM_H
#define TESTFORM_H

#include <QWidget>
#include "FramelessWindow.h"

namespace Ui {
class TestForm;
}

class TestForm : public FramelessWindow
{
    Q_OBJECT

public:
    explicit TestForm(QWidget *parent = 0);
    ~TestForm();

private:
    Ui::TestForm *ui;
};

#endif // TESTFORM_H
