QT += core network
QT -= gui

SOURCES += main.cpp \
           src/recordsmanager.cpp \
           src/requestshandlerserver.cpp \
           src/servermanager.cpp

HEADERS += \
           include/recordsmanager.h \
           include/requestshandlerserver.h \
           include/servermanager.h


INCLUDEPATH += $$_PRO_FILE_PWD_/include
INCLUDEPATH += $$_PRO_FILE_PWD_/../shared/include

win32 {
LIBS += -L$$PWD/../shared/lib/win32 -lDBManager
LIBS += -L$$PWD/../shared/lib/win32 -lNetworkLib
}



