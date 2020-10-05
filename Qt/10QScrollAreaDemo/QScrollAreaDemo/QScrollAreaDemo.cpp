#include "QScrollAreaDemo.h"
#include <QtWidgets>

QScrollAreaDemo::QScrollAreaDemo(QWidget *parent)
    : QMainWindow(parent)
{
    // 创建控件
    openBtn = new QPushButton("打开图片", this);
    scrollArea = new QScrollArea();
    imageLabel = new QLabel("无图片");
    imageLabel->setMinimumSize(100, 200);
    scrollArea->setWidget(imageLabel);

    vLayout = new QVBoxLayout();
    vLayout->addWidget(openBtn);
    vLayout->addWidget(scrollArea);

    groupBox = new QGroupBox("操作");
    groupBox->setLayout(vLayout);

    setCentralWidget(groupBox);

    // 创建信号槽
    connect(openBtn, SIGNAL(clicked()), this, SLOT(on_OpenBtn_Clicked()));
}

QScrollAreaDemo::~QScrollAreaDemo()
{

}

void QScrollAreaDemo::on_OpenBtn_Clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", QDir::currentPath());
    if (fileName.isEmpty())    return;

    QImage image(fileName);
    if (image.isNull())
    {
        QMessageBox::information(this, tr("Image Viewer"), tr("Cannot load %1.").arg(fileName));
        return;
    }

    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->setFixedSize(image.size()); // 根据图片大小调整label大小
}
