#include <QCoreApplication>
#include <QDir>
#include "QsLog.h"

using namespace QsLogging;

void test_output_file_stdout();

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    test_output_file_stdout();

    return a.exec();
}

// 测试日志输出到文件和控制台
void test_output_file_stdout()
{
    // 初始化日志机制
    Logger& logger = Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);

    // 添加日志输出到文件和控制台
    const QString sLogPath(QDir(QCoreApplication::applicationDirPath()).filePath("log.txt"));
    DestinationPtr fileDestination(DestinationFactory::MakeFileDestination(
      sLogPath, EnableLogRotation, MaxSizeBytes(512*1024), MaxOldLogCount(5)));
    DestinationPtr debugDestination(DestinationFactory::MakeDebugOutputDestination());
    logger.addDestination(fileDestination);
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

