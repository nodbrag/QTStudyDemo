#ifndef QUICKCONFIG_H
#define QUICKCONFIG_H

#include <QtCore/qglobal.h>

#if defined(USE_SHARED)
    #define LIBRARYSHARED_EXPORT Q_DECL_EXPORT
#elif defined(USE_STATIC)
    #define LIBRARYSHARED_EXPORT
#else
    #define LIBRARYSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif
