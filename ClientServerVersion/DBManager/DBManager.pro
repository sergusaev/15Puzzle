QT -= gui
QT += core sql
CONFIG += c++11
TEMPLATE = lib

win32 {
DESTDIR = $$PWD/../shared/lib/win32
}
android {
DESTDIR = $$PWD/../shared/lib/android
}

INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$_PRO_FILE_PWD_/../shared/include

DEFINES +=

HEADERS += \
    include/connectionmanager.h \
    include/dbmapper.h \
    include/dbmanager.h \
    include/dbmanagerclient.h \
    include/dbmanagerserver.h \
    include/executor.h \
    $$_PRO_FILE_PWD_/../shared/include/dbtypes.h \
    include/manipulator.h \
    include/selector.h \
    $$_PRO_FILE_PWD_/../shared/include/processor.h


#QMAKE_POST_LINK += "$$QMAKE_COPY $$shell_quote($$shell_path($$_PRO_FILE_PWD_/include/processor.h)) $$shell_quote($$shell_path($$_PRO_FILE_PWD_/../shared/include/))"
#QMAKE_POST_LINK += " & $$QMAKE_COPY $$shell_quote($$shell_path($$_PRO_FILE_PWD_/include/manipulator.h)) $$shell_quote($$shell_path($$_PRO_FILE_PWD_/../shared/include/))"
#QMAKE_POST_LINK += " & $$QMAKE_COPY $$shell_quote($$shell_path($$_PRO_FILE_PWD_/include/dbtypes.h)) $$shell_quote($$shell_path($$_PRO_FILE_PWD_/../shared/include/))"

SOURCES += \
    src/connectionmanager.cpp \
    src/manipulator.cpp \
    src/processor.cpp \
    src/selector.cpp \
    src/dbmanager.cpp \
    src/dbmanagerserver.cpp \
    src/executor.cpp
