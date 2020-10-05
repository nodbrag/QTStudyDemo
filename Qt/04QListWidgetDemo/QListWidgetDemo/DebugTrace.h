#ifndef DEBUGTRACE_H
#define DEBUGTRACE_H

#include <stdio.h>
#include <string.h>

//开启下面的宏表示程序运行在调试版本, 否则为发行版本, 这里假设只有调试版本才输出调试信息
#define _DEBUG

#ifdef _DEBUG
    //开启下面的宏就把调试信息输出到文件，注释即输出到终端
    #define DEBUG_TO_FILE
    #ifdef DEBUG_TO_FILE
        //调试信息输出到以下文件
        #define DEBUG_FILE "/tmp/debugmsg"
        //调试信息的缓冲长度
        #define DEBUG_BUFFER_MAX 4096
        //将调试信息输出到文件中
        #define printDebugMsg(moduleName, format, ...) {  \
            char buffer[DEBUG_BUFFER_MAX+1]={0}; \
            snprintf( buffer, DEBUG_BUFFER_MAX   \
                    , "[%s] "format" File:%s, Line:%d/n", moduleName, ##__VA_ARGS__, __FILE__, __LINE__ ); \
            FILE* fd = fopen(DEBUG_FILE, "a"); \
            if ( fd != NULL ) { \
                fwrite( buffer, strlen(buffer), 1, fd );\
                fflush( fd ); \
                fclose( fd ); \
            } \
        }
    #else
        //将调试信息输出到终端
        #define printDebugMsg(moduleName, format, ...) /
                  printf( "[%s] "format" File:%s, Line:%d/n", moduleName, ##__VA_ARGS__, __FILE__, __LINE__ );
    #endif //end for #ifdef DEBUG_TO_FILE
#else
    //发行版本，什么也不做
    #define printDebugMsg(moduleName, format, ...)
#endif  //end for #ifdef _DEBUG


//void printDebugMsg( const char* format, ...)
//{
//    char buffer[DEBUG_BUFFER_MAX_LENGTH + 1]={0};

//    va_list arg;
//    va_start (arg, format);
//    vsnprintf(buffer, DEBUG_BUFFER_MAX_LENGTH, format, arg);
//    va_end (arg);

//    printf( "%s", buffer );
//}

#endif // DEBUGTRACE_H
