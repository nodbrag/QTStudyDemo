#ifndef QUICK_H
#define QUICK_H

#include "quickcontroller.h"
#include "quickapplication.h"

#if defined(USE_SHARED)
#define QUICK_AUTO(ClassName)                                                                   \
    static int ClassId##ClassName = qRegisterMetaType<ClassName *>();                           \
    static void *ThisPtr##ClassName = QuickController::NewInstance(#ClassName);
#elif defined(USE_STATIC)
#define QUICK_AUTO(ClassName)                                                                   \
    static int ClassId##ClassName = qRegisterMetaType<ClassName *>();                           \
    static void *ThisPtr##ClassName = QuickController::NewInstance(#ClassName);
#else
#define QUICK_AUTO(ClassName)                                                                   \
    Q_DECLARE_METATYPE(ClassName *)                                                             \
    static int ClassId##ClassName = qRegisterMetaType<ClassName *>();                           \
    static void *ThisPtr##ClassName = QuickController::NewInstance(#ClassName);
#endif

#define QUICK_EVENT(PARENTANME)                                                                 \
    public:                                                                                         \
    bool event(QEvent *e) override                                                              \
    {                                                                                           \
        if(e->type() == QuickEvent::S_QuickEvent)                                                           \
        {                                                                                       \
            auto quickEvent = dynamic_cast<QuickEvent*>(e);                                     \
            auto methodName = quickEvent->eventName();                                          \
            auto infos = quickEvent->info();                                                    \
            QList<QGenericArgument> list;                                                       \
            methodName = QByteArray(METHODHEAD) + methodName;                                   \
            for(int i = 0; i < quickEvent->info().size() && i < 10; ++ i)                       \
                list << QGenericArgument(infos[i]->typeName(), infos[i]->constData());          \
            while(list.size() <= 10)                                                            \
                list << QGenericArgument();                                                     \
            QMetaObject::invokeMethod(this, methodName, list[0], list[1], list[2], list[3],     \
                                      list[4], list[5], list[6], list[7], list[8], list[9]);    \
            return true;                                                                        \
        }                                                                                       \
        return PARENTANME::event(e);                                                            \
    }

#define QUICK_DESTRUCT \
    QuickApplication::UnsubscribeEvent(this);\




#endif // QUICK_H
