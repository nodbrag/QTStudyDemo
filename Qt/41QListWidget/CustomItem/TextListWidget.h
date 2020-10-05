#ifndef TEXTLISTWIDGET_H
#define TEXTLISTWIDGET_H

#include <QListWidget>
#include <QMap>

class TextListWidget : public QListWidget
{
    Q_OBJECT
public:
    TextListWidget(QWidget *parent = nullptr);

    void addItem(const QString &text, const QVariant& userData = QVariant());

    QVariant userData(int row);

private slots:
    void onBtnClicked();

private:
    QMap<QObject*, QListWidgetItem*> widgetItemMap;
};

#endif // TEXTLISTWIDGET_H
