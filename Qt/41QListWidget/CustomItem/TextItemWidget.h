#ifndef TEXTITEMWIDGET_H
#define TEXTITEMWIDGET_H

#include <QWidget>

class QPushButton;
class QLabel;

class TextItemWidget : public QWidget
{
    Q_OBJECT
public:
    TextItemWidget(QWidget* parent = nullptr);

    QString getText() const;
    void setText(const QString &value);

signals:
    void deleteBtnClicked();

private:
    QLabel* label;
    QPushButton* btn;
};

#endif // TEXTITEMWIDGET_H
