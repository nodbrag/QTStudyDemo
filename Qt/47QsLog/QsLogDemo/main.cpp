#include "mainwindow.h"
#include <QApplication>
#include <QDir>
#include <iostream>
#include "QsLog.h"

using namespace QsLogging;

void test_output_file();
void test_output_stdout();
void test_output_function();
void test_output_qobject(MainWindow* window);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    test_output_file();
//    test_output_stdout();
//    test_output_function();
//    test_output_qobject(&w);

    return a.exec();
}

// 测试文件为目的地
void test_output_file()
{
    // 初始化日志机制
    Logger& logger = Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);

    // 添加文件为目的地
    const QString sLogPath(QDir(QApplication::applicationDirPath()).filePath("log.txt"));
    DestinationPtr fileDestination(DestinationFactory::MakeFileDestination(
      sLogPath, EnableLogRotation, MaxSizeBytes(512*1024), MaxOldLogCount(5)));
    logger.addDestination(fileDestination);

    // 打印日志
    QLOG_TRACE() << "1-trace msg";
    QLOG_DEBUG() << "2-debug msg";
    QLOG_INFO() << "3-info msg";
    QLOG_WARN() << "4-warn msg";
    QLOG_ERROR() << "5-error msg";
    QLOG_FATAL()  << "6-fatal msg";

    QsLogging::Logger::destroyInstance();
}

// 测试stdout为目的地
void test_output_stdout()
{
    // 初始化日志机制
    Logger& logger = Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);

    // 添加stdout为目的地
    DestinationPtr debugDestination(DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(debugDestination);

    // 打印日志
    QLOG_TRACE() << "1-trace msg";
    QLOG_DEBUG() << "2-debug msg";
    QLOG_INFO() << "3-info msg";
    QLOG_WARN() << "4-warn msg";
    QLOG_ERROR() << "5-error msg";
    QLOG_FATAL()  << "6-fatal msg";

    QsLogging::Logger::destroyInstance();
}

void logFunction(const QString &message, QsLogging::Level level)
{
    qDebug() << "From log function: " << qPrintable(message) << " " << static_cast<int>(level);
}

// 测试函数为目的地
void test_output_function()
{
    // 初始化日志机制
    Logger& logger = Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);

    // 添加函数为目的地
    DestinationPtr functorDestination(DestinationFactory::MakeFunctorDestination(&logFunction));
    logger.addDestination(functorDestination);

    // 打印日志
    QLOG_TRACE() << "1-trace msg";
    QLOG_DEBUG() << "2-debug msg";
    QLOG_INFO() << "3-info msg";
    QLOG_WARN() << "4-warn msg";
    QLOG_ERROR() << "5-error msg";
    QLOG_FATAL()  << "6-fatal msg";

    QsLogging::Logger::destroyInstance();
}

// 测试QObject为目的地
void test_output_qobject(MainWindow* window)
{
    // 初始化日志机制
    Logger& logger = Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);

    // 添加QObject为目的地
    DestinationPtr objectDestination(DestinationFactory::MakeFunctorDestination(window, SLOT(writeLog(QString,int))));
    logger.addDestination(objectDestination);

    // 打印日志
    QLOG_TRACE() << "1-trace msg";
    QLOG_DEBUG() << "2-debug msg";
    QLOG_INFO() << "3-info msg";
    QLOG_WARN() << "4-warn msg";
    QLOG_ERROR() << "5-error msg";
    QLOG_FATAL()  << "6-fatal msg";

    QsLogging::Logger::destroyInstance();
}
