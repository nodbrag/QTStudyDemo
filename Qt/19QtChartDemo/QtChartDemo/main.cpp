/*
说明：此程序演示QT使用QChart绘制柱状图；
1.先下载QChart源码，参考http://blog.csdn.net/accelerated1987/article/details/50564312；
2.然后编译源码；
3.然后安装好后，相应的源文件以及Qt5Charts.dll、Qt5Charts.a就被自动拷贝至QT安装目录下相应位置；
4.最后本demo程序就可以编译运行了。
注意：如果电脑上安装了2个版本的QT，比如我的电脑上安装了QT5.3.2和QT5.5.1，那么想直接双击exe就能运行，则
需要将高和低版本的库路径都添加至环境变量中，但是在path中的位置高的要比低的靠前，否则运行会报错。
这样在分别运行高低版本的exe时，就都可以运行了。原因的话，猜测应该是先找到高版本的库，所以会兼容低版本的exe。
*/

#include <QMainWindow>
#include <QApplication>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //![1]
        QBarSet *set0 = new QBarSet("Jane");
        QBarSet *set1 = new QBarSet("John");
        QBarSet *set2 = new QBarSet("Axel");
        QBarSet *set3 = new QBarSet("Mary");
        QBarSet *set4 = new QBarSet("Samantha");

        *set0 << 1 << 2 << 3 << 4 << 5 << 6;
        *set1 << 5 << 0 << 0 << 4 << 0 << 7;
        *set2 << 3 << 5 << 8 << 13 << 8 << 5;
        *set3 << 5 << 6 << 7 << 3 << 4 << 5;
        *set4 << 9 << 7 << 5 << 3 << 1 << 2;
    //![1]

    //![2]
        QBarSeries *series = new QBarSeries();
        series->append(set0);
        series->append(set1);
        series->append(set2);
        series->append(set3);
        series->append(set4);

    //![2]

    //![3]
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle("Simple barchart example");
        chart->setAnimationOptions(QChart::SeriesAnimations);
    //![3]

    //![4]
        QStringList categories;
        categories << "Jan" << "Feb" << "Mar" << "Apr" << "May" << "Jun";
        QBarCategoryAxis *axis = new QBarCategoryAxis();
        axis->append(categories);
        chart->createDefaultAxes();
        chart->setAxisX(axis, series);
    //![4]

    //![5]
        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);
    //![5]

    //![6]
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
    //![6]

    //![7]
        QMainWindow window;
        window.setCentralWidget(chartView);
        window.resize(420, 300);
        window.show();
    //![7]

    return a.exec();
}
