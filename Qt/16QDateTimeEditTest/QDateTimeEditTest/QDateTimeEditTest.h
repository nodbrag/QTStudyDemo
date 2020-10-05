#ifndef QDATETIMEEDITTEST_H
#define QDATETIMEEDITTEST_H

#include <QDialog>

namespace Ui {
class QDateTimeEditTest;
}

class QDateTimeEditTest : public QDialog
{
    Q_OBJECT

public:
    explicit QDateTimeEditTest(QWidget *parent = 0);
    ~QDateTimeEditTest();

private slots:
    void slot_showToolTip();

private:
    Ui::QDateTimeEditTest *ui;
};

#endif // QDATETIMEEDITTEST_H
